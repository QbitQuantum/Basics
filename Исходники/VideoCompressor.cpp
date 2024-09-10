VideoCompressorResult VideoCompressor::OpenFile(const String &Filename, UINT Width, UINT Height, UINT BitRate, UINT FrameRate, UINT AudioDeviceIndex, Clock *Timer)
{
    VideoCompressorResult Result = VideoCompressorResultSuccess;
    _Width = Width;
    _Height = Height;
    _CapturingAudio = (AudioDeviceIndex != 0xFFFFFFFF);
    _Clock = Timer;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    //PersistentAssert(SUCCEEDED(hr), "CoInitializeEx failed");

    hr = MFStartup(MF_VERSION);
    PersistentAssert(SUCCEEDED(hr), "MFStartup failed");
    
    hr = MFCreateSinkWriterFromURL(
            UnicodeString(Filename).CString(),
            NULL,
            NULL,
            &_Writer
            );
    PersistentAssert(SUCCEEDED(hr), "MFCreateSinkWriterFromURL failed");

    const UINT RawBufferSize = Width * Height * 4;
    
    IMFMediaType *OutputMediaType;
    MFCreateMediaType(&OutputMediaType);
    InitMediaType(OutputMediaType, MFVideoFormat_H264, BitRate, Width, Height, FrameRate);

    IMFMediaType *InputMediaType;
    MFCreateMediaType(&InputMediaType);
    InitMediaType(InputMediaType, MFVideoFormat_RGB32, RawBufferSize, Width, Height, FrameRate);

    DWORD VideoStreamIndex;
    hr = _Writer->AddStream(OutputMediaType, &VideoStreamIndex);
    PersistentAssert(SUCCEEDED(hr), "AddStream failed");
    OutputMediaType->Release();
    
    /*hr = MFTRegisterLocalByCLSID(
            __uuidof(CColorConvertDMO),
            MFT_CATEGORY_VIDEO_PROCESSOR,
            L"",
            MFT_ENUM_FLAG_SYNCMFT,
            0,
            NULL,
            0,
            NULL
            );
    PersistentAssert(SUCCEEDED(hr), "MFTRegisterLocalByCLSID failed");*/

    hr = _Writer->SetInputMediaType(VideoStreamIndex, InputMediaType, NULL);
    InputMediaType->Release();
    if(FAILED(hr))
    {
        if(Width > 1920 || Height > 1080)
        {
            MessageBox(NULL, "The maximum resolution for H.264 video is 1920x1080.", "Invalid Window Dimensions", MB_OK | MB_ICONERROR);
        }
        else
        {
            MessageBox(NULL, "There was an error when attempting to initialize video capture.  The maximum resolution for H.264 video is 1920x1080.", "Invalid Window Dimensions", MB_OK | MB_ICONERROR);
        }
        _Writer->Release();
        _Writer = NULL;
        _Clock = NULL;
        return VideoCompressorResultFailure;
    }
    
    if(_CapturingAudio)
    {
        //
        // Setup the output media type
        //
        IMFMediaType *OutputAudioType;
        hr = MFCreateMediaType( &OutputAudioType );
        PersistentAssert(SUCCEEDED(hr), "MFCreateMediaType failed");

        const UINT SamplesPerSecond = 44100;
        const UINT AverageBytesPerSecond = 24000;
        const UINT ChannelCount = 2;
        const UINT BitsPerSample = 16;
        
        OutputAudioType->SetGUID( MF_MT_MAJOR_TYPE, MFMediaType_Audio ) ;  
        OutputAudioType->SetGUID( MF_MT_SUBTYPE, MFAudioFormat_AAC ) ;
        OutputAudioType->SetUINT32( MF_MT_AUDIO_SAMPLES_PER_SECOND, SamplesPerSecond ) ;
        OutputAudioType->SetUINT32( MF_MT_AUDIO_BITS_PER_SAMPLE, BitsPerSample ) ;
        OutputAudioType->SetUINT32( MF_MT_AUDIO_NUM_CHANNELS, ChannelCount ) ;
        OutputAudioType->SetUINT32( MF_MT_AUDIO_AVG_BYTES_PER_SECOND, AverageBytesPerSecond ) ;
        OutputAudioType->SetUINT32( MF_MT_AUDIO_BLOCK_ALIGNMENT, 1 ) ;
        //OutputAudioType->SetUINT32( MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION, 0x29 ) ;

        DWORD AudioStreamIndex;
        hr = _Writer->AddStream( OutputAudioType, &AudioStreamIndex );
        PersistentAssert(SUCCEEDED(hr), "AddStream failed");

        //
        // Setup the input media type
        //

        IMFMediaType *InputAudioType;
        MFCreateMediaType( &InputAudioType );
        InputAudioType->SetGUID( MF_MT_MAJOR_TYPE, MFMediaType_Audio );
        InputAudioType->SetGUID( MF_MT_SUBTYPE, MFAudioFormat_PCM );
        InputAudioType->SetUINT32( MF_MT_AUDIO_BITS_PER_SAMPLE, BitsPerSample );
        InputAudioType->SetUINT32( MF_MT_AUDIO_SAMPLES_PER_SECOND, SamplesPerSecond );
        InputAudioType->SetUINT32( MF_MT_AUDIO_NUM_CHANNELS, ChannelCount );

        hr = _Writer->SetInputMediaType( AudioStreamIndex, InputAudioType, NULL );
        PersistentAssert(SUCCEEDED(hr), "SetInputMediaType failed");

        _AudioCapture.StartCapture(this, AudioDeviceIndex);
    }

    hr = _Writer->BeginWriting();
    PersistentAssert(SUCCEEDED(hr), "BeginWriting failed");

    
    hr = MFCreateSample(&_Sample);
    PersistentAssert(SUCCEEDED(hr), "MFCreateSample failed");

    hr = MFCreateMemoryBuffer(RawBufferSize, &_Buffer);
    _Buffer->SetCurrentLength(RawBufferSize);
    _Sample->AddBuffer(_Buffer);

    return Result;
}