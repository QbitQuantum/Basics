int SimulatorWin::run()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    parseCocosProjectConfig(_project);

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

    if (_project.getProjectDir().empty())
    {
        if (args.size() == 2)
        {
            // for Code IDE before RC2
            _project.setProjectDir(args.at(1));
            _project.setDebuggerType(kCCRuntimeDebuggerCodeIDE);
        }
    }

    // create the application instance
    _app = new AppDelegate();
    RuntimeEngine::getInstance()->setProjectConfig(_project);

#if (SIMULATOR_WITH_CONSOLE_AND_MENU > 0)
    // create console window
    if (_project.isShowConsole())
    {
        AllocConsole();
        _hwndConsole = GetConsoleWindow();
        if (_hwndConsole != NULL)
        {
            ShowWindow(_hwndConsole, SW_SHOW);
            BringWindowToTop(_hwndConsole);
            freopen("CONOUT$", "wt", stdout);
            freopen("CONOUT$", "wt", stderr);

            HMENU hmenu = GetSystemMenu(_hwndConsole, FALSE);
            if (hmenu != NULL)
            {
                DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
            }
        }
    }
#endif

    // log file
    if (_project.isWriteDebugLogToFile())
    {
        const string debugLogFilePath = _project.getDebugLogFilePath();
        _writeDebugLogFile = fopen(debugLogFilePath.c_str(), "w");
        if (!_writeDebugLogFile)
        {
            CCLOG("Cannot create debug log file %s", debugLogFilePath.c_str());
        }
    }

    // set environments
    SetCurrentDirectoryA(_project.getProjectDir().c_str());
    FileUtils::getInstance()->setDefaultResourceRootPath(_project.getProjectDir());
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
    if (dpi >= 120 && dpi < 144)
    {
        screenScale = 1.25f;
    }
    else if (dpi >= 144 && dpi < 192)
    {
        screenScale = 1.5f;
    }
    else if (dpi >= 192)
    {
        screenScale = 2.0f;
    }
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
    ConfigParser::getInstance()->setInitViewSize(frameSize);
    const bool isResize = _project.isResizeWindow();
    std::stringstream title;
    title << "Cocos Simulator - " << ConfigParser::getInstance()->getInitViewName();
    initGLContextAttrs();
    auto glview = GLViewImpl::createWithRect(title.str(), frameRect, frameScale);
    _hwnd = glview->getWin32Window();
    player::PlayerWin::createWithHwnd(_hwnd);
    DragAcceptFiles(_hwnd, TRUE);
    //SendMessage(_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
    //SendMessage(_hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
    //FreeResource(icon);

    auto director = Director::getInstance();
    director->setOpenGLView(glview);

    director->setAnimationInterval(1.0 / 60.0);

    // set window position
    if (_project.getProjectDir().length())
    {
        setZoom(_project.getFrameScale());
    }
    Vec2 pos = _project.getWindowOffset();
    if (pos.x != 0 && pos.y != 0)
    {
        RECT rect;
        GetWindowRect(_hwnd, &rect);
        MoveWindow(_hwnd, pos.x, pos.y, rect.right - rect.left, rect.bottom - rect.top, FALSE);
    }

    // path for looking Lang file, Studio Default images
    FileUtils::getInstance()->addSearchPath(getApplicationPath().c_str());

#if SIMULATOR_WITH_CONSOLE_AND_MENU > 0
    // init player services
    setupUI();
    DrawMenuBar(_hwnd);
#endif

    // prepare
    FileUtils::getInstance()->setPopupNotify(false);
    _project.dump();
    auto app = Application::getInstance();

    g_oldWindowProc = (WNDPROC)SetWindowLong(_hwnd, GWL_WNDPROC, (LONG)SimulatorWin::windowProc);

    // startup message loop
    return app->run();
}