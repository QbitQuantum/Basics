	/**
	 * Destroys the window and its associated properties.  Be careful calling this if
	 * the window is already destroyed by the user!
	 */
	void Window::destroy()
	{
		// Check whether the window is fullscreen or not.
		if (this->isFullscreen)
		{
			// Change the display settings for the window to not be full screen.
			if (ChangeDisplaySettings(NULL, 0) != DISP_CHANGE_SUCCESSFUL)
			{
#ifdef _DEBUG
				// If debugging, display an error indicating where the program failed.
				MessageBox(NULL, (LPCWSTR)L"Changing display from fullscreen failed!", (LPCWSTR)L"Window Destroy ERROR", MB_OK | MB_ICONERROR);
#else
				// If not debugging, display a nice error code to reference for the user.
				MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: WD" + FULLSCREEN_ERROR, (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
				// Make sure that the cursor is shown finally too.
				ShowCursor(true);
			}

			// Set the fullscreen boolean to false.
			this->isFullscreen = false;

			//		// Check if there is a device context and attempt to release it.
			//		if(deviceContext && !deviceContext->unused && !ReleaseDC(windowHandle, deviceContext))
			//		{
			//#ifdef _DEBUG
			//			// If debugging, display an error indicating that the device context couldn't be released.
			//			MessageBox(NULL, (LPCWSTR)L"Error releasing device context!", (LPCWSTR)L"Window Destroy ERROR", MB_OK | MB_ICONERROR);
			//#else
			//			// Display a nice error for the user if not debugging.
			//			MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: WD" + DC_RELEASE_ERROR, (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
			//#endif
			//			// Set the device context to NULL.
			//			deviceContext = NULL;
			//		}
			//		// Check if there is a window handle and attempt to destroy the window associated with it.
			//		if(windowHandle && !windowHandle->unused && !DestroyWindow(windowHandle))
			//		{
			//#ifdef _DEBUG
			//			// If debugging, display an error indicating that the window handle couldn't be destroyed.
			//			MessageBox(NULL, (LPCWSTR)L"Error destroying window handle!", (LPCWSTR)L"Window Destroy ERROR", MB_OK | MB_ICONERROR);
			//#else
			//			// Display a nice error to the user if not debugging.
			//			MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: WD" + WH_DESTROY_ERROR, (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
			//#endif
			//			// Set the window handle to NULL.
			//			windowHandle = NULL;
			//		}
			//		// Attempt to unregister the title associated with the window.
			//		if(!UnregisterClass(this->title, appInstance))
			//		{
			//#ifdef _DEBUG
			//			// If debugging, display  an error indicating that the window class could not be unregistered.
			//			MessageBox(NULL, (LPCWSTR)L"Error unregistering class!", (LPCWSTR)L"Window Destroy ERROR", MB_OK | MB_ICONERROR);
			//#else
			//			// Display a nice error to the user if not debugging.
			//			MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: WD" + WC_UNREGISTER_ERROR, (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
			//#endif
			//			// Set the applications instance handle to NULL.
			//			appInstance = NULL;
			//		}
		}
	}