EXTERN_C LONG WINAPI ScreenSaverProc(
	HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static HDC		hDC = NULL;	// Private GDI Device Context
	static HGLRC	hRC = NULL;	// Permanent Rendering Context
	static int		nState;
	static int		nFrames;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_CREATE:
		{
		// Load settings
		CCuckooSettings	settings;
		settings.Load();

		// Load clock
		switch (settings.GetClockType())
		{
		case 2:		// Mickey
			g_pClock = new CClockMickey;
			break;
		case 1:		// Wesminster
			g_pClock = new CClockWestminster;
			break;
		case 0:		// Cuckoo
			g_pClock = new CClockCuckoo;
			break;
		default:	// Error
			MessageBox(hWnd, _T("Unknown clock: Please configure the screen saver.\n\nHorloge inconnue: Veuillez reconfigurer l'écran de veille."), _T("Cuckoo"), MB_ICONEXCLAMATION);
			return -1;
		}
		if (g_pClock == NULL)
		{
			MessageBox(hWnd, _T("Not enought memory to load the clock."), _T("Cuckoo"), MB_ICONERROR);
			return -1;
		}

		// Initialize OpenGL on hWnd.
		if (!CreateGLWindow(hWnd, &hDC, &hRC))
			return -1;

		// Starting state
		nState = STATE_SWAP_TEST;

		// Set timers
		SetTimer(hWnd, 1, 10, NULL);
		return 0;
		}

	case WM_DESTROY:
		// Timers
		KillTimer(hWnd, 1);
		// Clock
		if (g_pClock != NULL)
		{
			delete g_pClock;
			g_pClock = NULL;
		}
		// OpenGL
		KillGLWindow(hWnd, hDC, hRC);
		return 0;

	case WM_TIMER:
		switch (nState)
		{
		case STATE_SWAP_TEST:
			// Check if SwapBuffers() swap or copy back to front
			if (IsSwapBufferCopyingBackToFront(hDC))
				g_pClock->SetSwapBufferMode(CClock::COPY_BACK_TO_FRONT);
			else
				g_pClock->SetSwapBufferMode(CClock::SWAP_BACK_AND_FRONT);
			nState++;
			break;

		case STATE_INIT_CLOCK:
			{
			// Load settings
			CCuckooSettings	settings;
			settings.Load();

			// Clock
			g_pClock->EnableSounds(settings.HasTicTacSound(), settings.BellsOnHours(), settings.BellsOnHalfHours(), settings.BellsOnQuartHours());
			g_pClock->Init();

			// Precise timing
			g_swTimer.Init();
			g_swTimer.Start();

			// Frame counter
			nFrames = 0;

			nState++;
			break;
			}

		case STATE_RENDER:
			// Met à jour l'heure
			if (++nFrames > 4)
			{
				nFrames = 0;
				g_pClock->UpdateTime();
			}

			// Affiche la scène
			DrawGLScene();
			glFlush();
			SwapBuffers(hDC);
			break;
		}
		return 0;

	case WM_SYSCOMMAND:
		if (wParam == SC_MONITORPOWER)
		{
			// Load settings
			CCuckooSettings	settings;
			settings.Load();
			if (settings.IsDisabledOnMonitorTurnOff())
				PostQuitMessage(0);
		}
	}

	// Pass All Unhandled Messages To DefScreenSaverProc
	return DefScreenSaverProc(hWnd, uMsg, wParam, lParam);
}