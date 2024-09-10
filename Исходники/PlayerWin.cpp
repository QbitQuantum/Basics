int PlayerWin::run()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    // set QUICK_V3_ROOT
    const char *QUICK_V3_ROOT = getenv("QUICK_V3_ROOT");
    if (!QUICK_V3_ROOT || strlen(QUICK_V3_ROOT) == 0)
    {
        MessageBox("Please run \"setup_win.bat\", set quick-cocos2d-x root path.", "quick-cocos2d-x player error");
        return 1;
    }
    SimulatorConfig::getInstance()->setQuickCocos2dxRootPath(QUICK_V3_ROOT);

    // load project config from command line args
    vector<string> args;
    for (int i = 0; i < __argc; ++i)
    {
        wstring ws(__wargv[i]);
        string s;
        s.assign(ws.begin(), ws.end());
        args.push_back(s);
    }
    _project.parseCommandLine(args);

    if (_project.getProjectDir().length() <= 0)
    {
        _project.resetToWelcome();
    }

    // set framework path
    if (!_project.isLoadPrecompiledFramework())
    {
        FileUtils::getInstance()->addSearchPath(SimulatorConfig::getInstance()->getQuickCocos2dxRootPath() + "quick/");
    }

    // create the application instance
    _app = new AppDelegate();
    _app->setProjectConfig(_project);

    // set window icon
    HICON icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_PLAYER));

    // create console window
    if (_project.isShowConsole())
    {
        AllocConsole();
        _hwndConsole = GetConsoleWindow();
        if (_hwndConsole != NULL)
        {
            SendMessage(_hwndConsole, WM_SETICON, ICON_BIG, (LPARAM)icon);
            SendMessage(_hwndConsole, WM_SETICON, ICON_SMALL, (LPARAM)icon);

            ShowWindow(_hwndConsole, SW_SHOW);
            BringWindowToTop(_hwndConsole);
            freopen("CONOUT$", "wt", stdout);
            freopen("CONOUT$", "wt", stderr);

            HMENU hmenu = GetSystemMenu(_hwndConsole, FALSE);
            if (hmenu != NULL) DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
        }
    }

    // set environments
    SetCurrentDirectoryA(_project.getProjectDir().c_str());
    FileUtils::getInstance()->setSearchRootPath(_project.getProjectDir().c_str());
    FileUtils::getInstance()->setWritablePath(_project.getWritableRealPath().c_str());

    // check screen DPI
    HDC screen = GetDC(0);
    int dpi = GetDeviceCaps(screen, LOGPIXELSX);
    ReleaseDC(0, screen);

    // set scale with DPI
    //  96 DPI = 100 % scaling
    // 120 DPI = 125 % scaling
    // 144 DPI = 150 % scaling
    // 192 DPI = 200 % scaling
    // http://msdn.microsoft.com/en-us/library/windows/desktop/dn469266%28v=vs.85%29.aspx#dpi_and_the_desktop_scaling_factor
    //
    // enable DPI-Aware with DeclareDPIAware.manifest
    // http://msdn.microsoft.com/en-us/library/windows/desktop/dn469266%28v=vs.85%29.aspx#declaring_dpi_awareness
    float screenScale = 1.0f;
    //if (dpi >= 120 && dpi < 144)
    //{
    //    screenScale = 1.25f;
    //}
    //else if (dpi >= 144 && dpi < 192)
    //{
    //    screenScale = 1.5f;
    //}
    //else if (dpi >= 192)
    //{
    //    screenScale = 2.0f;
    //}
    CCLOG("SCREEN DPI = %d, SCREEN SCALE = %0.2f", dpi, screenScale);

    // create opengl view
    Size frameSize = _project.getFrameSize();
    float frameScale = 1.0f;
    if (_project.isRetinaDisplay())
    {
        frameSize.width *= screenScale;
        frameSize.height *= screenScale;
    }
    else
    {
        frameScale = screenScale;
    }

    const Rect frameRect = Rect(0, 0, frameSize.width, frameSize.height);
    const bool isResize = _project.isResizeWindow();
	auto glview = GLViewImpl::createWithRect("quick-cocos2d-x", frameRect, frameScale, isResize);
	_hwnd = glview->getWin32Window();
    SendMessage(_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
    SendMessage(_hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
    FreeResource(icon);

    auto director = Director::getInstance();
    director->setOpenGLView(glview);
    //director->setScreenScale(screenScale);

    // set window position
    if (_project.getProjectDir().length())
    {
        setZoom(_project.getFrameScale());
        Vec2 pos = _project.getWindowOffset();
        if (pos.x != 0 && pos.y != 0)
        {
            glfwSetWindowPos(glview->getWindow(), pos.x, pos.y);
        }
    }

    // init player services
    initServices();

    loadLuaConfig();
    registerKeyboardEvent();

    // register event handlers
    auto eventDispatcher = director->getEventDispatcher();
    eventDispatcher->addCustomEventListener("APP.WINDOW_CLOSE_EVENT", CC_CALLBACK_1(PlayerWin::onWindowClose, this));
    eventDispatcher->addCustomEventListener("APP.WINDOW_RESIZE_EVENT", CC_CALLBACK_1(PlayerWin::onWindowResize, this));
    eventDispatcher->addCustomEventListener("APP.VIEW_SCALE", CC_CALLBACK_1(PlayerWin::onWindowScale, this));

    // prepare
    _project.dump();
    auto app = Application::getInstance();
    glfwSetWin32WindowProc(&PlayerWin::windowProc);

    HWND hwnd = _hwnd;
    HWND hwndConsole = _hwndConsole;
    const ProjectConfig &project = _project;
    director->getScheduler()->schedule([hwnd, hwndConsole, project](float dt) {
        CC_UNUSED_PARAM(dt);
        ShowWindow(hwnd, SW_RESTORE);
		GLFWwindow *window = dynamic_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView())->getWindow();
        glfwShowWindow(window);
    }, this, 0.0f, 0, 0.001f, false, "SHOW_WINDOW_CALLBACK");

    if (project.isAppMenu() && GetMenu(hwnd))
    {
        // update window size
        RECT rect;
        GetWindowRect(_hwnd, &rect);
        MoveWindow(_hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top + GetSystemMetrics(SM_CYMENU), FALSE);
    }
    ShowWindow(_hwnd, SW_MINIMIZE);

    // startup message loop
    return app->run();
}