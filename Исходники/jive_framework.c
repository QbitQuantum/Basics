static int jiveL_initSDL(lua_State *L) {
	const SDL_VideoInfo *video_info;
	JiveSurface *srf, *splash, *icon;
	Uint16 splash_w, splash_h;

	/* logging */
	log_ui_draw = LOG_CATEGORY_GET("jivelite.ui.draw");
	log_ui = LOG_CATEGORY_GET("jivelite.ui");

	/* linux fbcon does not need a mouse */
	SDL_putenv("SDL_NOMOUSE=1");

	/* allow the screensaver */
	SDL_putenv("SDL_VIDEO_ALLOW_SCREENSAVER=1");

	/* initialise SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG_ERROR(log_ui_draw, "SDL_Init(V|T|A): %s\n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	/* report video info */
	if ((video_info = SDL_GetVideoInfo())) {
		LOG_INFO(log_ui_draw, "%d,%d %d bits/pixel %d bytes/pixel [R<<%d G<<%d B<<%d]", video_info->current_w, video_info->current_h, video_info->vfmt->BitsPerPixel, video_info->vfmt->BytesPerPixel, video_info->vfmt->Rshift, video_info->vfmt->Gshift, video_info->vfmt->Bshift);
		LOG_INFO(log_ui_draw, "Hardware acceleration %s available", video_info->hw_available?"is":"is not");
		LOG_INFO(log_ui_draw, "Window manager %s available", video_info->wm_available?"is":"is not");
	}

	/* Register callback for additional events (used for multimedia keys)*/
	SDL_EventState(SDL_SYSWMEVENT,SDL_ENABLE);
	SDL_SetEventFilter(filter_events);

	platform_init(L);

	/* open window */
	SDL_WM_SetCaption("JiveLite Alpha", "JiveLite Alpha");
	SDL_ShowCursor(SDL_DISABLE);
	SDL_EnableKeyRepeat (100, 100);
	SDL_EnableUNICODE(1);

	/* load the icon */
	icon = jive_surface_load_image("jive/app.png");
	if (icon) {
		jive_surface_set_wm_icon(icon);
		jive_surface_free(icon);
	}

	screen_w = video_info->current_w;
	screen_h = video_info->current_h;

	screen_bpp = video_info->vfmt->BitsPerPixel;

	splash = jive_surface_load_image("jive/splash.png");
	if (splash) {
		jive_surface_get_size(splash, &splash_w, &splash_h);
		if (video_info->wm_available) {
			screen_w = splash_w;
			screen_h = splash_h;
		}
	}

	srf = jive_surface_set_video_mode(screen_w, screen_h, screen_bpp, video_info->wm_available ? false : true);
	if (!srf) {
		SDL_Quit();
		exit(-1);
	}

	if (splash) {
		jive_surface_blit(splash, srf, MAX(0, (screen_w - splash_w) / 2), MAX(0, (screen_h - splash_h) / 2));
		jive_surface_flip(srf);
	}

	lua_getfield(L, 1, "screen");
	if (lua_isnil(L, -1)) {
		LOG_ERROR(log_ui_draw, "no screen table");

		SDL_Quit();
		exit(-1);
	}

	/* store screen surface */
	JiveSurface **p = (JiveSurface **)lua_newuserdata(L, sizeof(JiveSurface *));
	*p = jive_surface_ref(srf);
	luaL_getmetatable(L, "JiveSurface");
	lua_setmetatable(L, -2);

	lua_setfield(L, -2, "surface");

	lua_getfield(L, -1, "bounds");
	lua_pushinteger(L, screen_w);
	lua_rawseti(L, -2, 3);
	lua_pushinteger(L, screen_h);
	lua_rawseti(L, -2, 4);
	lua_pop(L, 2);

	/* background image */
	jive_background = jive_tile_fill_color(0x000000FF);

	/* jive.ui.style = {} */
	lua_getglobal(L, "jive");
	lua_getfield(L, -1, "ui");
	lua_newtable(L);
	lua_setfield(L, -2, "style");
	lua_pop(L, 2);

	return 0;
}