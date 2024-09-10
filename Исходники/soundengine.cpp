void Sound_Engine::Internal::Init(){
	pXAudio2=0;
	pMasteringVoice=0;
	pSubmixVoice=0;
	pReverbEffect=0;
	nFrameToApply3DAudio=0;
	dwChannelMask=0;
	nChannels=0;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HR(XAudio2Create( &pXAudio2, 0 )) ;
	HR(pXAudio2->CreateMasteringVoice( &pMasteringVoice ) );

	// Check device details to make sure it's within our sample supported parameters
	XAUDIO2_DEVICE_DETAILS details;
	HR(pXAudio2->GetDeviceDetails( 0, &details ) );
	if( details.OutputFormat.Format.nChannels > OUTPUTCHANNELS ){
		RELEASECOM( pXAudio2 );
		assert(true);
	}
	dwChannelMask = details.OutputFormat.dwChannelMask;
	nChannels = details.OutputFormat.Format.nChannels;

	HR(XAudio2CreateReverb( &pReverbEffect, 0 ) ); // Create reverb effect


	// Create a submix voice
	// Performance tip: you need not run global FX with the sample number
	// of channels as the final mix.  For example, this sample runs
	// the reverb in mono mode, thus reducing CPU overhead.
	XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { pReverbEffect, TRUE, 1 } };
	XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };
	HR(pXAudio2->CreateSubmixVoice( &pSubmixVoice, 1,details.OutputFormat.Format.nSamplesPerSec, 0, 0, NULL, &effectChain ) );

	// Set default FX params
	XAUDIO2FX_REVERB_PARAMETERS native;
	ReverbConvertI3DL2ToNative( &g_PRESET_PARAMS[0], &native );
	pSubmixVoice->SetEffectParameters( 0, &native, sizeof( native ) );

	//
	// Initialize X3DAudio
	//  Speaker geometry configuration on the final mix, specifies assignment of channels
	//  to speaker positions, defined as per WAVEFORMATEXTENSIBLE.dwChannelMask

	X3DAudioInitialize( details.OutputFormat.dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, x3DInstance );
	CurrentListenerPos = D3DXVECTOR3( 0, 0, 0 );

	listener.Position = CurrentListenerPos;
	listener.OrientFront = D3DXVECTOR3( 0, 0, 1 );
	listener.OrientTop = D3DXVECTOR3( 0, 1, 0 );
	listener.pCone = (X3DAUDIO_CONE*)&Listener_DirectionalCone;

	dspSettings.SrcChannelCount = INPUTCHANNELS;
	dspSettings.DstChannelCount = nChannels;
	dspSettings.pMatrixCoefficients = matrixCoefficients;
}