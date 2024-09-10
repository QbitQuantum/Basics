void ofExitCallback(){
	// controlled destruction of the mainLoop before
	// any other deinitialization
	mainLoop.reset();

	// everything should be destroyed here, except for
	// static objects


	// finish every library and subsystem
	#ifndef TARGET_EMSCRIPTEN
		ofURLFileLoaderShutdown();
	#endif

	#ifndef TARGET_NO_SOUND
		//------------------------
		// try to close engine if needed:
		ofSoundShutdown();
		//------------------------
	#endif

	// try to close quicktime, for non-linux systems:
	#if defined(OF_VIDEO_CAPTURE_QUICKTIME) || defined(OF_VIDEO_PLAYER_QUICKTIME)
	closeQuicktime();
	#endif


	//------------------------
	// try to close freeImage:
	ofCloseFreeImage();


	#ifdef WIN32_HIGH_RES_TIMING
		timeEndPeriod(1);
	#endif

	// static deinitialization happens after this finishes
	// every object should have ended by now and won't receive any
	// events
}