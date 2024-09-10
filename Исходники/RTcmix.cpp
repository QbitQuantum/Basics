/* --------------------------------------------------------- init_globals --- */
void
RTcmix::init_globals(bool fromMain, const char *defaultDSOPath)
{
   Option::init();
   if (defaultDSOPath && defaultDSOPath[0])
      Option::dsoPathPrepend(defaultDSOPath);

   if (fromMain) {
#ifndef MAXMSP
      Option::readConfigFile(Option::rcName());
      Option::exitOnError(true); // we do this no matter what is in config file
#else
      Option::exitOnError(false);
#endif
      rtInteractive = 0;
   }
   else {
      SR = 44100.0; // what the heck...
      Option::print(0);
      Option::reportClipping(false);
   }

   RTBUFSAMPS = (int) Option::bufferFrames();  /* modifiable with rtsetparams */

   rtHeap = new heap;
   rtQueue = new RTQueue[MAXBUS*3];
#ifdef MULTI_THREAD
   taskManager = new TaskManager;
   mixVector.reserve(MAXBUS);
#endif

   for (int i = 0; i < MAXBUS; i++) {
      AuxToAuxPlayList[i] = -1; /* The playback order for AUX buses */
      ToOutPlayList[i] = -1;    /* The playback order for AUX buses */
      ToAuxPlayList[i] =-1;     /* The playback order for AUX buses */
   }

#ifdef MINGW
	max_input_fds = _getmaxstdio();
#else
	max_input_fds = sysconf(_SC_OPEN_MAX);
#endif
	if (max_input_fds == -1)	// call failed
		max_input_fds = 128;		// what we used to hardcode
	else
		max_input_fds -= RESERVE_INPUT_FDS;
	
	inputFileTable = new InputFile[max_input_fds];

   init_buf_ptrs();

   if (Option::autoLoad()) {
      const char *dsoPath = Option::dsoPath();
      if (strlen(dsoPath) == 0)
         registerDSOs(SHAREDLIBDIR);
      else
         registerDSOs(dsoPath);
   }
}