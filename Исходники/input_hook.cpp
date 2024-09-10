UIOHOOK_API int hook_run(event_type _eventsToHook) {
	int status = UIOHOOK_FAILURE;
	eventsToHook = _eventsToHook;

	// Set the thread id we want to signal later.
	hook_thread_id = GetCurrentThreadId();

	// Spot check the hInst incase the library was statically linked and DllMain
	// did not receive a pointer on load.
	if (hInst == NULL) {
		logger(LOG_LEVEL_INFO,	"%s [%u]: hInst was not set by DllMain().\n",
				__FUNCTION__, __LINE__);

		HINSTANCE hInstPE = GetModuleHandle(NULL);

		if (hInstPE != NULL) {
			DllMain(hInstPE, DLL_PROCESS_ATTACH, NULL);
		}
		else {
			logger(LOG_LEVEL_ERROR,	"%s [%u]: Could not determine hInst for SetWindowsHookEx()! (%#lX)\n",
					__FUNCTION__, __LINE__, (unsigned long) GetLastError());

			status = FALSE;
		}
	}

	bool wantsAnyKeyEvents = wants_any_key_events(), wantsAnyMouseEvents = wants_any_mouse_events();
	if (!wantsAnyKeyEvents && !wantsAnyMouseEvents)
		return UIOHOOK_FAILURE;//...maybe?

	// Create the native hooks.
	if (wantsAnyKeyEvents)
		keyboard_event_hhook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook_event_proc, hInst, 0);
	if (wantsAnyMouseEvents)
		mouse_event_hhook = SetWindowsHookEx(WH_MOUSE_LL, mouse_hook_event_proc, hInst, 0);

	// Create a window event hook to listen for capture change.
	win_event_hhook = SetWinEventHook(
			EVENT_OBJECT_NAMECHANGE, EVENT_OBJECT_NAMECHANGE, 
			NULL, 
			win_hook_event_proc, 
			0, 0, 
			WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

	bool success = true;
	if (wantsAnyKeyEvents && keyboard_event_hhook == NULL)
		success = false;

	if (wantsAnyMouseEvents && mouse_event_hhook == NULL)
		success = false;

	// If we did not encounter a problem, start processing events.
	if ( success ) {
		if (win_event_hhook == NULL) {
			logger(LOG_LEVEL_WARN,	"%s [%u]: SetWinEventHook() failed!\n",
					__FUNCTION__, __LINE__);
		}

		logger(LOG_LEVEL_DEBUG,	"%s [%u]: SetWindowsHookEx() successful.\n",
				__FUNCTION__, __LINE__);

		// Check and setup modifiers.
		initialize_modifiers();

		// Set the exit status.
		status = UIOHOOK_SUCCESS;

		// Windows does not have a hook start event or callback so we need to
		// manually fake it.
		hook_start_proc();

		// Block until the thread receives an WM_QUIT request.
		MSG message;
		while (GetMessage(&message, (HWND) NULL, 0, 0) > 0) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	else {
		logger(LOG_LEVEL_ERROR,	"%s [%u]: SetWindowsHookEx() failed! (%#lX)\n",
				__FUNCTION__, __LINE__, (unsigned long) GetLastError());

		status = UIOHOOK_ERROR_SET_WINDOWS_HOOK_EX;
	}
	
	
	// Stop the event hook and any timer still running.
	if (win_event_hhook != NULL) {
		UnhookWinEvent(win_event_hhook);
		win_event_hhook = NULL;
	}

	// Destroy the native hooks.
	if (keyboard_event_hhook != NULL) {
		UnhookWindowsHookEx(keyboard_event_hhook);
		keyboard_event_hhook = NULL;
	}

	if (mouse_event_hhook != NULL) {
		UnhookWindowsHookEx(mouse_event_hhook);
		mouse_event_hhook = NULL;
	}

	// We must explicitly call the cleanup handler because Windows does not
	// provide a thread cleanup method like POSIX pthread_cleanup_push/pop.
	hook_stop_proc();

	return status;
}