	void CoreWin32Platform::ToggleFullscreen()
	{
		// Setup styles based on windowed / fullscreen mode
		isFullscreen = !isFullscreen;

		if ( isFullscreen )
		{
			currentMode = fullscreenMode;
			GetWindowRect(hWindow, &windowPositionBeforeFullscreen);

			SetMenu( hWindow, NULL );
			SetWindowLong( hWindow, GWL_STYLE, FULLSCREEN_STYLE );
			SetWindowPos( hWindow, NULL, 0, 0, currentMode.width, currentMode.height, SWP_NOZORDER );
		} 
		else
		{
			SetWindowLong( hWindow, GWL_STYLE, WINDOWED_STYLE );

			currentMode = windowedMode;
			RECT windowedRect = GetWindowedRectForDisplayMode(currentMode);
	
			SetWindowPos( hWindow, HWND_NOTOPMOST, windowPositionBeforeFullscreen.left, windowPositionBeforeFullscreen.top, windowedRect.right - windowedRect.left, windowedRect.bottom - windowedRect.top, SWP_NOACTIVATE | SWP_SHOWWINDOW );
		}
		
		Logger::FrameworkDebug("[RenderManagerDX9] toggle mode: %d x %d isFullscreen: %d", currentMode.width, currentMode.height, isFullscreen);

		RenderManager::Instance()->ChangeDisplayMode(currentMode, isFullscreen);
		RenderManager::Instance()->Init(currentMode.width, currentMode.height);
		UIControlSystem::Instance()->SetInputScreenAreaSize(currentMode.width, currentMode.height);
		Core::Instance()->SetPhysicalScreenSize(currentMode.width, currentMode.height);
	}