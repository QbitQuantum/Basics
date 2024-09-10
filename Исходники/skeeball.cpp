/*! Initialised the airhockey game
 *
 *  @param          argc            Number of commandl-ine arguments
 *  @param          args            Command-line arguments
 *  @returns        ICRESULT        Success/failure of initialization
**/
ICRESULT SkeeBall::Init(int argc, char* args[])
{
    ICRESULT res = IC_OK;

    // Initialize SkeeBall Settings
    ProcessSettings();

    HACK_FULLSCREEN = m_Settings.bWiiMote;

#ifdef WIIMOTE
    if (m_Settings.bWiiMote)
    {
        // spawn console window and attache input/output streams
        AllocConsole();

        console = GetStdHandle(STD_OUTPUT_HANDLE);
        int hCrt = _open_osfhandle((long) console, _O_TEXT);
        FILE* hf_out = _fdopen(hCrt, "w");
        setvbuf(hf_out, NULL, _IONBF, 1);
        *stdout = *hf_out;

        HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
        hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
        FILE* hf_in = _fdopen(hCrt, "r");
        setvbuf(hf_in, NULL, _IONBF, 128);
        *stdin = *hf_in;
    }
#endif

    // create the main window
#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__)
    uint winFlags = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
    //uint winFlags = WS_CAPTION ;
    //uint winFlags = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
#elif defined __APPLE__
    uint winFlags = kWindowCloseBoxAttribute |
                    kWindowCollapseBoxAttribute |
                    kWindowStandardHandlerAttribute ;
    //uint winFlags = kWindowNoTitleBarAttribute;
#else
    uint winFlags = 0;
#endif

    icWindowDef window = {winFlags,
                          m_Settings.iScreen_x,
                          m_Settings.iScreen_y,
                          0,0,
                          "Skee Ball",
                          m_Settings.bFullscreen
                         };
    m_pMainWin = icWindow::GetWindow(window);

    // create the graphics device
    m_pGxDevice = new icGXDeviceGL();

    // check that we got the goods
    if (!m_pMainWin || !m_pGxDevice)
    {
#ifdef DEBUG_INSTALL
        MessageBoxA(0,"Failed to window or engine", "Error", 0);
#endif
        return IC_FAIL_GEN;
    }

    // initialize the graphics device
    m_pGxDevice->Init(m_pMainWin);

    //m_pGxDevice->EnableFog(m_Settings.bFog, m_Settings.fogParams);

    // Set the clear color to black
    ((icGXDeviceGL*)m_pGxDevice)->SetClearColor(icColor::BLACK);

    // show the main window
    m_pMainWin->Show();

    // initialize the sound engine
    res = m_SoundDevice.Initialize();
    if (ICEFAIL(res))
    {
#ifdef DEBUG_INSTALL
        MessageBoxA(0,"Failed to init audio device", "Error", 0);
#endif
        return res;
    }

    // Initialize the content manager
    m_Content = new icContentLoader(m_pGxDevice, &m_SoundDevice);

    icSoundParam params;
    params.bPaused = false;
    params.fPitch = 1.0f;
    params.bLoop = true;
    params.fVol = m_Settings.fMusic_vol;
    m_Content->Load("Resource/audio/01castlevania.wav",&m_BackGroundMusic);
    m_BackGroundMusic->SetParams(params);


    // start the background music
    if (m_Settings.bMusic)
        m_BackGroundMusic->Play();

    if (ICEFAIL(res))
    {
#ifdef DEBUG_INSTALL
        MessageBoxA(0,"some other shit failed", "Error", 0);
#endif
        return res;
    }

    // push the main menu (TODO, goes to gamestate right now)
    m_GameState.Init(m_Content);
    m_MainMenu.Init(m_Content);
    m_SettingsMenu.Init(m_Content);
    m_PauseMenu.Init(m_Content);
    m_LastGame.Init(m_Content);
    m_StateMachine.PushState(&m_LastGame);
    m_StateMachine.PushState(&m_MainMenu);

    // start keeping time
    m_GameTime.Elapsed();

    m_font.Initialize("Arial",24,m_Content->GetDevice());

    playing = true;

#ifdef WIIMOTE
    if (m_Settings.bWiiMote)
    {
        icThreadCreate<SkeeBall>(this,&SkeeBall::WiiMoteLoop,NULL,&m_pthread);
    }
#endif

    if (!ICEFAIL(res))
        return icApplication::Init(argc,args);


    return res;
}// END FUNCTION Init(int argc, char* args[])