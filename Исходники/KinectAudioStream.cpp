/// <summary>
/// Audio capture thread. Captures audio data in a loop until it is signaled to stop.
/// </summary>
/// <returns>Non-zero if thread ended successfully, zero in case of failure</returns>
DWORD WINAPI KinectAudioStream::CaptureThread()
{
    HANDLE mmHandle = NULL;
    DWORD mmTaskIndex = 0;
    HRESULT hr = S_OK;
    bool bContinue = true;
    BYTE *pbOutputBuffer = NULL;
    CStaticMediaBuffer outputBuffer;
    DMO_OUTPUT_DATA_BUFFER OutputBufferStruct = {0};
    OutputBufferStruct.pBuffer = &outputBuffer;
    DWORD dwStatus = 0;
    ULONG cbProduced = 0;

    // Set high priority to avoid getting preempted while capturing sound
    mmHandle = AvSetMmThreadCharacteristics("Audio", &mmTaskIndex);

    while (bContinue)
    {
        if (WaitForSingleObject(m_hStopEvent, 0) == WAIT_OBJECT_0)
        {
            bContinue = false;
            continue;
        }

        do
        {
            outputBuffer.Init(0);
            OutputBufferStruct.dwStatus = 0;
            hr = m_pKinectDmo->ProcessOutput(0, 1, &OutputBufferStruct, &dwStatus);
            if (FAILED(hr))
            {
                bContinue = false;
                break;
            }

            if (hr == S_FALSE)
            {
                cbProduced = 0;
            }
            else
            {
                outputBuffer.GetBufferAndLength(&pbOutputBuffer, &cbProduced);
            }

            // Queue audio data to be read by IStream client
            if (cbProduced > 0)
            {
                QueueCapturedData(pbOutputBuffer, cbProduced);
            }
        } while (OutputBufferStruct.dwStatus & DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE);

        Sleep(10); //sleep 10ms
    }

    SetEvent(m_hDataReady);
    AvRevertMmThreadCharacteristics(mmHandle);

    if (FAILED(hr))
    {
        return 0;
    }

    return 1;
}