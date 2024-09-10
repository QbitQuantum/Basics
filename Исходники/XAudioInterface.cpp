bool XAudioInterface::Init( )
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
    //CoInitialize(NULL);

    HRESULT hr;
    UINT32 xAudioCreationFlag = 0;
#ifdef _DEBUG
    //xAudioCreationFlag = XAUDIO2_DEBUG_ENGINE;
#endif

    if ( FAILED(hr = XAudio2Create( &m_XAudio2, xAudioCreationFlag, XAUDIO2_DEFAULT_PROCESSOR ) ))
    {
        return false;
    }

    // If we ever have to look for multiple device, it can be done through the following code:
    // http://msdn.microsoft.com/en-us/library/bb669173(VS.85).aspx
    // for now, we are going to use the default device since Win7 games will not require
    // advance features.

    if ( FAILED(hr = m_XAudio2->CreateMasteringVoice( &m_MasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL ) ) )
    {
        return false;
    }

    return true;
}