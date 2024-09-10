	void Audio::Initialize(bool music, bool fx)
	{
		m = music;
		f = fx;
		HRESULT hr = XAudio2Create(&s_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
		assert(SUCCEEDED(hr));

		hr = s_pXAudio2->CreateMasteringVoice(&s_pMasterVoice);
		assert(SUCCEEDED(hr));
	}