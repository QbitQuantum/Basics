void setupSynchronousSignalHandlers() {
    std::set_terminate(myTerminate);
    std::set_new_handler(reportOutOfMemoryErrorAndExit);

    // SIGABRT is the only signal we want handled by signal handlers on both windows and posix.
    invariant(signal(SIGABRT, abruptQuit) != SIG_ERR);

#if defined(_WIN32)
    _set_purecall_handler(myPureCallHandler);
    _set_invalid_parameter_handler(myInvalidParameterHandler);
    setWindowsUnhandledExceptionFilter();
#else
    invariant(signal(SIGHUP, SIG_IGN) != SIG_ERR);
    invariant(signal(SIGUSR2, SIG_IGN) != SIG_ERR);
    invariant(signal(SIGPIPE, SIG_IGN) != SIG_ERR);

    struct sigaction addrSignals;
    memset(&addrSignals, 0, sizeof(struct sigaction));
    addrSignals.sa_sigaction = abruptQuitWithAddrSignal;
    sigemptyset(&addrSignals.sa_mask);
    addrSignals.sa_flags = SA_SIGINFO;

    // ^\ is the stronger ^C. Log and quit hard without waiting for cleanup.
    invariant(signal(SIGQUIT, abruptQuit) != SIG_ERR);

    invariant(sigaction(SIGSEGV, &addrSignals, 0) == 0);
    invariant(sigaction(SIGBUS, &addrSignals, 0) == 0);
    invariant(sigaction(SIGILL, &addrSignals, 0) == 0);
    invariant(sigaction(SIGFPE, &addrSignals, 0) == 0);

    setupSIGTRAPforGDB();
#endif
}