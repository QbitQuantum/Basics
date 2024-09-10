int LuaHostWin32::run(void)
{
    loadProjectConfig();

    AllocConsole();
    freopen("CONOUT$", "wt", stdout);
    freopen("CONOUT$", "wt", stderr);

    // disable close console
    HWND hwndConsole = GetConsoleWindow();
    if (hwndConsole != NULL)
    {
        HMENU hMenu = GetSystemMenu(hwndConsole, FALSE);
        if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }

    do
    {
        m_exit = TRUE;

        if (m_project.isShowConsole())
        {
            ShowWindow(hwndConsole, SW_SHOW);
            BringWindowToTop(hwndConsole);
        }
        else
        {
            ShowWindow(hwndConsole, SW_HIDE);
        }

        // create the application instance
        m_app = new AppDelegate();
        m_app->setStartupScriptFilename(m_project.getScriptFilePath());

        // set environments
        SetCurrentDirectoryA(m_project.getProjectDir().c_str());
        vector<string> searchPaths;
        searchPaths.push_back(m_project.getProjectDir());
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

        // create opengl view
        CCEGLView* eglView = CCEGLView::sharedOpenGLView();    
        eglView->setMenuResource(MAKEINTRESOURCE(IDC_LUAHOSTWIN32));
        eglView->setWndProc(WindowProc);
        eglView->setFrameSize(m_project.getFrameSize().width, m_project.getFrameSize().height);
        eglView->setFrameZoomFactor(m_project.getFrameScale());

        // make window actived
        m_hwnd = eglView->getHWnd();
        BringWindowToTop(m_hwnd);

        // restore window position
        const CCPoint windowOffset = m_project.getWindowOffset();
        if (windowOffset.x >= 0 || windowOffset.y >= 0)
        {
            eglView->moveWindow(windowOffset.x, windowOffset.y);
        }

        // set icon
        HICON icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LUAHOSTWIN32));
        SendMessage(m_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
        SendMessage(hwndConsole, WM_SETICON, ICON_BIG, (LPARAM)icon);

        // run game
        CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
        const vector<string> arr = m_project.getPackagePathArray();
        for (vector<string>::const_iterator it = arr.begin(); it != arr.end(); ++it)
        {
            stack->addSearchPath(it->c_str());
        }

        m_app->run();

        // cleanup
        CCScriptEngineManager::sharedManager()->removeScriptEngine();
        CCScriptEngineManager::purgeSharedManager();
        CocosDenshion::SimpleAudioEngine::end();

        delete m_app;
        m_app = NULL;
    } while (!m_exit);

    FreeConsole();
    return 0;
}