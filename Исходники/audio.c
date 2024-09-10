/* note: only works when loopback is 48khz 2 channel floating*/
void audio_detect(void)
{
    HRESULT hr;
    REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
    //REFERENCE_TIME hnsActualDuration;
    UINT32 bufferFrameCount;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;
    IMMDeviceCollection *pDeviceCollection = NULL;
    //BOOL bDone = FALSE;
    UINT count;
    //HANDLE hEvent = NULL;

    CoInitialize(NULL);

    hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (void**)&pEnumerator);
    EXIT_ON_ERROR(hr)

    hr = pEnumerator->lpVtbl->EnumAudioEndpoints(pEnumerator, eAll, DEVICE_STATE_ACTIVE, &pDeviceCollection);
    EXIT_ON_ERROR(hr)

    hr = pDeviceCollection->lpVtbl->GetCount(pDeviceCollection, &count);
    EXIT_ON_ERROR(hr)

    printf("%u\n", count);

    hr = pEnumerator->lpVtbl->GetDefaultAudioEndpoint(pEnumerator, eRender, eConsole, &pDevice);
    EXIT_ON_ERROR(hr)

    hr = pDevice->lpVtbl->Activate(pDevice, &IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&pAudioClient);
    EXIT_ON_ERROR(hr)

    hr = pAudioClient->lpVtbl->GetMixFormat(pAudioClient, &pwfx);
    EXIT_ON_ERROR(hr)

    printf("default format: %u %u %u %lu %lu %u %u\n", WAVE_FORMAT_PCM, pwfx->wFormatTag, pwfx->nChannels, pwfx->nSamplesPerSec, pwfx->nAvgBytesPerSec, pwfx->wBitsPerSample, pwfx->nBlockAlign);

    if(pwfx->nSamplesPerSec != 48000 || pwfx->nChannels != 2 || pwfx->wFormatTag != WAVE_FORMAT_EXTENSIBLE) {
        printf("unsupported format for loopback\n");
        goto Exit;
    }

    WAVEFORMATEXTENSIBLE *wfx = (void*)pwfx;
    if(memcmp(&KSDATAFORMAT_SUBTYPE_IEEE_FLOAT, &wfx->SubFormat, sizeof(wfx->SubFormat)) != 0) {
        goto Exit;
    }

        /* if(memcmp(&KSDATAFORMAT_SUBTYPE_PCM, &wfx->SubFormat, sizeof(wfx->SubFormat)) == 0) {
            printf("pcm\n");
        } else {
            printf("unknown\n");
        }*/

    hr = pAudioClient->lpVtbl->Initialize(pAudioClient, AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_LOOPBACK, hnsRequestedDuration, 0, pwfx, NULL);
    EXIT_ON_ERROR(hr)

    /*AUDCLNT_STREAMFLAGS_EVENTCALLBACK
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hEvent == NULL)
    {
        hr = E_FAIL;
        goto Exit;
    }

    hr = pAudioClient->lpVtbl->
    EXIT_ON_ERROR(hr)*/

    // Get the size of the allocated buffer.
    hr = pAudioClient->lpVtbl->GetBufferSize(pAudioClient, &bufferFrameCount);
    EXIT_ON_ERROR(hr)

    hr = pAudioClient->lpVtbl->GetService(pAudioClient, &IID_IAudioCaptureClient_utox, (void**)&pCaptureClient);
    EXIT_ON_ERROR(hr)

    printf("%u %lu\n", bufferFrameCount, pwfx->nSamplesPerSec);

    postmessage(NEW_AUDIO_IN_DEVICE, STR_AUDIO_IN_DEFAULT_LOOPBACK, 0, (void*)(size_t)1);
    return;

Exit:
    CoTaskMemFree(pwfx);
    SAFE_RELEASE(pEnumerator)
    SAFE_RELEASE(pDevice)
    SAFE_RELEASE(pAudioClient)
    SAFE_RELEASE(pCaptureClient)

    printf("audio_init fail: %lu\n", hr);

}