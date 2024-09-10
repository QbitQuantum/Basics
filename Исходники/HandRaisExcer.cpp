DWORD WINAPI HandRaisExcer::Txt2SpeechThread()
{		
		HRESULT                        hr = S_OK;
		CComPtr<ISpObjectToken>        cpAudioOutToken;
		CComPtr<IEnumSpObjectTokens>   cpEnum;
		CComPtr<ISpVoice>              cpVoice;
		ULONG                          ulCount = 0;

		if (FAILED(::CoInitialize(NULL)))
				return FALSE; 
		// Create the SAPI voice.
		hr = cpVoice.CoCreateInstance(CLSID_SpVoice);

		if (SUCCEEDED (hr))
		{
		   // Enumerate the available audio output devices.
		   hr = SpEnumTokens( SPCAT_AUDIOOUT, NULL, NULL, &cpEnum);
		}

		if (SUCCEEDED (hr))
		{
		   // Get the number of audio output devices.
		   hr = cpEnum->GetCount( &ulCount);
		}

		if (SUCCEEDED (hr))
		{
			hr = cpEnum->Next( 1, &cpAudioOutToken, NULL );
		}

		if (SUCCEEDED (hr))
		{
			hr = cpVoice->SetOutput( cpAudioOutToken, TRUE );
		}

		if (SUCCEEDED (hr))
		{
			cpVoice->SetRate(-1);
			while (TRUE)
			{
				if (m_isHandReinitial)
				{
					m_isHandReinitial = FALSE;
					Sleep(100);   //Refresh m_pStrToSpeak					
					cpVoice->Speak(m_pStrToSpeak, SPF_DEFAULT, NULL);	   
				}
			}
		}

		::CoUninitialize();

		if (FAILED(hr)) return FALSE;

	return TRUE;
}