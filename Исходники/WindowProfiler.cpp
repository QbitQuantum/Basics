  int WindowProfiler::run
  (
   const std::string& title,
   int argc, const char** argv, 
   int width, int height,
   int Major, int Minor
   )
  {
    s_project = this;

    sysVisibleConsole();

#if _WIN32
    if (m_singleThreaded)
    {
      HANDLE proc = GetCurrentProcess();
      size_t procmask;
      size_t sysmask;
      // pin to one physical cpu for smoother timings, disable hyperthreading
      GetProcessAffinityMask(proc,(PDWORD_PTR)&procmask,(PDWORD_PTR)&sysmask);
      if (sysmask & 8){
        // quadcore, use last core
        procmask = 8;
      }
      else if (sysmask & 2){
        // dualcore, use last core
        procmask = 2;
      }
      SetProcessAffinityMask(proc,(DWORD_PTR)procmask);
    }
#endif

    bool vsyncstate = true;
    unsigned int intervalSeconds = 2;
    unsigned int frameLimit = 0;
    unsigned int timerLimit = 0;
    const char* dumpatexit = NULL;

    for (int i = 0; i < argc; i++){
      if (strcmp(argv[i],"-winsize") == 0 && i + 2 < argc){
        width  = atoi(argv[i+1]);
        height = atoi(argv[i+2]);
        i+=2;
      }
      if (strcmp(argv[i],"-vsync") == 0 && i + 1 < argc){
        vsyncstate = atoi(argv[i+1]) ? true : false;
        i+=1;
      }
      if (strcmp(argv[i],"-frames")==0 && i+1<argc){
        frameLimit = atoi(argv[i+1]);
        i++;
      }
      if (strcmp(argv[i],"-timerprints")==0 && i+1<argc){
        timerLimit = atoi(argv[i+1]);
        i++;
      }
      if (strcmp(argv[i],"-timerinterval")==0 && i+1<argc){
        intervalSeconds = atoi(argv[i+1]);
        i++;
      }
      if (strcmp(argv[i],"-bmpatexit")==0 && i+1<argc){
        dumpatexit = argv[i+1];
        i++;
      }
    }

    ContextFlags flags;
    flags.major = Major;
    flags.minor = Minor;
    flags.robust = 0;
    flags.core  = 0;
#ifdef NDEBUG
    flags.debug = 0;
#else
    flags.debug = 1;
#endif
    flags.share = NULL;

    if (!activate(width,height,title.c_str(), &flags)){
      printf("Could not create GL context: %d.%d\n",flags.major,flags.minor);
      return EXIT_FAILURE;
    }

    vsync( vsyncstate );

    m_window.m_viewsize[0] = width;
    m_window.m_viewsize[1] = height;

    m_profiler.init();
    m_gltimers.init(m_profiler.getRequiredTimers());
    m_profiler.setDefaultGPUInterface(&m_gltimers);

    bool Run = begin();
    m_active = true;

    double timeStart = sysGetTime();
    double timeBegin = sysGetTime();
    double frames = 0;

    bool   lastVsync = m_vsync;

    if(Run)
    {
      while(true)
      {
        if (!NVPWindow::sysPollEvents(false)){
          break;
        }

        while ( !isOpen() ){
          NVPWindow::sysWaitEvents();
        }

        if (m_window.onPress(KEY_V)){
          vsync(!m_vsync);
        }
        
        std::string stats;
        {
          nv_helpers::Profiler::FrameHelper helper(m_profiler,sysGetTime(), float(intervalSeconds), stats);
          {
            NV_PROFILE_SECTION("Frame");
            think(sysGetTime() - timeStart);
          }
          memset(m_window.m_keyToggled, 0, sizeof(m_window.m_keyToggled)); 
          if( m_doSwap )
          {
            swapBuffers();
          }
        }
        if (m_profilerPrint && !stats.empty()){
          if (!timerLimit || timerLimit == 1){
            fprintf(stdout,"%s\n",stats.c_str());
          }
          if (timerLimit == 1){
            frameLimit = 1;
          }
          if (timerLimit){
            timerLimit--;
          }
        }

        frames++;

        double timeCurrent = sysGetTime();
        double timeDelta = timeCurrent - timeBegin;
        if (timeDelta > double(intervalSeconds) || lastVsync != m_vsync || frameLimit==1){
          std::ostringstream combined; 

          if (lastVsync != m_vsync){
            timeDelta = 0;
          }

          if (m_timeInTitle) {
            combined << title << ": " << (timeDelta*1000.0/(frames)) << " [ms]" << (m_vsync ? " (vsync on - V for toggle)" : "");
            setTitle(combined.str().c_str());
          }

          if (frameLimit==1){
            fprintf(stdout,"frametime: %f ms\n", (timeDelta*1000.0/(frames)));
          }

          frames = 0;
          timeBegin = timeCurrent;
          lastVsync = m_vsync;
        }

        if(m_window.m_keyPressed[KEY_ESCAPE] || frameLimit==1)
          break;

        if (frameLimit) frameLimit--;
      }
    }

    if (dumpatexit){
      dumpScreenshot(dumpatexit,m_window.m_viewsize[0],m_window.m_viewsize[1]);
    }

    end();
    m_active = false;

    m_profiler.deinit();
    m_gltimers.deinit();

    return Run ? EXIT_SUCCESS : EXIT_FAILURE;
  }