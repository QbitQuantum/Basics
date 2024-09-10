    void setupSignalHandlers() {
        set_terminate( myTerminate );
        set_new_handler( myNewHandler );

        // SIGABRT is the only signal we want handled by signal handlers on both windows and posix.
        invariant( signal(SIGABRT, abruptQuit) != SIG_ERR );

#ifdef _WIN32
        _set_purecall_handler( ::abort ); // TODO improve?
        setWindowsUnhandledExceptionFilter();
        massert(10297,
                "Couldn't register Windows Ctrl-C handler",
                SetConsoleCtrlHandler(static_cast<PHANDLER_ROUTINE>(CtrlHandler), TRUE));

#else
        invariant( signal(SIGHUP , SIG_IGN ) != SIG_ERR );
        invariant( signal(SIGUSR2, SIG_IGN ) != SIG_ERR );
        invariant( signal(SIGPIPE, SIG_IGN) != SIG_ERR );

        struct sigaction addrSignals;
        memset( &addrSignals, 0, sizeof( struct sigaction ) );
        addrSignals.sa_sigaction = abruptQuitWithAddrSignal;
        sigemptyset( &addrSignals.sa_mask );
        addrSignals.sa_flags = SA_SIGINFO;

        invariant( sigaction(SIGSEGV, &addrSignals, 0) == 0 );
        invariant( sigaction(SIGBUS, &addrSignals, 0) == 0 );
        invariant( sigaction(SIGILL, &addrSignals, 0) == 0 );
        invariant( sigaction(SIGFPE, &addrSignals, 0) == 0 );


        setupSIGTRAPforGDB();

        // asyncSignals is a global variable listing the signals that should be handled by the
        // interrupt thread, once it is started via startSignalProcessingThread().
        sigemptyset( &asyncSignals );
        sigaddset( &asyncSignals, SIGHUP );
        sigaddset( &asyncSignals, SIGINT );
        sigaddset( &asyncSignals, SIGTERM );
        sigaddset( &asyncSignals, SIGQUIT );
        sigaddset( &asyncSignals, SIGUSR1 );
        sigaddset( &asyncSignals, SIGXCPU );
#endif
    }