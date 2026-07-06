# Memories

> 校园记忆胶片杂志 — 每一张照片，都是青春的底片。

Memories 是一款专为校园场景打造的跨平台客户端，支持 Android、iOS、Windows、macOS 和 Linux。每所学校拥有独立的客户端包，数据隔离、安全可靠。

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)

---

## 项目结构

```text
Memories-Client/
├── web/          # Web 前台（React + Vite + Tailwind CSS）
├── Android/      # Android 原生客户端（Java）
├── iOS/          # iOS 客户端
├── macOS/        # macOS 客户端
├── Windows/      # Windows 客户端
├── Linux/        # Linux 客户端
├── admin/        # 管理后台
└── LICENSE       # GPL v3
```

## 快速开始

按需进入对应平台目录构建。首次克隆后建议先准备各端的本地配置文件，再执行构建命令；真实配置、依赖缓存和构建产物不应提交到仓库。

| 模块 | 入口 | 常用命令 |
| ------ | ------ | ---------- |
| Web 前台 | `web/` | `pnpm install`、`pnpm dev`、`pnpm build` |
| 管理后台 | `admin/` | `npm install`、`npm run dev`、`npm run build` |
| Android | `Android/` | `./gradlew :app:assembleDebug` |
| Linux | `Linux/` | `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release` |
| Windows | `Windows/` | 见 `Windows/README.md` |

## 本地配置

- Android：复制 `Android/app-config.example.properties` 到 `Android/app/src/main/assets/app-config.properties`，填写 API、OAuth、学校和主题配置。
- Linux/Windows：按平台 README 安装 Qt、CMake 和编译器后构建。
- Web/admin：依赖目录 `node_modules/` 和构建目录 `dist/` 只保留在本机。

## 清理构建产物

以下目录是可再生成产物，已在 `.gitignore` 中忽略，可按需删除后重新构建：

```bash
rm -rf build Android/.gradle Android/build Android/app/build Linux/build Linux/build-gcc14 Linux/build-release web/dist admin/dist
```

## Web 前台

基于 React 18 + Vite + Tailwind CSS + shadcn/ui 构建。

```bash
cd web
pnpm install
pnpm dev        # 启动开发服务器
pnpm build      # 构建静态文件到 dist/
```

## Android 客户端

原生 Java 项目，使用 Android Studio 或 Gradle 构建。

```bash
cd Android
cp app-config.example.properties app/src/main/assets/app-config.properties
# 编辑配置文件填入你的参数
./gradlew :app:assembleDebug
```

详细说明见 [Android/README.md](Android/README.md)。

## 桌面客户端

- Linux 客户端使用 C++20、Qt 6 和 CMake 构建，详细说明见 [Linux/README.md](Linux/README.md)。
- Windows 客户端使用 C++20、Qt 6 和 CMake 构建，详细说明见 [Windows/README.md](Windows/README.md)。

## 主要功能

- 📷 **校园广场** — 浏览全校师生的照片记忆
- 📤 **多图上传** — 支持批量选择、队列上传、进度展示
- 🔗 **OAuth 登录** — 通过校园墙账号安全登录
- 🎨 **主题定制** — 亮色 / 暗色主题自由切换
- 📦 **一校一包** — 每所学校独立客户端，数据完全隔离
- 🌐 **跨平台** — Android / iOS / Windows / macOS / Linux 全覆盖

## 技术栈

| 模块 | 技术 |
| ------ | ------ |
| 官网 | React 18, Vite, Tailwind CSS, shadcn/ui, Framer Motion |
| Android | Java, Android SDK, Gradle |
| 多语言 | 简体中文 / 繁體中文 / English / 日本語 |

## 开源协议

本项目基于 [GNU General Public License v3.0](LICENSE) 开源。
