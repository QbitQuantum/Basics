TTSWidget::TTSWidget(QWidget* parent /*= 0*/, Qt::WFlags flags /*= 0*/) : QWidget(parent, flags)
{
	setupUi(this);

#ifdef _WIN32
	CoInitialize(NULL);
	HRESULT                             hr = S_OK;
	CComPtr<ISpObjectToken>             cpVoiceToken;
	CComPtr<IEnumSpObjectTokens>        cpEnum;
	CComPtr<ISpVoice>                   cpVoice;
	ULONG                               ulCount = 0;
	
	// Create the SAPI voice
	if(SUCCEEDED(hr))
		hr = cpVoice.CoCreateInstance( CLSID_SpVoice ); 
	//Enumerate the available voices 
	if(SUCCEEDED(hr))
		hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);
	//Get the number of voices
	if(SUCCEEDED(hr))
		hr = cpEnum->GetCount(&ulCount);
	// Obtain a list of available voice tokens
	while (SUCCEEDED(hr) && ulCount-- )
	{
		cpVoiceToken.Release();
		if(SUCCEEDED(hr))
			hr = cpEnum->Next( 1, &cpVoiceToken, NULL );
		WCHAR* voiceName = 0;
		if (SUCCEEDED(SpGetDescription(cpVoiceToken, &voiceName)))
		{
			m_voice->addItem(QString::fromUtf16((const ushort*) voiceName));
			CoTaskMemFree(voiceName);
		}
	}
	CoUninitialize();
#endif

	connect(m_voice, SIGNAL(currentIndexChanged(int)), this, SLOT(voiceChanged(int)));
	connect(m_speakButton, SIGNAL(clicked()), this, SLOT(speak()));	
}