const char *MusicDriver_DMusic::Start(const char * const *parm)
{
	if (performance != NULL) return NULL;

	if (proc.CoCreateInstance == NULL) {
		if (!LoadLibraryList((Function*)&proc, ole_files)) {
			return "ole32.dll load failed";
		}
	}

	/* Initialize COM */
	if (FAILED(proc.CoInitialize(NULL))) {
		return "COM initialization failed";
	}

	/* create the performance object */
	if (FAILED(proc.CoCreateInstance(
				CLSID_DirectMusicPerformance,
				NULL,
				CLSCTX_INPROC,
				IID_IDirectMusicPerformance,
				(LPVOID*)&performance
			))) {
		proc.CoUninitialize();
		return "Failed to create the performance object";
	}

	/* initialize it */
	if (FAILED(performance->Init(NULL, NULL, NULL))) {
		performance->Release();
		performance = NULL;
		proc.CoUninitialize();
		return "Failed to initialize performance object";
	}

	/* choose default Windows synth */
	if (FAILED(performance->AddPort(NULL))) {
		performance->CloseDown();
		performance->Release();
		performance = NULL;
		proc.CoUninitialize();
		return "AddPort failed";
	}

	/* create the loader object; this will be used to load the MIDI file */
	if (FAILED(proc.CoCreateInstance(
				CLSID_DirectMusicLoader,
				NULL,
				CLSCTX_INPROC,
				IID_IDirectMusicLoader,
				(LPVOID*)&loader
			))) {
		performance->CloseDown();
		performance->Release();
		performance = NULL;
		proc.CoUninitialize();
		return "Failed to create loader object";
	}

	return NULL;
}