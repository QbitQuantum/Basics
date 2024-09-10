int CZPlayer::InitAudio()
{
	ZeroMemory(m_audioState,sizeof(AUDIO_STATE));
	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	UINT32 flags = 0;
#ifdef _DEBUG
	flags |= XAUDIO2_DEBUG_ENGINE;
#endif

	HRESULT hr;
	
	if(FAILED(hr = XAudio2Create(&m_audioState->pXAudio2,flags)))
		return -1;

	if( FAILED( hr = m_audioState->pXAudio2->CreateMasteringVoice( &m_audioState->pMasteringVoice ) ) )
    {
        SAFE_RELEASE( m_audioState->pXAudio2 );
        return -1;
    }

	if( FAILED( hr = m_audioState->pXAudio2->GetDeviceDetails( 0, &m_details ) ) )
    {
        SAFE_RELEASE( m_audioState->pXAudio2 );
        return -1;
    }



    //
    // Create reverb effect
    //
    flags = 0;
#ifdef _DEBUG
    flags |= XAUDIO2FX_DEBUG;
#endif

    if( FAILED( hr = XAudio2CreateReverb( &m_audioState->pReverbEffect, flags ) ) )
    {
        SAFE_RELEASE( m_audioState->pXAudio2 );
        return -1;
    }

    
     //Create a submix voice
    

    //Performance tip: you need not run global FX with the sample number
    //of channels as the final mix.  For example, this sample runs
    //the reverb in mono mode, thus reducing CPU overhead.
    XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { m_audioState->pReverbEffect, TRUE, 1 } };
    XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

    if( FAILED( hr = m_audioState->pXAudio2->CreateSubmixVoice( &m_audioState->pSubmixVoice, 1,
                                                               m_details.OutputFormat.Format.nSamplesPerSec, 0, 0,
                                                               NULL, &effectChain ) ) )
    {
        SAFE_RELEASE( m_audioState->pXAudio2 );
        SAFE_RELEASE( m_audioState->pReverbEffect );
        return -1;
    }

	XAUDIO2FX_REVERB_PARAMETERS native;
    ReverbConvertI3DL2ToNative( &g_PRESET_PARAMS[1], &native );
    m_audioState->pSubmixVoice->SetEffectParameters( 0, &native, sizeof( native ) );
	m_audioState->pSourceVoice = 0;
	// done
	m_audioState->bInitialized = true;
	m_playerState.stop = true;
	return 0;
}