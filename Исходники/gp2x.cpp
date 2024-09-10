void OSystem_GP2X::initBackend() {
	// Setup default save path to be workingdir/saves
	char savePath[PATH_MAX + 1];
	char workDirName[PATH_MAX + 1];

	if (getcwd(workDirName, PATH_MAX) == NULL) {
		error("Could not obtain current working directory");
	} else {
		printf("Current working directory: %s\n", workDirName);
	}

	strcpy(savePath, workDirName);
	strcat(savePath, "/saves");
	printf("Current save directory: %s\n", savePath);
	struct stat sb;
	if (stat(savePath, &sb) == -1)
		if (errno == ENOENT) // Create the dir if it does not exist
			if (mkdir(savePath, 0755) != 0)
				warning("mkdir for '%s' failed", savePath);

	ConfMan.registerDefault("savepath", savePath);

	#ifdef DUMP_STDOUT
		// The GP2X has a serial console but most users do not use this so we
		// output all our STDOUT and STDERR to files for debug purposes.
		char STDOUT_FILE[PATH_MAX + 1];
		char STDERR_FILE[PATH_MAX + 1];

		strcpy(STDOUT_FILE, workDirName);
		strcpy(STDERR_FILE, workDirName);
		strcat(STDOUT_FILE, "/scummvm.stdout.txt");
		strcat(STDERR_FILE, "/scummvm.stderr.txt");

		/* Flush the output in case anything is queued */
		fclose(stdout);
		fclose(stderr);

		/* Redirect standard input and standard output */
		FILE *newfp = freopen(STDOUT_FILE, "w", stdout);
		if (newfp == NULL) {
		#if !defined(stdout)
			stdout = fopen(STDOUT_FILE, "w");
		#else
			newfp = fopen(STDOUT_FILE, "w");
			if (newfp) {
				*stdout = *newfp;
			}
		#endif
		}

		newfp = freopen(STDERR_FILE, "w", stderr);
		if (newfp == NULL) {
		#if !defined(stderr)
			stderr = fopen(STDERR_FILE, "w");
		#else
			newfp = fopen(STDERR_FILE, "w");
			if (newfp) {
				*stderr = *newfp;
			}
		#endif
		}

		setbuf(stderr, NULL);
		printf("%s\n", "Debug: STDOUT and STDERR redirected to text files.");
	#endif /* DUMP_STDOUT */

	// Setup other defaults.
	ConfMan.registerDefault("aspect_ratio", true);

	/* Up default volume values as we use a seperate system level volume anyway. */
	ConfMan.registerDefault("music_volume", 192);
	ConfMan.registerDefault("sfx_volume", 192);
	ConfMan.registerDefault("speech_volume", 192);
	ConfMan.registerDefault("autosave_period", 3 * 60);	// Trigger autosave every 3 minutes - On low batts 4 mins is about your warning time.

	ConfMan.setBool("FM_low_quality", true);

	/* Initialize any GP2X specific stuff we may want (Batt Status, scaler etc.) */
	GP2X_HW::deviceInit();

	/* Set Default hardware mixer volume to a preset level (VOLUME_INITIAL). This is done to 'reset' volume level if set by other apps. */
	GP2X_HW::mixerMoveVolume(0);

	// Create the events manager
	if (_eventSource == 0)
		_eventSource = new GP2XSdlEventSource();

	// Create the graphics manager
	if (_graphicsManager == 0)
		_graphicsManager = new GP2XSdlGraphicsManager(_eventSource);

	/* Pass to POSIX method to do the heavy lifting */
	OSystem_POSIX::initBackend();
}