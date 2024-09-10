    void KinectAudioSource::Start()
    {

        DMO_MEDIA_TYPE mt = {0};

        ULONG cbProduced = 0;

        memset( &outputBufferStruct_, 0, sizeof(outputBufferStruct_) );
        outputBufferStruct_.pBuffer = &mediaBuffer_;

        // Set DMO output format
        CHECKHR( MoInitMediaType(&mt, sizeof(WAVEFORMATEX)) );

        mt.majortype = MEDIATYPE_Audio;
        mt.subtype = MEDIASUBTYPE_PCM;
        mt.lSampleSize = 0;
        mt.bFixedSizeSamples = TRUE;
        mt.bTemporalCompression = FALSE;
        mt.formattype = FORMAT_WaveFormatEx;
        memcpy(mt.pbFormat, &GetWaveFormat(), sizeof(WAVEFORMATEX));
    
        CHECKHR( mediaObject_->SetOutputType(0, &mt, 0) );
        MoFreeMediaType(&mt);

        // Allocate streaming resources. This step is optional. If it is not called here, it
        // will be called when first time ProcessInput() is called. However, if you want to 
        // get the actual frame size being used, it should be called explicitly here.
        CHECKHR( mediaObject_->AllocateStreamingResources() );
    
        // Get actually frame size being used in the DMO. (optional, do as you need)
        int iFrameSize;
        PROPVARIANT pvFrameSize;
        PropVariantInit(&pvFrameSize);
        CHECKHR(propertyStore_->GetValue(MFPKEY_WMAAECMA_FEATR_FRAME_SIZE, &pvFrameSize));
        iFrameSize = pvFrameSize.lVal;
        PropVariantClear(&pvFrameSize);

        // allocate output buffer
        mediaBuffer_.SetBufferLength( GetWaveFormat().nSamplesPerSec * GetWaveFormat().nBlockAlign );
    }