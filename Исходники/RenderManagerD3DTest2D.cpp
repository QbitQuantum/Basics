int main(int argc, char* argv[]) {
    // Get an OSVR client context to use to access the devices
    // that we need.
    osvr::clientkit::ClientContext context(
        "org.opengoggles.exampleclients.TrackerCallback");

    // Construct button devices and connect them to a callback
    // that will set the "quit" variable to true when it is
    // pressed.  Use button "1" on the left-hand or
    // right-hand controller.
    osvr::clientkit::Interface leftButton1 =
        context.getInterface("/controller/left/1");
    leftButton1.registerCallback(&myButtonCallback, &quit);

    osvr::clientkit::Interface rightButton1 =
        context.getInterface("/controller/right/1");
    rightButton1.registerCallback(&myButtonCallback, &quit);

    // Open Direct3D and set up the context for rendering to
    // an HMD.  Do this using the OSVR RenderManager interface,
    // which maps to the nVidia or other vendor direct mode
    // to reduce the latency.
    osvr::renderkit::RenderManager* render =
        osvr::renderkit::createRenderManager(context.get(), "Direct3D11");

    if ((render == nullptr) || (!render->doingOkay())) {
        std::cerr << "Could not create RenderManager" << std::endl;
        return 1;
    }

    // Set callback to handle setting up rendering in an eye
    render->SetDisplayCallback(SetupDisplay);

    // Register callbacks to render things in left hand, right
    // hand, and world space.
    render->AddRenderCallback("/", DrawWorld);

// Set up a handler to cause us to exit cleanly.
#ifdef _WIN32
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
#endif

    // Open the display and make sure this worked.
    osvr::renderkit::RenderManager::OpenResults ret = render->OpenDisplay();
    if (ret.status == osvr::renderkit::RenderManager::OpenStatus::FAILURE) {
        std::cerr << "Could not open display" << std::endl;
        return 2;
    }
    if (ret.library.D3D11 == nullptr) {
        std::cerr << "Attempted to run a Direct3D11 program with a config file "
                  << "that specified a different rendering library."
                  << std::endl;
        return 3;
    }

    // Set up the rendering state we need.
    if (!SetupRendering(ret.library)) {
        return 4;
    }

    // Continue rendering until it is time to quit.
    while (!quit) {
        // Update the context so we get our callbacks called and
        // update tracker state.
        context.update();

        if (!render->Render()) {
            std::cerr
                << "Render() returned false, maybe because it was asked to quit"
                << std::endl;
            quit = true;
        }
    }

    g_vertexBuffer->Release();

    // Close the Renderer interface cleanly.
    delete render;

    return 0;
}