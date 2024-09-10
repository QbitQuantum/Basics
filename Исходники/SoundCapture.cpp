HRESULT SoundCapture::Open( DWORD dwSampleRate, WORD wBitPerSample, WORD wChannels )
{
	GUID deviceGuid = GUID_NULL;
	HRESULT hr = DirectSoundCaptureCreate( &deviceGuid, &m_pDSCapture, NULL );
	m_dwNextCaptureOffset = 0;

	WAVEFORMATEX wfxInput;
	ZeroMemory ( &wfxInput, sizeof(wfxInput) );
	wfxInput.wFormatTag = WAVE_FORMAT_PCM;
	wfxInput.nSamplesPerSec = dwSampleRate;
	wfxInput.wBitsPerSample = wBitPerSample;
	wfxInput.nChannels = wChannels;
	wfxInput.nBlockAlign = wfxInput.nChannels * ( wfxInput.wBitsPerSample / 8 );
	wfxInput.nAvgBytesPerSec = wfxInput.nBlockAlign * wfxInput.nSamplesPerSec;

	DWORD dwNotifySize = max( 1024, wfxInput.nAvgBytesPerSec / 8 );
	dwNotifySize -= dwNotifySize % wfxInput.nBlockAlign;
	m_dwCaptureBufferSize = dwNotifySize * NUM_REC_NOTIFICATIONS;

	DSCBUFFERDESC dscbd;
	ZeroMemory( &dscbd, sizeof(dscbd) );
	dscbd.dwSize = sizeof(dscbd);
	dscbd.dwBufferBytes = m_dwCaptureBufferSize;
	dscbd.lpwfxFormat = &wfxInput; // Set the format during creatation
	hr = m_pDSCapture->CreateCaptureBuffer( &dscbd, &m_pDSBCapture, NULL );

	DSBPOSITIONNOTIFY arrPosNotify[NUM_REC_NOTIFICATIONS + 1];
	ZeroMemory( &arrPosNotify, sizeof( DSBPOSITIONNOTIFY ) * ( NUM_REC_NOTIFICATIONS + 1 ) );
	m_hNotificationEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

	hr = m_pDSBCapture->QueryInterface( IID_IDirectSoundNotify, (VOID**)&m_pDSNotify );
	for ( int i = 0; i < NUM_REC_NOTIFICATIONS; i++ )
	{
		arrPosNotify[i].dwOffset = (dwNotifySize * i) + dwNotifySize - 1;
		arrPosNotify[i].hEventNotify = m_hNotificationEvent;
	}
	hr = m_pDSNotify->SetNotificationPositions( NUM_REC_NOTIFICATIONS, arrPosNotify );
	return S_OK;
}