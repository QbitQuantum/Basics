// setup creates the performance object, the default audio path, the
// audio path for non-local sounds, the audio path for the listener, the
// loader for creating segments from sound files and extracts the buffer
// from the non-local audio path and the listener from the listener audio
// path
//
bool SoundCard::setup(void* hwnd) {

    bool rc = false;
	HRESULT hr;
	UINT32 flags = 0;

	// Enable XAudio2 debugging if we're running in debug mode
	#ifdef _DEBUG
		flags |= XAUDIO2_DEBUG_ENGINE;
	#endif

	if ( FAILED( hr = XAudio2Create( &pXAudio2, flags ) ) )
	{
		error(L"SoundCard::01 Failed to initialize XAudio2 engine");
		release();
	}
	else if ( FAILED( hr = pXAudio2->CreateMasteringVoice( &pMasteringVoice ) ) )
	{
		error(L"SoundCard::02 Failed to create Mastering Voice");
		release();
	}
    else
	{
		// Initialize the X3DAudio engine
		XAUDIO2_DEVICE_DETAILS deviceDetails;
		pXAudio2->GetDeviceDetails(0,&deviceDetails);
		DWORD channelMask = deviceDetails.OutputFormat.dwChannelMask;

		X3DAudioInitialize( channelMask, X3DAUDIO_SPEED_OF_SOUND, X3DInstance );
		update(); // update the X3DAUDIO_LISTENER with the current camera position/heading
		
        // set the frequency and volume range of the context
		// http://msdn.microsoft.com/en-us/library/ee415828(v=VS.85).aspx
		context->set(GF_AU_FREQ, DEFAULT_FREQUENCY); 
        context->set(GF_AU_MXVL, MAX_VOLUME);
        context->set(GF_AU_MNVL, MIN_VOLUME);
		context->set(GF_AU_CVOL, DEFAULT_VOLUME);

        rc = true;
    }

	return rc;
}