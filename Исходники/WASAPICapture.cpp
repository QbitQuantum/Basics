DWORD CWASAPICapture::DoCaptureThread()
{
    HANDLE mmcssHandle = NULL;

    IXAudio2* xaudio = 0;
    IXAudio2MasteringVoice* mastering_voice = 0;

    IXAudio2SourceVoice* source_voice = 0;

    try {

        bool stillPlaying = true;
        DWORD mmcssTaskIndex = 0;

        HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
        if (FAILED(hr))
        {
            printf_s("Unable to initialize COM in render thread: %x\n", hr);
            return hr;
        }

    
        mmcssHandle = AvSetMmThreadCharacteristics(L"Audio", &mmcssTaskIndex);
        if (mmcssHandle == NULL)
        {
            printf_s("Unable to enable MMCSS on capture thread: %d\n", GetLastError());
        }

        //
        //  XAudioの初期化
        //
        {
            UINT32 flags = 0;
#ifdef _DEBUG
            flags |= XAUDIO2_DEBUG_ENGINE;
#endif
            if( FAILED( hr = XAudio2Create( &xaudio, flags ) ) )
                throw "XAudio2Create";

            //  Create a mastering voice
            if( FAILED( hr = xaudio->CreateMasteringVoice( &mastering_voice ) ) )
                throw "CreateMasteringVoice";

            //  WAVファイルのWAVEFORMATEXを使ってSourceVoiceを作成
            if( FAILED( xaudio->CreateSourceVoice( &source_voice, MixFormat() ) ) )
                throw "CreateSourceVoice";

            //  再生
            source_voice->Start();

        }

        while (stillPlaying)
        {
            HRESULT hr;
            //
            //  In Timer Driven mode, we want to wait for half the desired latency in milliseconds.
            //
            //  That way we'll wake up half way through the processing period to pull the 
            //  next set of samples from the engine.
            //
		    DWORD waitResult = WaitForSingleObject(_ShutdownEvent, _EngineLatencyInMS / 2);
            switch (waitResult)
            {
            case WAIT_OBJECT_0 + 0:     // _ShutdownEvent
                stillPlaying = false;       // We're done, exit the loop.
                break;        
            case WAIT_TIMEOUT:          // Timeout
                //
                //  We need to retrieve the next buffer of samples from the audio capturer.
                //
                BYTE *pData;
                UINT32 framesAvailable;
                DWORD  flags;

                //
                //  Find out how much capture data is available.  We need to make sure we don't run over the length
                //  of our capture buffer.  We'll discard any samples that don't fit in the buffer.
                //
                hr = _CaptureClient->GetBuffer(&pData, &framesAvailable, &flags, NULL, NULL);
                if (SUCCEEDED(hr))
                {
                    UINT32 framesToCopy = min(framesAvailable, static_cast<UINT32>((_CaptureBufferSize - _CurrentCaptureIndex) / _FrameSize));
                    if (framesToCopy != 0)
                    {
                        //
                        //  The flags on capture tell us information about the data.
                        //
                        //  We only really care about the silent flag since we want to put frames of silence into the buffer
                        //  when we receive silence.  We rely on the fact that a logical bit 0 is silence for both float and int formats.
                        //
                        if (flags & AUDCLNT_BUFFERFLAGS_SILENT)
                        {
                            //
                            //  Fill 0s from the capture buffer to the output buffer.
                            //
                            ZeroMemory(&_CaptureBuffer[_CurrentCaptureIndex], framesToCopy*_FrameSize);
                        }
                        else
                        {
                            //
                            //  Copy data from the audio engine buffer to the output buffer.
                            //
                            CopyMemory(&_CaptureBuffer[_CurrentCaptureIndex], pData, framesToCopy*_FrameSize);

                            // SourceVoiceにデータを送信
                            XAUDIO2_BUFFER buffer = { 0 };
                            buffer.AudioBytes = framesToCopy * _FrameSize;  //バッファのバイト数
                            buffer.pAudioData = &pData[ 0 ];                //バッファの先頭アドレス
                            source_voice->SubmitSourceBuffer( &buffer );
                        }
                        //
                        //  Bump the capture buffer pointer.
                        //
                        _CurrentCaptureIndex += framesToCopy*_FrameSize;
                    }
                    hr = _CaptureClient->ReleaseBuffer(framesAvailable);
                    if (FAILED(hr))
                    {
                        printf_s("Unable to release capture buffer: %x!\n", hr);
                    }
                }
                break;
            }
        }
    }
    catch( const char* e )
    {
        std::cout << e << std::endl;
    }

    //  Cleanup XAudio2
    if( mastering_voice != 0 ) {
        // ここで落ちる
        //mastering_voice->DestroyVoice();
        mastering_voice = 0;
    }

    if( xaudio != 0 ) {
        // ここでも落ちる
        //xaudio->Release();
        xaudio = 0;
    }

    AvRevertMmThreadCharacteristics(mmcssHandle);
    
    CoUninitialize();
    return 0;
}