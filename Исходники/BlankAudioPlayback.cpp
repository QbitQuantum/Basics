    BlankAudioPlayback(CTSTR lpDevice)
    {
        const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
        const IID IID_IMMDeviceEnumerator    = __uuidof(IMMDeviceEnumerator);
        const IID IID_IAudioClient           = __uuidof(IAudioClient);
        const IID IID_IAudioRenderClient     = __uuidof(IAudioRenderClient);

        HRESULT err;
        err = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, IID_IMMDeviceEnumerator, (void**)&mmEnumerator);
        if(FAILED(err))
            CrashError(TEXT("Could not create IMMDeviceEnumerator: 0x%08lx"), err);

        if (scmpi(lpDevice, TEXT("Default")) == 0)
            err = mmEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &mmDevice);
        else
            err = mmEnumerator->GetDevice(lpDevice, &mmDevice);
        if(FAILED(err))
            CrashError(TEXT("Could not create IMMDevice"));

        err = mmDevice->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&mmClient);
        if(FAILED(err))
            CrashError(TEXT("Could not create IAudioClient"));

        WAVEFORMATEX *pwfx;
        err = mmClient->GetMixFormat(&pwfx);
        if(FAILED(err))
            CrashError(TEXT("Could not get mix format from audio client"));

        UINT inputBlockSize = pwfx->nBlockAlign;

        err = mmClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, ConvertMSTo100NanoSec(1000), 0, pwfx, NULL);
        if(FAILED(err))
            CrashError(TEXT("Could not initialize audio client, error = %08lX"), err);

        err = mmClient->GetService(IID_IAudioRenderClient, (void**)&mmRender);
        if(FAILED(err))
            CrashError(TEXT("Could not get audio render client"));

        //----------------------------------------------------------------

        UINT bufferFrameCount;
        err = mmClient->GetBufferSize(&bufferFrameCount);
        if(FAILED(err))
            CrashError(TEXT("Could not get audio buffer size"));

        BYTE *lpData;
        err = mmRender->GetBuffer(bufferFrameCount, &lpData);
        if(FAILED(err))
            CrashError(TEXT("Could not get audio buffer"));

        zero(lpData, bufferFrameCount*inputBlockSize);

        mmRender->ReleaseBuffer(bufferFrameCount, 0);//AUDCLNT_BUFFERFLAGS_SILENT); //probably better if it doesn't know

        if(FAILED(mmClient->Start()))
            CrashError(TEXT("Could not start audio source"));
    }