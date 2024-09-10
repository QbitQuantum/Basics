void CSH_XAudio2::InitializeXAudio2()
{
	HRESULT result = S_OK;

	result = CoInitializeEx(0, COINIT_MULTITHREADED);
	assert(SUCCEEDED(result));

	//Instantiate XAudio2's class factory to prevent DLL from being unloaded by COM
	//Otherwise, DllCanUnloadNow always returns S_OK (can be unloaded)
	result = CoGetClassObject(__uuidof(XAudio2), CLSCTX_INPROC_SERVER, NULL, __uuidof(IClassFactory), reinterpret_cast<void**>(&m_classFactory));
	assert(SUCCEEDED(result));

	result = XAudio2Create(&m_xaudio2);
	assert(SUCCEEDED(result));

	result = m_xaudio2->CreateMasteringVoice(&m_masteringVoice);
	assert(SUCCEEDED(result));

	m_voiceCallback = new VoiceCallback(this);

	{
		WAVEFORMATEX waveFormat = {};
		memset(&waveFormat, 0, sizeof(WAVEFORMATEX));
		waveFormat.nSamplesPerSec	= SAMPLE_RATE;
		waveFormat.wBitsPerSample	= 16;
		waveFormat.nChannels		= 2;
		waveFormat.cbSize			= 0;
		waveFormat.wFormatTag		= WAVE_FORMAT_PCM;
		waveFormat.nBlockAlign		= (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
		waveFormat.nAvgBytesPerSec	= waveFormat.nBlockAlign * waveFormat.nSamplesPerSec;

		result = m_xaudio2->CreateSourceVoice(&m_sourceVoice, &waveFormat, 0, 2.0f, m_voiceCallback);
		assert(SUCCEEDED(result));
	}

	result = m_sourceVoice->Start();
	assert(SUCCEEDED(result));
}