/* Constructor
 */
XAudioSoundSystem::XAudioSoundSystem(void)
{
    HRESULT hr;
    mXAudio2 = NULL;	
	mMasteringVoice = NULL;

    UINT32 flags = 0;

	//
    // Initialize XAudio2
    //
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

	if( FAILED( hr = XAudio2Create( &mXAudio2, flags ) ) )
    {
        wprintf( L"Failed to init XAudio2 engine: %#X\n", hr );
		return;
    }	

    //
    // Create a mastering voice
    //
    if( FAILED( hr = mXAudio2->CreateMasteringVoice( &mMasteringVoice ) ) )
    {
        wprintf( L"Failed creating mastering voice: %#X\n", hr );
        SAFE_RELEASE( mXAudio2 );
		return;
    }
}