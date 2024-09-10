	//----------------------------------------------------------------------------------------------------
	bool EEMusic::InitializeMusic()
	{
		if (!s_isMusicInitialized)
		{
			av_register_all();

			// CoInitializeEx(NULL, COINIT_MULTITHREADED);
			if (FAILED(XAudio2Create(&s_XAudio2, 0)))
			{
				MessageBoxW(NULL, L"Create XAudio2 failed!", L"ERROR", MB_OK);
				// CoUninitialize();
				return false;
			}
			if (FAILED(s_XAudio2->CreateMasteringVoice(&s_masteringVoice)))
			{
				MessageBoxW(NULL, L"Create mastering voice failed!", L"ERROR", MB_OK);
				s_XAudio2->Release();
				s_XAudio2 = NULL;
				// CoUninitialize();
				return false;
			}

			s_isMusicInitialized = true;
		}

		return true;
	}