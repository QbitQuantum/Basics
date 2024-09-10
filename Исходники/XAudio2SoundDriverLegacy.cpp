BOOL XAudio2SoundDriverLegacy::Setup()
{
	if (dllInitialized == true) return true;
	dllInitialized = true;
	bufferLength[0] = bufferLength[1] = bufferLength[2] = bufferLength[3] = bufferLength[4] = bufferLength[5] = 0;
	bufferLength[6] = bufferLength[7] = bufferLength[8] = bufferLength[9] = 0;
	audioIsPlaying = false;
	writeBuffer = 0;
	readBuffer = 0;
	filledBuffers = 0;
	bufferBytes = 0;
	lastLength = 1;

	cacheSize = 0;
	interrupts = 0;

	hMutex = CreateMutex(NULL, FALSE, NULL);
	if (FAILED(XAudio2Create(&g_engine)))
	{
		CoUninitialize();
		return -1;
	}

	if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	{
		g_engine->Release();
		CoUninitialize();
		return -2;
	}
	canPlay = true;

	// Load Wave File

	WAVEFORMATEX wfm;

	memset(&wfm, 0, sizeof(WAVEFORMATEX));

	wfm.wFormatTag = WAVE_FORMAT_PCM;
	wfm.nChannels = 2;
	wfm.nSamplesPerSec = 44100;
	wfm.wBitsPerSample = 16; // TODO: Allow 8bit audio...
	wfm.nBlockAlign = wfm.wBitsPerSample / 8 * wfm.nChannels;
	wfm.nAvgBytesPerSec = wfm.nSamplesPerSec * wfm.nBlockAlign;


	if (FAILED(g_engine->CreateSourceVoice(&g_source, &wfm, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &voiceCallback, NULL, NULL)))
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}

	g_source->Start();
	SetVolume(Configuration::getVolume());

	return FALSE;
}