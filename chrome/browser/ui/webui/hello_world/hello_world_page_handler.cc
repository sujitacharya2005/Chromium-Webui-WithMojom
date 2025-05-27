#include "chrome/browser/ui/webui/hello_world/hello_world_page_handler.h"

#include "base/logging.h"

HelloWorldPageHandler::HelloWorldPageHandler(
    mojo::PendingReceiver<hello_world::mojom::HelloWorldPageHandler> receiver)
    : receiver_(this, std::move(receiver)) {
  LOG(INFO) << "HelloWorldPageHandler created and bound!";
}

void HelloWorldPageHandler::Greet(GreetCallback callback) {
  std::move(callback).Run("Hello from C++ backend!");
}

HelloWorldPageHandler::~HelloWorldPageHandler() = default;
