DWORD CWASAPICapture::DoCaptureThread()
{
    bool stillPlaying = true;
    HANDLE waitArray[2] = {_ShutdownEvent, _StreamSwitchEvent};
    HANDLE mmcssHandle = NULL;
    DWORD mmcssTaskIndex = 0;

    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    PersistentAssert(SUCCEEDED(hr), "CoInitializeEx failed");
    
    if (!DisableMMCSS)
    {
        mmcssHandle = AvSetMmThreadCharacteristics("Audio", &mmcssTaskIndex);
        PersistentAssert(mmcssHandle != NULL, "AvSetMmThreadCharacteristics failed");
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
        DWORD waitResult = WaitForMultipleObjects(2, waitArray, FALSE, _EngineLatencyInMS / 2);
        switch (waitResult)
        {
        case WAIT_OBJECT_0 + 0:     // _ShutdownEvent
            stillPlaying = false;       // We're done, exit the loop.
            break;
        case WAIT_OBJECT_0 + 1:     // _StreamSwitchEvent
            PersistentSignalError("StreamSwitch event unexpected");
            stillPlaying = false;
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
            UINT64 CaptureStartTime;
            hr = _CaptureClient->GetBuffer(&pData, &framesAvailable, &flags, NULL, &CaptureStartTime);
            if (SUCCEEDED(hr))
            {
                UINT32 framesToCopy = min(framesAvailable, static_cast<UINT32>((_CaptureBufferSize - _CurrentCaptureIndex) / _FrameSize));
                const UINT BytesToCopy = framesToCopy * _FrameSize;
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
                        ZeroMemory(&_CaptureBuffer[_CurrentCaptureIndex], BytesToCopy);
                    }
                    else
                    {
                        //
                        //  Copy data from the audio engine buffer to the output buffer.
                        //
                        CopyMemory(&_CaptureBuffer[_CurrentCaptureIndex], pData, BytesToCopy);
                    }
                    //
                    //  Bump the capture buffer pointer.
                    //
                    if(_Compressor == NULL)
                    {
                        _CurrentCaptureIndex += BytesToCopy;
                    }
                }

                hr = _CaptureClient->ReleaseBuffer(framesAvailable);
                PersistentAssert(SUCCEEDED(hr), "_CaptureClient->ReleaseBuffer failed");
                if(_Compressor && framesToCopy != 0)
                {
                    _Compressor->AudioSample32Bit2Channel((float *)_CaptureBuffer, framesToCopy, CaptureStartTime);
                }
            }
            break;
        }
    }
    if (!DisableMMCSS)
    {
        AvRevertMmThreadCharacteristics(mmcssHandle);
    }

    CoUninitialize();
    return 0;
}