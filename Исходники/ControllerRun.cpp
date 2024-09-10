DWORD FAR PASCAL CController::RunController(CController* pController)
{
	if ( !pController )
		return 0;

	VARIANT_BOOL fIsSupported;
	pController->m_pGame->get_IsSupported(&fIsSupported);
	if ( fIsSupported==VARIANT_FALSE ) {
		MessageBox(pController->m_hParentWnd, "This game is not supported by Visual PinMAME", "Failed to start", MB_ICONINFORMATION|MB_OK);
		return 1;
	}

	g_fHandleMechanics = pController->m_iHandleMechanics;
	g_fHandleKeyboard  = pController->m_fHandleKeyboard;
	g_fMechSamples = pController->m_fMechSamples;

	// Load the game specific settings
	LoadGameSettings(pController->m_szROM);

	// set some options for the mamew environment
	// set_option("window", "1", 0);
	set_option("resolution", "1x1x16", 0);
	set_option("debug_resolution", "640x480x16", 0);
	set_option("maximize", "0", 0);
	set_option("throttle", "1", 0);
	set_option("sleep", "1", 0);
	set_option("autoframeskip", "0", 0);
	set_option("skip_gameinfo", "1", 0);
	set_option("skip_disclaimer", "1", 0);
	set_option("keepaspect", "0", 0);

	VARIANT fHasSound;
	VariantInit(&fHasSound);
	pController->m_pGameSettings->get_Value(CComBSTR("sound"), &fHasSound);
	if (fHasSound.boolVal==VARIANT_FALSE)
		options.samplerate = 0; // indicates game sound disabled

#ifndef DEBUG
	void* pSplashWnd = NULL;
	if(!cabinetMode)
	// display the splash screen
	CreateSplashWnd(&pSplashWnd, pController->m_szSplashInfoLine);
#endif

	// set the global pointer to Controller
	m_pController = pController;

	g_fPause = 0;

	int iSyncLevel = synclevel;
	if ( iSyncLevel<0 )
		iSyncLevel = 0;
	else if ( iSyncLevel>60 )
		iSyncLevel = 60;

	if ( iSyncLevel ) {
		if ( iSyncLevel<=20 )
			g_iSyncFactor = 1024;
		else
			g_iSyncFactor = (int) (1024.0*(iSyncLevel/60.0));

		g_hEnterThrottle = CreateEvent(NULL, false, true, NULL);
	}
#ifndef DEBUG
	else {
		// just in case
		g_iSyncFactor = 0;
		g_hEnterThrottle = INVALID_HANDLE_VALUE;

		switch ( threadpriority ) {
			case 1:
				SetThreadPriority(pController->m_hThreadRun, THREAD_PRIORITY_ABOVE_NORMAL);
				break;
			case 2:
				SetThreadPriority(pController->m_hThreadRun, THREAD_PRIORITY_HIGHEST);
				break;
		}
	}
#endif

	vpm_game_init(pController->m_nGameNo);
	run_game(pController->m_nGameNo);
	vpm_game_exit(pController->m_nGameNo);

	if ( iSyncLevel ) {
		SetEvent(g_hEnterThrottle);
		CloseHandle(g_hEnterThrottle);
		g_hEnterThrottle = INVALID_HANDLE_VALUE;
		g_iSyncFactor = 0;
	}
	else
		SetThreadPriority(pController->m_hThreadRun, THREAD_PRIORITY_NORMAL);

	// fire the OnMachineStopped event
	OnStateChange(0);

	// reset the global pointer to Controller
	m_pController = NULL;

#ifndef DEBUG
	if(!cabinetMode)
	// destroy the splash screensync
		DestroySplashWnd(&pSplashWnd); 
#endif

	return 0;
}