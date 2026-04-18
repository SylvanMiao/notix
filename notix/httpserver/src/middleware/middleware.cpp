#include "middleware.h"
#include "beast_http.h"
#include "program_state_test.h"

#include <algorithm>

namespace middleware
{
	void HtmlAfterBadge::operator()(HttpContext &ctx, Next next) const
	{
		next();

		if (!ctx.response.base().count(http::field::content_type))
		{
			return;
		}

		std::string content_type(ctx.response[http::field::content_type]);
		std::transform(content_type.begin(), content_type.end(), content_type.begin(),
									 [](unsigned char c)
									 { return static_cast<char>(std::tolower(c)); });

		if (content_type.find("text/html") == std::string::npos)
		{
			return;
		}

		auto body_str = boost::beast::buffers_to_string(ctx.response.body().data());
		const std::string badge =
				"<div style=\"margin-top:12px;padding:8px;border:1px dashed #888;color:#333;\">"
				"After Middleware Applied ✅"
				"</div>";

		const std::string closing_body = "</body>";
		const auto pos = body_str.find(closing_body);
		if (pos != std::string::npos)
		{
			body_str.insert(pos, badge);
		}
		else
		{
			body_str += badge;
		}

		ctx.response.body().clear();
		beast::ostream(ctx.response.body()) << body_str;
	}

	void MethodGuard::operator()(http_connection &self, HttpContext &ctx, Next next) const
	{
		const auto method = ctx.method();
		if (method != http::verb::get && method != http::verb::post)
		{
			self.send_error(http::status::method_not_allowed, 1401,
											"invalid request method: " + std::string(ctx.request.method_string()));
			ctx.stop();
			return;
		}

		next();
	}

	void DemoPageBefore::operator()(HttpContext &ctx, Next next) const
	{
		const auto target = ctx.target();
		if (ctx.method() == http::verb::get &&
				(target == "/mw-demo" || target == "/mw_demo"))
		{
			ctx.response.result(http::status::ok);
			ctx.response.set(http::field::content_type, "text/html; charset=utf-8");
			ctx.response.body().clear();
			beast::ostream(ctx.response.body())
					<< "<html><head><title>Middleware Demo</title></head><body>"
					<< "<h1>Before Middleware Worked ✅</h1>"
					<< "<p>This page is generated directly by middleware before router dispatch.</p>"
					<< "<p>Now: " << program_state_test::now() << "</p>"
					<< "<p>Target: " << target << "</p>"
					<< "</body></html>";
			ctx.stop();
			return;
		}

		next();
	}

	void register_default_middlewares(http_connection &self, MiddlewarePipeline &pipeline)
	{
		// pipeline.use([](HttpContext &ctx, Next next)
		// 							 { HtmlAfterBadge{}(ctx, next); });

		pipeline.use([&self](HttpContext &ctx, Next next)
								 { MethodGuard{}(self, ctx, next); });

		pipeline.use([](HttpContext &ctx, Next next)
								 { DemoPageBefore{}(ctx, next); });
	}
}


