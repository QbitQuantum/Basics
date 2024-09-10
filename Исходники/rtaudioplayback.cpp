void
RtAudioPlayback::initAudio(
    long sampleRate,
    int channels )
{
    //int channels = 2;
    //int sampleRate = 44100;

    int nBuffers = 16;
    int bufferSize = 512;

    try
    {
        RtAudio::RtAudioApi api = RtAudio::UNSPECIFIED;
        RtAudioFormat format = RTAUDIO_SINT16;
        m_audio = new RtAudio();

        int card = internalSoundCardID( m_deviceNum );

        #ifdef Q_WS_X11
        api = RtAudio::LINUX_ALSA;
        #endif

        RtAudioDeviceInfo info = m_audio->getDeviceInfo( card );
        delete m_audio;

        if ( info.nativeFormats & RTAUDIO_SINT32 )
        {
            format = RTAUDIO_SINT32;
        }
        if ( info.nativeFormats & RTAUDIO_SINT24 )
        {
            format = RTAUDIO_SINT24;
        }
        if ( info.nativeFormats & RTAUDIO_SINT16 )
        {
            format = RTAUDIO_SINT16;
        }

        m_audio = new RtAudio( card, channels, 0, 0, format, sampleRate, &bufferSize, nBuffers, api );
    }
    catch ( RtError &error )
    {
        LOGL( 1, "Initialising RtAudio failed. RtAudio error type: " << error.getType() <<
                 " Message: " << error.getMessage() );

        // Don't delete m_audio here or it will crash.
        // We don't emit an error signal here, it happens on startPlayback if
        // we have no m_audio.
        m_audio = 0;

        return;
    }
}