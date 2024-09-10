int SDL_main_env(int argc, char **argv, char **env)
#endif
{
	char	drivername[64];
	struct main_args ma;
	SDL_Thread	*main_thread;
	int		main_ret;
	int		use_sdl_video=FALSE;
#ifdef _WIN32
	char		*driver_env=NULL;
#endif

	ma.argc=argc;
	ma.argv=argv;
	ma.enviro=env;
#ifndef _WIN32
	load_sdl_funcs(&sdl);
#endif

	if(sdl.gotfuncs) {
		use_sdl_video=TRUE;

#ifdef _WIN32
		/* Fail to windib (ie: No mouse attached) */
		if(sdl.Init(SDL_INIT_VIDEO)) {
			driver_env=getenv("SDL_VIDEODRIVER");
			if(driver_env==NULL || strcmp(driver_env,"windib")) {
				putenv("SDL_VIDEODRIVER=windib");
				WinExec(GetCommandLine(), SW_SHOWDEFAULT);
				return(0);
			}
			/* Sure ,we can't use video, but audio is still valid! */
			if(sdl.Init(0)==0)
				sdl_initialized=TRUE;
		}
		else {
			sdl_video_initialized=TRUE;
			sdl_initialized=TRUE;
		}
#else
		/*
		 * On Linux, SDL doesn't properly detect availability of the
		 * framebuffer apparently.  This results in remote connections
		 * displaying on the local framebuffer... a definate no-no.
		 * This ugly hack attempts to prevent this... of course, remote X11
		 * connections must still be allowed.
		 */
		if((!use_sdl_video) || ((getenv("REMOTEHOST")!=NULL || getenv("SSH_CLIENT")!=NULL) && getenv("DISPLAY")==NULL)) {
			/* Sure ,we can't use video, but audio is still valid! */
			if(sdl.Init(0)==0)
				sdl_initialized=TRUE;
		}
		else {
			if(sdl.Init(SDL_INIT_VIDEO)==0) {
				sdl_initialized=TRUE;
				sdl_video_initialized=TRUE;
			}
			else {
				/* Sure ,we can't use video, but audio is still valid! */
				if(sdl.Init(0)==0)
					sdl_initialized=TRUE;
			}
		}
#endif
		if(sdl_video_initialized && sdl.VideoDriverName(drivername, sizeof(drivername))!=NULL) {
			/* Unacceptable drivers */
			if((!strcmp(drivername, "caca")) || (!strcmp(drivername,"aalib")) || (!strcmp(drivername,"dummy"))) {
				sdl.QuitSubSystem(SDL_INIT_VIDEO);
				sdl_video_initialized=FALSE;
			}
			else {
				const SDL_VideoInfo *initial=sdl.GetVideoInfo();

				/* Save initial video mode */
				if(initial)
					sdl.initial_videoinfo=*initial;
				else
					memset(&sdl.initial_videoinfo, 0, sizeof(sdl.initial_videoinfo));
				sdl_video_initialized=TRUE;
			}
		}
	}
	if(sdl_video_initialized) {
		SetThreadName("SDL Main");
		atexit(sdl.Quit);
		sdl_main_sem=sdl.SDL_CreateSemaphore(0);
		sdl_exit_sem=sdl.SDL_CreateSemaphore(0);
		main_thread=sdl.CreateThread(sdl_run_main,&ma);
		sdl.SemWait(sdl_main_sem);
		if(sdl_drawing_thread!=NULL) {
			sdl_drawing_thread(NULL);
			sdl_exit_drawing_thread=NULL;
			if(!main_returned) {
				main_ret=0;
			}
		}
		sdl.SemWait(sdl_exit_sem);
		if(main_returned)
			sdl.WaitThread(main_thread, &main_ret);
	}
	else
		main_ret=XPDEV_main(argc, argv, env);
	return(main_ret);
}