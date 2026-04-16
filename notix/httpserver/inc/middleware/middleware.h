#pragma once
#include <functional>
#include <vector>

#include "http_context.h"

class http_connection;


// 这里用运行时多态，主要是next()需要在函数对象数组中满足调用栈
using Next = std::function<void()>;
using Middleware = std::function<void(middleware::HttpContext &, Next)>;
using FinalHandler = std::function<void(middleware::HttpContext &)>;

class MiddlewarePipeline {
public:
    void use(Middleware m) {
        middlewares.push_back(m);
    }

    void execute(middleware::HttpContext &ctx, FinalHandler final_handler = nullptr) {
        size_t index = 0;

        std::function<void()> dispatch = [&]() {
            if (ctx.terminated) return;

            if (index >= middlewares.size()) {
                if (final_handler) {
                    final_handler(ctx);
                }
                return;
            }

            auto& m = middlewares[index++];
            m(ctx, dispatch);
        };

        dispatch();
    }

private:
    std::vector<Middleware> middlewares;
};



namespace middleware
{
    /**
     * @brief after middleware：在后续处理完成后为 HTML 响应注入可视化标记。
     */
    struct HtmlAfterBadge {
        void operator()(HttpContext &ctx, Next next) const;
    };

    /**
     * @brief 方法守卫中间件（仅允许 GET/POST）
     */
    struct MethodGuard {
        void operator()(http_connection &self, HttpContext &ctx, Next next) const;
    };

    /**
     * @brief before middleware 示例：拦截 `/mw-demo` 与 `/mw_demo`。
     */
    struct DemoPageBefore {
        void operator()(HttpContext &ctx, Next next) const;
    };

    /**
     * @brief 注册默认中间件链。
     * @param self 当前连接对象（用于写错误响应）
     * @param pipeline 中间件管线
     */
    void register_default_middlewares(http_connection &self, MiddlewarePipeline &pipeline);

}
// Middleware logger = [](middleware::HttpContext& ctx, Next next) {
//     std::cout << ctx.request.method_string() << " " << ctx.target() << std::endl;
//     next();
// };