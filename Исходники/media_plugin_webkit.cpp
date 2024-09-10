    bool initBrowser()
    {
        // already initialized
        if ( mInitState > INIT_STATE_UNINITIALIZED )
            return true;

        // set up directories
        char cwd[ FILENAME_MAX ];	// I *think* this is defined on all platforms we use
        if (NULL == getcwd( cwd, FILENAME_MAX - 1 ))
        {
            llwarns << "Couldn't get cwd - probably too long - failing to init." << llendl;
            return false;
        }
        std::string application_dir = std::string( cwd );

#if LL_LINUX
        // take care to initialize glib properly, because some
        // versions of Qt don't, and we indirectly need it for (some
        // versions of) Flash to not crash the browser.
        if (!g_thread_supported ()) g_thread_init (NULL);
        g_type_init();
#endif

#if LL_DARWIN
        // When running under the Xcode debugger, there's a setting called "Break on Debugger()/DebugStr()" which defaults to being turned on.
        // This causes the environment variable USERBREAK to be set to 1, which causes these legacy calls to break into the debugger.
        // This wouldn't cause any problems except for the fact that the current release version of the Flash plugin has a call to Debugger() in it
        // which gets hit when the plugin is probed by webkit.
        // Unsetting the environment variable here works around this issue.
        unsetenv("USERBREAK");
#endif

#if LL_WINDOWS
        //*NOTE:Mani - On windows, at least, the component path is the
        // location of this dll's image file.
        std::string component_dir;
        char dll_path[_MAX_PATH];
        DWORD len = GetModuleFileNameA(gModuleHandle, (LPCH)&dll_path, _MAX_PATH);
        while(len && dll_path[ len ] != ('\\') )
        {
            len--;
        }
        if(len >= 0)
        {
            dll_path[len] = 0;
            component_dir = dll_path;
        }
        else
        {
            // *NOTE:Mani - This case should be an rare exception.
            // GetModuleFileNameA should always give you a full path, no?
            component_dir = application_dir;
        }
#else
        std::string component_dir = application_dir;
#endif

        // window handle - needed on Windows and must be app window.
#if LL_WINDOWS
        char window_title[ MAX_PATH ];
        GetConsoleTitleA( window_title, MAX_PATH );
        void* native_window_handle = (void*)FindWindowA( NULL, window_title );
#else
        void* native_window_handle = 0;
#endif

        // main browser initialization
        bool result = LLQtWebKit::getInstance()->init( application_dir, component_dir, mProfileDir, native_window_handle );
        if ( result )
        {
            mInitState = INIT_STATE_INITIALIZED;

            return true;
        };

        return false;
    };