bool Audio3D::initialiseAudio()
{
	if (m_masteringVoice != NULL)
		m_masteringVoice->DestroyVoice();

	SAFE_RELEASE(m_XAudio2);

	HRESULT hr;
	if (FAILED(hr = XAudio2Create( &m_XAudio2, 0)))
	{
		LOG->logMsg(LT_ERROR, "Error while creating XAudio2: %#X", hr);
		SAFE_RELEASE(m_XAudio2);
		return false;
	}

	if (FAILED(hr = m_XAudio2->CreateMasteringVoice(&m_masteringVoice)))
	{
		LOG->logMsg(LT_ERROR, "Audio3D: Error while creating master voice: %#X", hr);
		return false;
	}

	XAUDIO2_DEVICE_DETAILS details;
    if( FAILED( hr = m_XAudio2->GetDeviceDetails( 0, &details ) ) )
    {
        SAFE_RELEASE( m_XAudio2 );
		LOG->logMsg(LT_ERROR, "Failed to retrieve DeviceDetails: %#X", hr);
        return false;
    }

    if( details.OutputFormat.Format.nChannels > OUTPUTCHANNELS )
    {
        SAFE_RELEASE( m_XAudio2 );
		LOG->logMsg(LT_ERROR, "nChannels too large.");
        return false;
    }

    m_channelMask = details.OutputFormat.dwChannelMask;
    m_channels = details.OutputFormat.Format.nChannels;

	//Create reverb effect:

	 if( FAILED( hr = XAudio2CreateReverb( &m_reverbEffect, 0 ) ) )
    {
        SAFE_RELEASE( m_XAudio2 );
		LOG->logMsg(LT_ERROR, "Failed to create reverb: %#X", hr);
        return false;
    }


	//Create submix voice for mixing effects

	XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { m_reverbEffect, TRUE, 1 } };
    XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

    if( FAILED( hr = m_XAudio2->CreateSubmixVoice( &m_submixVoice, 1,
                                                               details.OutputFormat.Format.nSamplesPerSec, 0, 0,
                                                               NULL, &effectChain ) ) )
    {
        SAFE_RELEASE( m_XAudio2 );
        SAFE_RELEASE( m_reverbEffect );
		LOG->logMsg(LT_ERROR, "Failed to create submix voice: %#X", hr);
        return false;
    }

	
	// Set default FX params
    XAUDIO2FX_REVERB_PARAMETERS native;
    ReverbConvertI3DL2ToNative( &PRESET_PARAMS[0], &native );
    m_submixVoice->SetEffectParameters( 0, &native, sizeof( native ) );

	const float SPEEDOFSOUND = X3DAUDIO_SPEED_OF_SOUND;

    X3DAudioInitialize( details.OutputFormat.dwChannelMask, SPEEDOFSOUND, m_x3DInstance );

    m_useInnerRadius = true;
	m_listenerPos = D3DXVECTOR3( 0, 0, 0 );
	m_useRedirectToLFE = ((details.OutputFormat.dwChannelMask & SPEAKER_LOW_FREQUENCY) != 0);

	//
    // Setup 3D audio structs
    //
    m_listener.Position = m_listenerPos;
    m_listener.OrientFront = D3DXVECTOR3( 0, 1, 0 );
    m_listener.OrientTop = D3DXVECTOR3( 0, 1, 0 );
    m_listener.pCone = (X3DAUDIO_CONE*)&m_listener_DirectionalCone;

	//LOG->logMsg(LT_STATUS, "Audio3D: initialized.");

	this->m_curveDistanceScaler = 60.0f;

	m_initialized = true;

	return true;
}