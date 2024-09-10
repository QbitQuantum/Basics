void SDLStub::init(const char *title) {
	putenv((char *)"SDL_VIDEO_WINDOW_POS");
	putenv((char *)"SDL_VIDEO_CENTERED=1");

#ifdef _WIN32
	SetConsoleTitleA(title);
#endif

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_SetCaption(title, NULL);

	int x, y; 

	SDL_GetMouseState( &x,&y ); 
	SDL_ShowCursor( SDL_ENABLE ); 
	SDL_WarpMouse( x, y ); 

	memset(&input, 0, sizeof(input));
	_offscreen = (uint8_t *)malloc(SCREEN_W * SCREEN_H * 2);
	if (!_offscreen) {
		error("Unable to allocate offscreen buffer");
	}
	_fullscreen = false;
	_scaler = 1;
	prepareGfxMode();
}