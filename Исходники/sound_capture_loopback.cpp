void LoopbackCaptureFor(IMMDevice* mmDevice, std::string filename, int secs)
{
    // open new file
    MMIOINFO mi = { 0 };

    // some flags cause mmioOpen write to this buffer
    // but not any that we're using
    std::wstring wsFilename(filename.begin(), filename.end()); // mmioOpen wants a wstring
    HMMIO file = mmioOpen(const_cast<LPWSTR>(wsFilename.c_str()), &mi, MMIO_WRITE | MMIO_CREATE);

    time_t startTime = time(nullptr);

    // activate an IAudioClient
    IAudioClient* audioClient;
    HRESULT hr = mmDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void**)&audioClient);
    if (FAILED(hr))
    {
        fprintf(stderr, "IMMDevice::Activate(IAudioClient) failed: hr = 0x%08x", hr);
        return;
    }

    // get the default device periodicity
    REFERENCE_TIME hnsDefaultDevicePeriod;
    hr = audioClient->GetDevicePeriod(&hnsDefaultDevicePeriod, nullptr);
    if (FAILED(hr))
    {
        fprintf(stderr, "IAudioClient::GetDevicePeriod failed: hr = 0x%08x\n", hr);
        audioClient->Release();
        return;
    }

    // get the default device format
    WAVEFORMATEX* waveform;
    hr = audioClient->GetMixFormat(&waveform);
    if (FAILED(hr))
    {
        fprintf(stderr, "IAudioClient::GetMixFormat failed: hr = 0x%08x\n", hr);
        CoTaskMemFree(waveform);
        audioClient->Release();
        return;
    }

    // coerce int-16 wave format
    // can do this in-place since we're not changing the size of the format
    // also, the engine will auto-convert from float to int for us
    switch (waveform->wFormatTag)
    {
        case WAVE_FORMAT_IEEE_FLOAT:
            waveform->wFormatTag = WAVE_FORMAT_PCM;
            waveform->wBitsPerSample = BITS_PER_SAMPLE;
            waveform->nBlockAlign = BLOCK_ALIGN;
            waveform->nAvgBytesPerSec = BYTE_RATE;
            break;
        case WAVE_FORMAT_EXTENSIBLE:
        {
            // naked scope for case-local variable
            PWAVEFORMATEXTENSIBLE pEx = reinterpret_cast<PWAVEFORMATEXTENSIBLE>(waveform);
            if (IsEqualGUID(KSDATAFORMAT_SUBTYPE_IEEE_FLOAT, pEx->SubFormat))
            {
                pEx->SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
                pEx->Samples.wValidBitsPerSample = BITS_PER_SAMPLE;
                waveform->wBitsPerSample = BITS_PER_SAMPLE;
                waveform->nBlockAlign = waveform->nChannels * BYTE_PER_SAMPLE;
                waveform->nAvgBytesPerSec = waveform->nBlockAlign * waveform->nSamplesPerSec;
            }
            break;
        }
    }

    MMCKINFO ckRIFF = { 0 };
    MMCKINFO ckData = { 0 };
    hr = WriteWaveHeader(file, waveform, &ckRIFF, &ckData);

    // create a periodic waitable timer
    HANDLE hWakeUp = CreateWaitableTimer(nullptr, FALSE, nullptr);
    UINT32 nBlockAlign = waveform->nBlockAlign;

    // call IAudioClient::Initialize
    // note that AUDCLNT_STREAMFLAGS_LOOPBACK and AUDCLNT_STREAMFLAGS_EVENTCALLBACK
    // do not work together...
    // the "data ready" event never gets set
    // so we're going to do a timer-driven loop
    hr = audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_LOOPBACK, 0, 0, waveform, 0);
    if (FAILED(hr))
    {
        fprintf(stderr, "IAudioClient::Initialize failed: hr = 0x%08x\n", hr);
        CloseHandle(hWakeUp);
        audioClient->Release();
        return;
    }

    // free up waveform
    CoTaskMemFree(waveform);

    // activate an IAudioCaptureClient
    IAudioCaptureClient* audioCaptureClient;
    hr = audioClient->GetService(__uuidof(IAudioCaptureClient), (void**)&audioCaptureClient);

    // register with MMCSS
    DWORD nTaskIndex = 0;
    HANDLE hTask = AvSetMmThreadCharacteristics(L"Capture", &nTaskIndex);
    if (hTask == nullptr)
    {
        DWORD dwErr = GetLastError();
        fprintf(stderr, "AvSetMmThreadCharacteristics failed: last error = %u\n", dwErr);
        audioCaptureClient->Release();
        CloseHandle(hWakeUp);
        audioClient->Release();
        return;
    }

    // set the waitable timer
    LARGE_INTEGER liFirstFire;
    liFirstFire.QuadPart = -hnsDefaultDevicePeriod / 2; // negative means relative time
    LONG lTimeBetweenFires = (LONG)hnsDefaultDevicePeriod / 2 / (10 * 1000); // convert to milliseconds
    if (!SetWaitableTimer(hWakeUp, &liFirstFire, lTimeBetweenFires, nullptr, nullptr, FALSE))
    {
        DWORD dwErr = GetLastError();
        fprintf(stderr, "SetWaitableTimer failed: last error = %u\n", dwErr);
        AvRevertMmThreadCharacteristics(hTask);
        audioCaptureClient->Release();
        CloseHandle(hWakeUp);
        audioClient->Release();
        return;
    }

    // call IAudioClient::Start
    hr = audioClient->Start();

    // loopback capture loop
    DWORD dwWaitResult;

    UINT32 frames = 0;
    for (UINT32 passes = 0; ; passes++)
    {
        // drain data while it is available
        UINT32 nextPacketSize;
        for (hr = audioCaptureClient->GetNextPacketSize(&nextPacketSize);
            SUCCEEDED(hr) && nextPacketSize > 0;
            hr = audioCaptureClient->GetNextPacketSize(&nextPacketSize))
        {
            // get the captured data
            BYTE* data;
            UINT32 framesToRead;
            DWORD dwFlags;

            hr = audioCaptureClient->GetBuffer(&data, &framesToRead, &dwFlags, nullptr, nullptr);
            if (FAILED(hr))
            {
                fprintf(stderr, "IAudioCaptureClient::GetBuffer failed on pass %u after %u frames: hr = 0x%08x\n", passes, frames, hr);
                audioClient->Stop();
                CancelWaitableTimer(hWakeUp);
                AvRevertMmThreadCharacteristics(hTask);
                audioCaptureClient->Release();
                CloseHandle(hWakeUp);
                audioClient->Release();
                return;
            }

            // this type of error seems to happen often, ignore it
            if (dwFlags == AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY)
                ;
            else if (dwFlags != 0) {
                fprintf(stderr, "IAudioCaptureClient::GetBuffer set flags to 0x%08x on pass %u after %u frames\n", dwFlags, passes, frames);
                audioClient->Stop();
                CancelWaitableTimer(hWakeUp);
                AvRevertMmThreadCharacteristics(hTask);
                audioCaptureClient->Release();
                CloseHandle(hWakeUp);
                audioClient->Release();
                return;
            }

            if (framesToRead == 0)
            {
                fprintf(stderr, "IAudioCaptureClient::GetBuffer said to read 0 frames on pass %u after %u frames\n", passes, frames);
                audioClient->Stop();
                CancelWaitableTimer(hWakeUp);
                AvRevertMmThreadCharacteristics(hTask);
                audioCaptureClient->Release();
                CloseHandle(hWakeUp);
                audioClient->Release();
                return;
            }

            LONG lBytesToWrite = framesToRead * nBlockAlign;
#pragma prefast(suppress: __WARNING_INCORRECT_ANNOTATION, "IAudioCaptureClient::GetBuffer SAL annotation implies a 1-byte buffer")
            LONG lBytesWritten = mmioWrite(file, reinterpret_cast<PCHAR>(data), lBytesToWrite);
            if (lBytesToWrite != lBytesWritten)
            {
                fprintf(stderr, "mmioWrite wrote %u bytes on pass %u after %u frames: expected %u bytes\n", lBytesWritten, passes, frames, lBytesToWrite);
                audioClient->Stop();
                CancelWaitableTimer(hWakeUp);
                AvRevertMmThreadCharacteristics(hTask);
                audioCaptureClient->Release();
                CloseHandle(hWakeUp);
                audioClient->Release();
                return;
            }

            frames += framesToRead;

            hr = audioCaptureClient->ReleaseBuffer(framesToRead);
        }

        dwWaitResult = WaitForSingleObject(hWakeUp, INFINITE);

        if (time(nullptr) - startTime > secs)
            break;
    }

    FinishWaveFile(file, &ckData, &ckRIFF);
    audioClient->Stop();
    CancelWaitableTimer(hWakeUp);
    AvRevertMmThreadCharacteristics(hTask);
    audioCaptureClient->Release();
    CloseHandle(hWakeUp);
    audioClient->Release();


    // everything went well... fixup the fact chunk in the file
    MMRESULT result = mmioClose(file, 0);
    file = nullptr;
    if (result != MMSYSERR_NOERROR)
    {
        fprintf(stderr, "mmioClose failed: MMSYSERR = %u\n", result);
        return;
    }

    // reopen the file in read/write mode
    mi = { 0 };
    file = mmioOpen(const_cast<LPWSTR>(wsFilename.c_str()), &mi, MMIO_READWRITE);
    if (file == nullptr)
    {
        fprintf(stderr, "mmioOpen(\"%ls\", ...) failed. wErrorRet == %u\n", filename, mi.wErrorRet);
        return;
    }

    // descend into the RIFF/WAVE chunk
    ckRIFF = { 0 };
    ckRIFF.ckid = MAKEFOURCC('W', 'A', 'V', 'E'); // this is right for mmioDescend
    result = mmioDescend(file, &ckRIFF, nullptr, MMIO_FINDRIFF);
    if (result != MMSYSERR_NOERROR)
    {
        fprintf(stderr, "mmioDescend(\"WAVE\") failed: MMSYSERR = %u\n", result);
        return;
    }

    // descend into the fact chunk
    MMCKINFO ckFact = { 0 };
    ckFact.ckid = MAKEFOURCC('f', 'a', 'c', 't');
    result = mmioDescend(file, &ckFact, &ckRIFF, MMIO_FINDCHUNK);
    if (result != MMSYSERR_NOERROR) {
        fprintf(stderr, "mmioDescend(\"fact\") failed: MMSYSERR = %u\n", result);
        return;
    }

    // write the correct data to the fact chunk
    LONG lBytesWritten = mmioWrite(file, reinterpret_cast<PCHAR>(&frames), sizeof(frames));
    if (lBytesWritten != sizeof(frames))
    {
        fprintf(stderr, "Updating the fact chunk wrote %u bytes; expected %u\n", lBytesWritten, (UINT32)sizeof(frames));
        return;
    }

    // ascend out of the fact chunk
    result = mmioAscend(file, &ckFact, 0);
    if (result != MMSYSERR_NOERROR)
        fprintf(stderr, "mmioAscend(\"fact\") failed: MMSYSERR = %u\n", result);
}