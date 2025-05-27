
# Hello World WebUI (chrome://hello_world)

This is a minimal Chromium WebUI page (`chrome://hello_world`) demonstrating Mojo interface integration between the browser (C++) and renderer (TypeScript) layers.

## ✨ Overview

This WebUI example showcases:

- `chrome://hello_world` registered as a new WebUI page
- Mojo-based communication between JS (renderer) and C++ (browser)
- A working Mojo `PageHandlerFactory` and `PageHandler` example
- TypeScript-based frontend calling C++ `greet()` method
- Safe and structured IPC using `.mojom` interfaces

---

## 📁 Project Structure

```text
chrome/
├── browser/
│   ├── chrome_browser_interface_binders_webui.cc  # Registers Mojo binders
│   └── ui/
│       └── webui/
│           └── hello_world/
│               ├── hello_world_ui.{h,cc}          # WebUI controller
│               ├── hello_world_page_handler.{h,cc}# Mojo backend impl
│               └── hello_world.mojom              # Mojo interface
├── browser_exposed_mojom_targets.gni              # Expose Mojom to frontend
├── chrome_paks.gni                                # Add resources to .pak
└── tools/gritsettings/resource_ids.spec           # Reserve resource IDs

chrome/browser/resources/
└── hello_world/
    ├── hello_world.html                           # HTML entrypoint
    ├── hello_world.ts                             # TypeScript frontend
    └── BUILD.gn                                    # WebUI resource build config
```

---

## 🔌 Mojo Interface

```mojom
module hello_world.mojom;

interface HelloWorldPageHandler {
  Greet() => (string message);
};

interface HelloWorldPageHandlerFactory {
  CreateHelloWorldPageHandler(
    pending_receiver<HelloWorldPageHandler> handler);
};
```

---

## 🧠 Mojo Lifecycle (Renderer → Browser)

1. `hello_world.ts` uses `HelloWorldPageHandlerFactory.getRemote()` to get a Mojo interface.
2. JS calls `createHelloWorldPageHandler(...)` with a locally created `HelloWorldPageHandlerRemote`.
3. Browser receives it in `HelloWorldUI::CreateHelloWorldPageHandler(...)`.
4. Browser handler responds to `greet()` with a string.
5. JS prints the message: ✅ `"Hello from C++ backend!"`

---

## 🧪 Verify It Works

- Run Chromium and navigate to:  
  ```
  chrome://hello_world
  ```
- Open DevTools → Console:  
  ✅ You should see:  
  ```
  Greeting from handler: Hello from C++ backend!
  ```

---

## ⚙️ Build Integration

Ensure the following are included:

- `chrome_browser_interface_binders_webui.cc`  
  ```cpp
  RegisterWebUIControllerInterfaceBinder<
      ::hello_world::mojom::HelloWorldPageHandlerFactory, HelloWorldUI>(map);
  ```
- `chrome_web_ui_configs.cc`  
  ```cpp
  webui::HelloWorldUIConfig::Register();
  ```
- `chrome_paks.gni`, `BUILD.gn`, `resource_ids.spec` to pack the HTML/JS

---

## 💡 Tip: Debugging Mojo

- Check `chrome_debug.log` (on Windows: `%LOCALAPPDATA%\Chromium\User Data\chrome_debug.log`)
- Mojo error: `No binder found...` usually means the interface wasn’t registered via `RegisterWebUIControllerInterfaceBinder<>()`
- You can add `LOG(INFO)` or breakpoints in:
  - `HelloWorldUI::BindInterface()`
  - `HelloWorldUI::CreateHelloWorldPageHandler()`

---

## 📦 License

BSD-style license, see Chromium LICENSE file.
