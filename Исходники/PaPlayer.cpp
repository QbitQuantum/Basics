bool PaPlayer::initStream()
{
    close();
    PaStreamParameters outputParameters;
    PaError err;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
       m_lastError = "No default output device.";
       return false;
    }
    outputParameters.channelCount = m_wavFile->channelsCount();       /* stereo/mono output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    const double sampleRate = m_wavFile->audioSampleRate();
    const unsigned int framesPerBuffer = 64;

    err = Pa_OpenStream(
              &m_stream,
              NULL, // no input
              &outputParameters,
              sampleRate,
              framesPerBuffer,
              paClipOff,      // we won't output out of range samples so don't bother clipping them
              wavPlayCallback,
              this );
    CheckError(err);

    err = Pa_SetStreamFinishedCallback( m_stream, &StreamFinished );
    CheckError(err);

    err = Pa_StartStream( m_stream );
    CheckError(err);

    return true;
}