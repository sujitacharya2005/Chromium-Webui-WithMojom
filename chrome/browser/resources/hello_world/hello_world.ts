import {
  HelloWorldPage,
  HelloWorldPageHandlerRemote,
  HelloWorldPageHandlerFactory,
} from './hello_world.mojom-webui.js';

class HelloWorldPageImpl {
  constructor() {
    // ✅ Create the handlerRemote (unbound initially)
    const handlerRemote = new HelloWorldPageHandlerRemote();

    // ✅ Create the remote for HelloWorldPage (optional, if needed)
    const pageRemote = HelloWorldPage.getRemote();

    // ✅ Request the factory from the browser
    const factory = HelloWorldPageHandlerFactory.getRemote();

    // ✅ Use the factory to bind the handler
    factory.createHelloWorldPageHandler(
      pageRemote,                                      // page remote
      handlerRemote.$.bindNewPipeAndPassReceiver()     // correct pending_receiver
    );

    // ✅ Now you can use handlerRemote
    handlerRemote.greet().then(response => {
      console.log('Greeting from handler:', response.message);
    });
  }
}

new HelloWorldPageImpl();
