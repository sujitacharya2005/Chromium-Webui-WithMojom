// chrome/browser/ui/webui/hello_world/hello_world_ui.h

#include "chrome/browser/ui/webui/hello_world/hello_world.mojom.h"
#include "chrome/browser/ui/webui/hello_world/hello_world_page_handler.h"
#include "content/public/browser/webui_config.h"
#include "content/public/common/url_constants.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "ui/webui/mojo_web_ui_controller.h"

class HelloWorldUI;

class HelloWorldUIConfig : public content::DefaultWebUIConfig<HelloWorldUI> {
 public:
  HelloWorldUIConfig()
      : DefaultWebUIConfig(content::kChromeUIScheme, "hello_world") {}
  std::unique_ptr<content::WebUIController> CreateWebUIController(
      content::WebUI* web_ui,
      const GURL& url) override;

  bool IsWebUIEnabled(content::BrowserContext* browser_context) override;
};

class HelloWorldUI : public ui::MojoWebUIController,
                     public hello_world::mojom::HelloWorldPageHandlerFactory {
 public:
  explicit HelloWorldUI(content::WebUI* web_ui);
  HelloWorldUI(const HelloWorldUI&) = delete;
  HelloWorldUI& operator=(const HelloWorldUI&) = delete;
  ~HelloWorldUI() override;

  void BindInterface(
      mojo::PendingReceiver<hello_world::mojom::HelloWorldPageHandlerFactory>
          receiver);
 void BindInterface(
            mojo::PendingReceiver<hello_world::mojom::HelloWorldPage> receiver);
        

 private:
  void CreateHelloWorldPageHandler(
      mojo::PendingRemote<hello_world::mojom::HelloWorldPage> page,
      mojo::PendingReceiver<hello_world::mojom::HelloWorldPageHandler> handler)
      override;

  std::unique_ptr<HelloWorldPageHandler> page_handler_;
  mojo::Receiver<hello_world::mojom::HelloWorldPageHandlerFactory>
      factory_receiver_{this};
  WEB_UI_CONTROLLER_TYPE_DECL();
};
