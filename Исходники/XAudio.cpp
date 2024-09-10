void InitXAudio(Game* thegame)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HRESULT hr = XAudio2Create(&XAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if(FAILED(hr))
	    exit(EXIT_FAILURE);

	hr = XAudio2->CreateMasteringVoice(&MasterVoice);
	if(FAILED(hr))
		exit(EXIT_FAILURE);
}