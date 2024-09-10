int DIB_CreateWindow(_THIS)
{
	char *windowid = SDL_getenv("SDL_WINDOWID");

	SDL_RegisterApp(NULL, 0, 0);

	SDL_windowid = (windowid != NULL);
	if ( SDL_windowid ) {
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
		/* wince 2.1 does not have strtol */
		wchar_t *windowid_t = SDL_malloc((SDL_strlen(windowid) + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, windowid, -1, windowid_t, SDL_strlen(windowid) + 1);
		SDL_Window = (HWND)wcstol(windowid_t, NULL, 0);
		SDL_free(windowid_t);
#else
		SDL_Window = (HWND)SDL_strtoull(windowid, NULL, 0);
#endif
		if ( SDL_Window == NULL ) {
			SDL_SetError("Couldn't get user specified window");
			return(-1);
		}

		/* DJM: we want all event's for the user specified
			window to be handled by SDL.
		 */
		userWindowProc = (WNDPROCTYPE)GetWindowLongPtr(SDL_Window, GWLP_WNDPROC);
		SetWindowLongPtr(SDL_Window, GWLP_WNDPROC, (LONG_PTR)WinMessage);
	} else {
		SDL_Window = CreateWindow(SDL_Appname, SDL_Appname,
                        (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX),
                        CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, NULL, NULL, SDL_Instance, NULL);
		if ( SDL_Window == NULL ) {
			SDL_SetError("Couldn't create window");
			return(-1);
		}
		ShowWindow(SDL_Window, SW_HIDE);
	}

	/* JC 14 Mar 2006
		Flush the message loop or this can cause big problems later
		Especially if the user decides to use dialog boxes or assert()!
	*/
	WIN_FlushMessageQueue();

	return(0);
}