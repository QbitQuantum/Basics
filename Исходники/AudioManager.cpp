bool CAudioManager::Init()
{
	HRESULT hr;
	
	hr = XAudio2Create(&m_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if(FAILED(hr))
	{
		LogErrorHr("Failed to create XAudio2", hr);
		return false;
	}

	hr = m_pXAudio2->CreateMasteringVoice(&m_pDevice);
	if(FAILED(hr))
	{
		LogErrorHr("Failed to create mastering voice", hr);
		return false;
	}

	for(int iTrackIndex = 0; iTrackIndex < g_iAudioTrackCount; iTrackIndex++)
	{
		if(!m_tracks[iTrackIndex].Init(m_pXAudio2, m_pDevice))
		{
			return false;
		}
	}

	m_bInited = true;

	return true;
}