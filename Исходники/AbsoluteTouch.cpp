int main(int argc, char *argv[])
{
    CommandLineArgs args(argc, argv);
    if (!args.ok) {
        PrintUsage();
        return 1;
    }

    // Print init info
    std::cout << "AbsoluteTouch v" << VERSION_NAME << std::endl;
    std::cout << "Author: " << AUTHOR << std::endl;
    std::cout << "Project page: " << PROJECT_URL << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Starting..." << std::endl;

    // Initialize COM
    CCoInitialize init;

    // Set cleanup handler
    g_mainThreadId = GetCurrentThreadId();
    if (!SetConsoleCtrlHandler(OnConsoleSignal, TRUE)) {
        std::cerr << "Error: failed to register console control handler" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Registered console control handler" << std::endl;

    // Initialize touchpad manager
    try {
        g_touchpadManager = new TouchpadManager();
    } catch (const TouchpadInitException &e) {
        std::cerr << "Error: could not initialize touchpad manager" << std::endl;
        std::cerr << e.what() << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Initialized touchpad manager" << std::endl;

    // Acquire exclusive touchpad access
    if (!g_touchpadManager->Acquire()) {
        std::cerr << "Error: could not acquire exclusive touchpad access" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Acquired exclusive touchpad access" << std::endl;

    // Register touchpad touch callback
    g_touchCallback = new AbsoluteTouchCallback();
    g_touchCallback->SetScreenRect(Rect<long>(0, 0, 65535, 65535).scale(args.screenRect));
    g_touchCallback->SetTouchpadRect(g_touchpadManager->GetTouchpadRect().scale(args.touchpadRect));
    g_touchCallback->SetSmoothingWeight(args.smoothingWeight);
    g_touchCallback->SetSendClick(args.sendClick);
    g_touchpadManager->SetTouchCallback(g_touchCallback);
    std::cout << "Registered touch listener" << std::endl;

    // Enable touchpad if option was specified
    if (args.manageTouchpad && !g_touchpadManager->IsTouchpadEnabled()) {
        g_touchpadManager->SetTouchpadEnabled(true);
        g_touchpadEnabledModified = true;
        std::cout << "Enabled touchpad" << std::endl;
    }

    // Print usage instructions
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Initialization complete, absolute touch mode enabled!" << std::endl;
    std::cout << "Keep this window open until you wish to exit absolute touch mode." << std::endl;
    std::cout << "To exit the program, you can use CTRL-C." << std::endl;

    // Main message loop
    MSG msg;
    BOOL ret;
    while ((ret = GetMessage(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CleanUp();
    g_cleanupFinished = true;
    return 0;
}