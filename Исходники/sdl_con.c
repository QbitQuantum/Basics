/* Called from main thread only (Passes Event) */
int sdl_init(int mode)
{
#if !defined(NO_X) && defined(__unix__)
	dll_handle	dl;
	const char *libnames[2]={"X11", NULL};
#endif

	if(init_sdl_video()) {
		fprintf(stderr, "SDL Video Init Failed\n");
		return(-1);
	}

	bitmap_init(sdl_drawrect, sdl_flush);

	if(mode==CIOLIB_MODE_SDL_FULLSCREEN)
		fullscreen=1;
	if(mode==CIOLIB_MODE_SDL_YUV)
		yuv.enabled=1;
	if(mode==CIOLIB_MODE_SDL_YUV_FULLSCREEN) {
		yuv.enabled=1;
		fullscreen=1;
	}
#if (SDL_MAJOR_VERSION > 1) || (SDL_MINOR_VERSION > 2) || (SDL_PATCHLEVEL > 9)
	if(yuv.enabled) {
		const SDL_version	*linked=sdl.Linked_Version();
		if(linked->major > 1 || linked->minor > 2 || linked->patch > 9) {
			yuv.screen_width=sdl.initial_videoinfo.current_w;
			yuv.screen_height=sdl.initial_videoinfo.current_h;
		}
	}
#endif
	sdl_init_mode(3);
	if(yuv.enabled && yuv.overlay==NULL) {
		fprintf(stderr, "YUV Enabled, but overlay is NULL\n");
		sdl_init_good=0;
	}
	sdl_user_func_ret(SDL_USEREVENT_INIT);

	if(sdl_init_good) {
		cio_api.mode=fullscreen?CIOLIB_MODE_SDL_FULLSCREEN:CIOLIB_MODE_SDL;
#ifdef _WIN32
		FreeConsole();
#endif
#if !defined(NO_X) && defined(__unix__)
		dl=xp_dlopen(libnames,RTLD_LAZY|RTLD_GLOBAL,7);
		if(dl!=NULL) {
			sdl_x11available=TRUE;
			if(sdl_x11available && (sdl_x11.XFree=xp_dlsym(dl,XFree))==NULL) {
				xp_dlclose(dl);
				sdl_x11available=FALSE;
			}
			if(sdl_x11available && (sdl_x11.XGetSelectionOwner=xp_dlsym(dl,XGetSelectionOwner))==NULL) {
				xp_dlclose(dl);
				sdl_x11available=FALSE;
			}
			if(sdl_x11available && (sdl_x11.XConvertSelection=xp_dlsym(dl,XConvertSelection))==NULL) {
				xp_dlclose(dl);
				sdl_x11available=FALSE;
			}
			if(sdl_x11available && (sdl_x11.XGetWindowProperty=xp_dlsym(dl,XGetWindowProperty))==NULL) {
				xp_dlclose(dl);
				sdl_x11available=FALSE;
			}
			if(sdl_x11available && (sdl_x11.XChangeProperty=xp_dlsym(dl,XChangeProperty))==NULL) {
				xp_dlclose(dl);
				sdl_x11available=FALSE;
			}
			if(sdl_x11available && (sdl_x11.XSendEvent=xp_dlsym(dl,XSendEvent))==NULL) {
				xp_dlclose(dl);
				sdl_x11available=FALSE;
			}
			if(sdl_x11available && (sdl_x11.XSetSelectionOwner=xp_dlsym(dl,XSetSelectionOwner))==NULL) {
				xp_dlclose(dl);
				sdl_x11available=FALSE;
			}
		}
		if(sdl_x11available)
			sdl.EventState(SDL_SYSWMEVENT, SDL_ENABLE);
#endif
		return(0);
	}

	return(-1);
}