void speak(string Qtext,int sleepTime)
{
	HRESULT hr = E_FAIL;

	CSpDynamicString Qtextout;


	if (SUCCEEDED(hr = ::CoInitialize(NULL)))
	{
		{
			CComPtr<ISpRecoContext> cpRecoCtxt;
			CComPtr<ISpRecoGrammar> cpGrammar;
			CComPtr<ISpVoice> cpVoice;
			hr = cpRecoCtxt.CoCreateInstance(CLSID_SpSharedRecoContext);

			if (SUCCEEDED(hr))
			{
				hr = cpRecoCtxt->GetVoice(&cpVoice);
			}

			if (cpRecoCtxt && cpVoice &&
				SUCCEEDED(hr = cpRecoCtxt->SetNotifyWin32Event()) &&
				SUCCEEDED(hr = cpRecoCtxt->SetInterest(SPFEI(SPEI_RECOGNITION), SPFEI(SPEI_RECOGNITION))) &&
				SUCCEEDED(hr = cpRecoCtxt->SetAudioOptions(SPAO_RETAIN_AUDIO, NULL, NULL)) &&
				SUCCEEDED(hr = cpRecoCtxt->CreateGrammar(0, &cpGrammar)) &&
				SUCCEEDED(hr = cpGrammar->LoadDictation(NULL, SPLO_STATIC)) &&
				SUCCEEDED(hr = cpGrammar->SetDictationState(SPRS_ACTIVE)))
			{
				USES_CONVERSION;
				CComPtr<ISpRecoResult> cpResult;
				Qtextout.operator=(Qtext.c_str());
				cpVoice->Speak(Qtextout, SPF_ASYNC, NULL);
				Sleep(sleepTime);
			}
		}
		::CoUninitialize();
	}
}