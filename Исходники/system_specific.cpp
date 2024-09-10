//drag and drop support, call after window was initialized
void system_window_init(){

	//drag and drop
	#if TARGET_OS == WIN
		SDL_SysWMinfo wmInfo;

		//set SDL version to WMinfo struct
		//-> maybe problems when not calling this macro before
		SDL_VERSION(&wmInfo.version);  

		if(SDL_GetWMInfo(&wmInfo) != SDL_TRUE) {
			cerr << "Error on getting WMInfo" << endl;
			return;
		}

		SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
		DragAcceptFiles(wmInfo.window, true); //afxwin.h
	#endif
	
	//other OS ...
}