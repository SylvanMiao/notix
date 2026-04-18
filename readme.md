# Notix 项目说明

## 项目简述

开发平台：`Ubuntu 22.04`

当前核心目标是基于 Asio + Beast 构建可演进的 HTTP 网关框架，并逐步补齐中间件、路由、会话与生产化能力。
同时构建AI原生服务，支持一站式图像处理与知识库问答

已规划：

1. 使用 Asio 构建异步网络服务器
2. 使用 Beast 实现 HTTP 网关能力
3. 用户信息录入与管理
4. 图像处理能力集成
5. LLM 问答模块集成

---

## 当前目录（HTTP 相关）

- `notix/httpserver/`
	- `src/http/`：Beast 连接处理与请求分发
	- `src/router/`：静态/动态路由匹配
	- `src/middleware/`：中间件函数对象与注册
	- `inc/middleware/http_context.h`：中间件上下文
	- `static/`：HTML 模板资源

---

## 当前已实现能力（截至 2026-04-16）

### HTTP 与请求处理

- GET/POST 分发
- JSON 统一错误返回
- `Content-Type` / 空 body / JSON 格式校验
- body 大小限制（1MB）
- 请求日志（method/target/status/cost/error）

### 路由

- 静态路由：`/count`、`/time`、`/email`
- 动态路由参数：如 `/time/{zone}`、`/email/{source}`
- Router 抽象与匹配结果结构（`match_result`）

### 中间件

- MiddlewarePipeline（`before` / `after`）
- 统一 `HttpContext`（request/response/route/state）
- 方法守卫中间件（仅允许 GET/POST）
- before 可视化示例：`/mw-demo`、`/mw_demo`
- after 可视化示例：HTML 响应注入标记

---

## 第一部分HTTP框架 与个人`todo.md` 的阶段对齐

### 阶段 0：用户与数据基础能力（P0+）

- 状态：**未开始**
- 说明：优先级高于阶段 C / D，用于把框架提升为“可用”状态
- 计划项：
	- Session 支持：会话管理、登录态保持、TTL 续期
	- Session 持久化：数据库存储（可选：内存 + DB 双写）
	- 数据库连接池：统一连接管理、复用与超时处理
	- 轻量 ORM：简化 CRUD 与对象映射

### 阶段 A：先修正确性（P0）

- 状态：**已完成**
- 覆盖项：POST 分发、错误统一、基础校验、body limit、关键日志

### 阶段 B：抽象路由与处理链（P1）

- 状态：**已完成**
- 已完成：Router、动态参数、上下文对象、MiddlewarePipeline
- 待完善：路由处理仍有部分在 `http_connection` 内硬编码分支，尚未完全 handler 注册化

### 阶段 C：补齐 Web 基础能力（P1）

- 状态：**未开始**
- 计划项：CORS、Session、鉴权、静态文件服务化

### 阶段 D：生产化增强（P2）

- 状态：**未开始**
- 计划项：TLS/HTTPS、连接策略增强、限流、可观测性指标

---

## 最近开发里程碑

- **2026-03-10**：验证 Boost.Beast 与 JsonCpp 基础可用
- **2026-04-13**：完成基础 Beast HTTP 框架与路由雏形
- **2026-04-16**：中间件框架落地（before/after + 可视化验证）
- **2026-04-18**：将路由回调修改为 handler 风格，降低 `http_connection` 内分支复杂度
---

## 下一步计划

0. 优先实现用户与数据基础能力（Session + 数据库）
	- SessionManager（Cookie + TTL + 登录态）
	- Session 数据库持久化（含读写策略）
	- 数据库连接池与轻量 ORM 接入

1. 进入阶段 C：优先实现 CORS（含 OPTIONS 预检）
2. 鉴权中间件（白名单 + 登录校验）

---

## TODO（高优先级）

1. Session 生命周期设计（创建、续期、失效、清理）
2. Session 数据结构与序列化格式（JSON 或二进制）
3. Session 存储接口抽象（内存实现 / 数据库实现）
4. 数据库连接池设计（最大连接数、超时、健康检查）
5. ORM 选型与最小封装（基础 CRUD + 查询参数）
6. 登录态中间件与 Session 绑定策略
