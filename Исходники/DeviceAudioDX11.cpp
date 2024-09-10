void DeviceAudioDX11::restartAudio (void)
{
#if DT2_MULTITHREADED_AUDIO
    AutoSpinLockRecursive lock(&_lock);
#endif

    if (!_x_audio_2) {
        // Initialize Audio system
        HRESULT hr = XAudio2Create( &_x_audio_2, 0, XAUDIO2_DEFAULT_PROCESSOR );

        Assert(SUCCEEDED(hr));

        // Initialize Mastering Voice
        hr = _x_audio_2->CreateMasteringVoice( &_x_master_voice );

        Assert(SUCCEEDED(hr));

        // Initialize 3D audio
        XAUDIO2_VOICE_DETAILS voice_details;
        _x_master_voice->GetVoiceDetails(&voice_details);

        // Initialize 3D audio subsystem
        X3DAudioInitialize( voice_details.InputChannels, X3DAUDIO_SPEED_OF_SOUND, _x3_instance );

        // Initialize listener
        ::memset(&_x3_listener,0,sizeof(X3DAUDIO_LISTENER));

        // Initialize DSP parameters
        ::memset(&_x3_dsp,0,sizeof(X3DAUDIO_DSP_SETTINGS));

        _x3_dsp_matrix.resize(voice_details.InputChannels * NUM_CHANNELS);

        _x3_dsp_delays.resize(voice_details.InputChannels);

        _x3_dsp.pMatrixCoefficients = &_x3_dsp_matrix[0];
        _x3_dsp.pDelayTimes = &_x3_dsp_delays[0];
        _x3_dsp.DstChannelCount = voice_details.InputChannels;
        _x3_dsp.SrcChannelCount = 0; // Changed on the fly when calculating


        // Initialize rest of this class
        setNumberOfChannels(32);
    
        // Get all channels playing again
        for (DTuint c = 0; c < min2(_channels.size(),_save_channels.size()); ++c) {                
            playOnChannel (_channels[c], _save_channels[c]._source, _save_channels[c]._sound_loader);
            RELEASE(_save_channels[c]._source);
            RELEASE(_save_channels[c]._sound_loader);
        }
        
        _save_channels.clear();
    }
}