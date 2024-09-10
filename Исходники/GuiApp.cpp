  GuiApp::~GuiApp() {

    //! close simulation
    exit_main(0);

    libManager->releaseLibrary("cfg_manager");
    libManager->releaseLibrary("lib_manager_gui");
    libManager->releaseLibrary("main_gui");

    libManager->clearLibraries();
    delete libManager;


#ifdef WIN32
    // end scheduler of 1ms
    timeEndPeriod(1);
#endif //WIN32

  }