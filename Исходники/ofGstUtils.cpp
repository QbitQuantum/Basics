ofGstUtils::ofGstUtils() {
	bLoaded 					= false;
	speed 						= 1;
	bPaused						= false;
	bIsMovieDone				= false;
	bPlaying					= false;
	loopMode					= OF_LOOP_NONE;
	bFrameByFrame 				= false;

	gstPipeline					= NULL;
	gstSink						= NULL;

	durationNanos				= 0;

	isAppSink					= false;
	isStream					= false;

	appsink						= NULL;
	closing 					= false;

	busWatchID					= 0;

#if GLIB_MINOR_VERSION<32
	if(!g_thread_supported()){
		g_thread_init(NULL);
	}
#endif

	if(!gst_inited){
#ifdef TARGET_WIN32
		string gst_path = g_getenv("GSTREAMER_1_0_ROOT_X86");
		//putenv(("GST_PLUGIN_PATH_1_0=" + ofFilePath::join(gst_path, "lib\\gstreamer-1.0") + ";.").c_str());
		// to make it compatible with gcc and C++11 standard
		SetEnvironmentVariableA("GST_PLUGIN_PATH_1_0", ofFilePath::join(gst_path, "lib\\gstreamer-1.0").c_str());
#endif
		gst_init (NULL, NULL);
		gst_inited=true;
		ofLogVerbose("ofGstUtils") << "gstreamer inited";
	}
	if(!plugin_registered){
		gst_plugin_register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR,
					"appsink", (char*)"Element application sink",
					appsink_plugin_init, "0.1", "LGPL", "ofVideoPlayer", "openFrameworks",
					"http://openframeworks.cc/");
		plugin_registered=true;
	}

}