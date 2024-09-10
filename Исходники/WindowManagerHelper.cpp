int GetWindowState(SDL_Window* window)
{
	int state = 0;
#ifndef HEADLESS
	WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);

	struct SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDL_GetWindowWMInfo(window, &info);

	if (GetWindowPlacement(info.info.win.window, &wp)) {
		if (wp.showCmd == SW_SHOWMAXIMIZED)
			state = SDL_WINDOW_MAXIMIZED;
		if (wp.showCmd == SW_SHOWMINIMIZED)
			state = SDL_WINDOW_MINIMIZED;
	}
#endif
	return state;
}