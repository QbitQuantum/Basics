int SoundDevice::CreateSoundDevice( U_INT speakers )
{
#ifdef _DEBUG
	static const UINT32		flags		= XAUDIO2_DEBUG_ENGINE;
#else
	static const UINT32		flags		= 0;
#endif

	if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
	{
		return -1;
	}

	if( FAILED( XAudio2Create( &xAudio, flags ) ) )
	{
		CoUninitialize();
		return -2;
	}
	if( FAILED( xAudio->CreateMasteringVoice( &masterVoice ) ) )
	{
		CoUninitialize();
		return -3;
	}

	return 0;
}