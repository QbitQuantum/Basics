int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
    CONTEXT("WinMain()");

    BOOL any_desktop_running = IsAnyDesktopRunning();

    BOOL startup_desktop;

    // strip extended options from the front of the command line
    String ext_options;

    while(*lpCmdLine == '-') {
        while(*lpCmdLine && !_istspace((unsigned)*lpCmdLine))
            ext_options += *lpCmdLine++;

        while(_istspace((unsigned)*lpCmdLine))
            ++lpCmdLine;
    }

     // command line option "-install" to replace previous shell application with ROS Explorer
    if (_tcsstr(ext_options,TEXT("-install"))) {
        // install ROS Explorer into the registry
        TCHAR path[MAX_PATH];

        int l = GetModuleFileName(0, path, COUNTOF(path));
        if (l) {
            HKEY hkey;

            if (!RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), &hkey)) {

                ///@todo save previous shell application in config file

                RegSetValueEx(hkey, TEXT("Shell"), 0, REG_SZ, (LPBYTE)path, l*sizeof(TCHAR));
                RegCloseKey(hkey);
            }

            if (!RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), &hkey)) {

                ///@todo save previous shell application in config file

                RegSetValueEx(hkey, TEXT("Shell"), 0, REG_SZ, (LPBYTE)TEXT(""), l*sizeof(TCHAR));
                RegCloseKey(hkey);
            }
        }

        HWND shellWindow = GetShellWindow();

        if (shellWindow) {
            DWORD pid;

            // terminate shell process for NT like systems
            GetWindowThreadProcessId(shellWindow, &pid);
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

             // On Win 9x it's sufficient to destroy the shell window.
            DestroyWindow(shellWindow);

            if (TerminateProcess(hProcess, 0))
                WaitForSingleObject(hProcess, INFINITE);

            CloseHandle(hProcess);
        }

        startup_desktop = TRUE;
    } else {
         // create desktop window and task bar only, if there is no other shell and we are
         // the first explorer instance
         // MS Explorer looks additionally into the registry entry HKCU\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\shell,
         // to decide wether it is currently configured as shell application.
        startup_desktop = !any_desktop_running;
    }


    bool autostart = !any_desktop_running;

    // disable autostart if the SHIFT key is pressed
    if (GetAsyncKeyState(VK_SHIFT) < 0)
        autostart = false;

#ifdef _DEBUG    //MF: disabled for debugging
    autostart = false;
#endif

    // If there is given the command line option "-desktop", create desktop window anyways
    if (_tcsstr(ext_options,TEXT("-desktop")))
        startup_desktop = TRUE;
#ifndef ROSSHELL
    else if (_tcsstr(ext_options,TEXT("-nodesktop")))
        startup_desktop = FALSE;

    // Don't display cabinet window in desktop mode
    if (startup_desktop && !_tcsstr(ext_options,TEXT("-explorer")))
        nShowCmd = SW_HIDE;
#endif

    if (_tcsstr(ext_options,TEXT("-noautostart")))
        autostart = false;
    else if (_tcsstr(ext_options,TEXT("-autostart")))
        autostart = true;

#ifndef __WINE__
    if (_tcsstr(ext_options,TEXT("-console"))) {
        AllocConsole();

        _dup2(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_RDONLY), 0);
        _dup2(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), 0), 1);
        _dup2(_open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), 0), 2);

        g_Globals._log = _fdopen(1, "w");
        setvbuf(g_Globals._log, 0, _IONBF, 0);

        LOG(TEXT("starting explorer debug log\n"));
    }
#endif


    if (startup_desktop) {
         // hide the XP login screen (Credit to Nicolas Escuder)
         // another undocumented event: "Global\\msgina: ReturnToWelcome"
        if (!SetShellReadyEvent(TEXT("msgina: ShellReadyEvent")))
            SetShellReadyEvent(TEXT("Global\\msgina: ShellReadyEvent"));
    }
#ifdef ROSSHELL
    else
        return 0;    // no shell to launch, so exit immediatelly
#endif


    if (!any_desktop_running) {
        // launch the shell DDE server
        if (g_SHDOCVW_ShellDDEInit)
            (*g_SHDOCVW_ShellDDEInit)(TRUE);
    }


    bool use_gdb_stub = false;    // !IsDebuggerPresent();

    if (_tcsstr(ext_options,TEXT("-debug")))
        use_gdb_stub = true;

    if (_tcsstr(ext_options,TEXT("-break"))) {
        LOG(TEXT("debugger breakpoint"));
        __debugbreak();
    }

#ifdef _M_IX86
    // activate GDB remote debugging stub if no other debugger is running
    if (use_gdb_stub) {
        LOG(TEXT("waiting for debugger connection...\n"));

        initialize_gdb_stub();
    }
#endif

    g_Globals.init(hInstance);

    // initialize COM and OLE before creating the desktop window
    OleInit usingCOM;

    // init common controls library
    CommonControlInit usingCmnCtrl;

    g_Globals.read_persistent();

    if (startup_desktop) {
        WaitCursor wait;

        g_Globals._desktops.init();

        g_Globals._hwndDesktop = DesktopWindow::Create();
#ifdef _USE_HDESK
        g_Globals._desktops.get_current_Desktop()->_hwndDesktop = g_Globals._hwndDesktop;
#endif
    }

    if (_tcsstr(ext_options,TEXT("-?"))) {
        MessageBoxA(g_Globals._hwndDesktop,
            "/e        open cabinet window in explorer mode\r\n"
            "/root        open cabinet window in rooted mode\r\n"
            "/mdi        open cabinet window in MDI mode\r\n"
            "/sdi        open cabinet window in SDI mode\r\n"
            "\r\n"
            "-?        display command line options\r\n"
            "\r\n"
            "-desktop        start in desktop mode regardless of an already running shell\r\n"
            "-nodesktop    disable desktop mode\r\n"
            "-explorer        display cabinet window regardless of enabled desktop mode\r\n"
            "\r\n"
            "-install        replace previous shell application with ROS Explorer\r\n"
            "\r\n"
            "-noautostart    disable autostarts\r\n"
            "-autostart    enable autostarts regardless of debug build\r\n"
            "\r\n"
            "-console        open debug console\r\n"
            "\r\n"
            "-debug        activate GDB remote debugging stub\r\n"
            "-break        activate debugger breakpoint\r\n",
            "ROS Explorer - command line options", MB_OK);
    }

    Thread* pSSOThread = NULL;

    if (startup_desktop) {
        // launch SSO thread to allow message processing independent from the explorer main thread
        pSSOThread = new SSOThread;
        pSSOThread->Start();
    }

    /**TODO launching autostart programs can be moved into a background thread. */
    if (autostart) {
        const char* argv[] = {"", "s"};    // call startup routine in SESSION_START mode
        startup(2, argv);
    }

#ifndef ROSSHELL
    if (g_Globals._hwndDesktop)
        g_Globals._desktop_mode = true;
#endif


    int ret = explorer_main(hInstance, lpCmdLine, nShowCmd);


    // write configuration file
    g_Globals.write_persistent();

    if (pSSOThread) {
        pSSOThread->Stop();
        delete pSSOThread;
    }

    if (!any_desktop_running) {
        // shutdown the shell DDE server
        if (g_SHDOCVW_ShellDDEInit)
            (*g_SHDOCVW_ShellDDEInit)(FALSE);
    }

    return ret;
}