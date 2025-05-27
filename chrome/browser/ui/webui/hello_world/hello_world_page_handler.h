#include "chrome/browser/ui/webui/hello_world/hello_world.mojom.h"
#include "mojo/public/cpp/bindings/receiver.h"

class HelloWorldPageHandler : public hello_world::mojom::HelloWorldPageHandler {
 public:
  explicit HelloWorldPageHandler(
      mojo::PendingReceiver<hello_world::mojom::HelloWorldPageHandler>
          receiver);
  void Greet(GreetCallback callback) override;
  ~HelloWorldPageHandler() override;


 private:
  mojo::Receiver<hello_world::mojom::HelloWorldPageHandler> receiver_;
};
