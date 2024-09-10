void OSystem_SDL::init() {
    // Initialize SDL
    initSDL();

    if (!_logger)
        _logger = new Backends::Log::Log(this);

    if (_logger) {
        Common::WriteStream *logFile = createLogFile();
        if (logFile)
            _logger->open(logFile);
    }


    // Creates the early needed managers, if they don't exist yet
    // (we check for this to allow subclasses to provide their own).
    if (_mutexManager == 0)
        _mutexManager = new SdlMutexManager();

    if (_timerManager == 0)
        _timerManager = new SdlTimerManager();

#ifdef USE_OPENGL
    // Setup a list with both SDL and OpenGL graphics modes
    setupGraphicsModes();
#endif
}