void GameAudio::initialize()
{
	currentMusicPlaying = ENUM_MUSIC_NONE;	//// initially, current music is none
	
	bool ciFailed = FAILED(CoInitializeEx(0, COINIT_MULTITHREADED));
	UINT32 flags = 0;

	bool xa2cSuccess = SUCCEEDED(XAudio2Create(&xAudio2Engine));

	bool cmvSuccess = SUCCEEDED(xAudio2Engine->CreateMasteringVoice(&masterVoice,
		XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, 0));
	
	//// -- still not sure if I need only one master voice or multiple(one master per one source voice)
}