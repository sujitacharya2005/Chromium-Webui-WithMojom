// chrome/browser/ui/webui/hello_world/hello_world_ui.cc

#include "chrome/browser/ui/webui/hello_world/hello_world_ui.h"

#include "base/containers/span.h"
#include "base/logging.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/grit/hello_world_resources.h"
#include "chrome/grit/hello_world_resources_map.h"
#include "content/public/browser/web_ui_data_source.h"
#include "ui/webui/webui_util.h"

std::unique_ptr<content::WebUIController>
HelloWorldUIConfig::CreateWebUIController(content::WebUI* web_ui,
                                          const GURL& url) {
  return std::make_unique<HelloWorldUI>(web_ui);
}

bool HelloWorldUIConfig::IsWebUIEnabled(
    content::BrowserContext* browser_context) {
  return true;
}

HelloWorldUI::HelloWorldUI(content::WebUI* web_ui)
    : MojoWebUIController(web_ui, true) {
  content::WebUIDataSource* source = content::WebUIDataSource::CreateAndAdd(
      Profile::FromWebUI(web_ui), "hello_world");
  //   source->AddResourcePaths(kHelloWorldResources);
  // source->AddResourcePath("hello_world.html",
  // IDR_HELLO_WORLD_HELLO_WORLD_HTML); source->AddResourcePath(
  //     "hello_world.js",
  //     IDR_HELLO_WORLD_HELLO_WORLD_JS);  // ts will compile to js
  // source->AddResourcePath("hello_world.mojom-webui.js",
  //                         IDR_HELLO_WORLD_HELLO_WORLD_MOJOM_WEBUI_JS);
  // source->AddResourcePath("user_display_mode.mojom-webui.js",
  //                         IDR_HELLO_WORLD_USER_DISPLAY_MODE_MOJOM_WEBUI_JS);

  // source->SetDefaultResource(IDR_HELLO_WORLD_HELLO_WORLD_HTML);
  // //
  // content::WebUIDataSource::Add(web_ui->GetWebContents()->GetBrowserContext(),
  // //                                 source);
  webui::SetupWebUIDataSource(source, kHelloWorldResources,
                              IDR_HELLO_WORLD_HELLO_WORLD_HTML);
}

void HelloWorldUI::BindInterface(
    mojo::PendingReceiver<hello_world::mojom::HelloWorldPageHandlerFactory>
        receiver) {
  LOG(INFO) << "Sumit BindInterface ";

  factory_receiver_.Bind(std::move(receiver));
}

void HelloWorldUI::BindInterface(
  mojo::PendingReceiver<hello_world::mojom::HelloWorldPage> receiver) {
LOG(INFO) << "Bound HelloWorldPage interface";
// Not used? Just store or ignore
}


void HelloWorldUI::CreateHelloWorldPageHandler(
    mojo::PendingRemote<hello_world::mojom::HelloWorldPage> page,
    mojo::PendingReceiver<hello_world::mojom::HelloWorldPageHandler> handler) {
  LOG(INFO) << "Sumit CreateHelloWorldPageHandler ";

  page_handler_ = std::make_unique<HelloWorldPageHandler>(std::move(handler));
}

WEB_UI_CONTROLLER_TYPE_IMPL(HelloWorldUI)

HelloWorldUI::~HelloWorldUI() = default;
