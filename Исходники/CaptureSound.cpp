//-----------------------------------------------------------------------------
// Name: InitDirectSound()
// Desc: Initilizes DirectSound
//-----------------------------------------------------------------------------
HRESULT CCaptureSound::InitDirectSound( GUID* pDeviceGuid )
{
    HRESULT hr;
    m_dwCaptureBufferSize = 0;
    m_dwNotifySize        = 0;
//    g_pWaveFile           = NULL;

    // Initialize COM
    if( FAILED( hr = CoInitialize(NULL) ) )
	{
        printf( "CoInitialize" );
		return hr;
	}


    // Create IDirectSoundCapture using the preferred capture device
    //if( FAILED( hr = DirectSoundCaptureCreate( pDeviceGuid, &m_pDSCapture, NULL ) ) )  //DirectSoundCaptureCreate??
	//in here ,use DSDEVID_DefaultVoiceCapture 
	if( FAILED( hr = DirectSoundCaptureCreate(&DSDEVID_DefaultVoiceCapture, &m_pDSCapture, NULL ) ) )  //DSDEVID_DefaultCapture?? DSDEVID_DefaultVoiceCapture
	{				//DirectSoundCreate8(NULL,&dsound_handle->g_pDsd,NULL)
        printf("DirectSoundCaptureCreate");
		return hr;
	}

	//{WAVE_FORMAT_PCM, 1, 8000, 16000, 2, 16, 0} //Ĭ����Ƶ��ʽ
	 // wFormatTag, nChannels, nSamplesPerSec, mAvgBytesPerSec,
    // nBlockAlign, wBitsPerSample, cbSize
	m_wfxInput.wFormatTag= WAVE_FORMAT_PCM;
	m_wfxInput.nChannels=1;
	m_wfxInput.nSamplesPerSec=8000;
	m_wfxInput.wBitsPerSample=16;
	m_wfxInput.nBlockAlign = m_wfxInput.nChannels * ( m_wfxInput.wBitsPerSample / 8 );
    m_wfxInput.nAvgBytesPerSec = m_wfxInput.nBlockAlign * m_wfxInput.nSamplesPerSec;
	m_wfxInput.cbSize=0;

    return S_OK;
}