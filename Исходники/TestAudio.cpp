int main(int argc, char *argv[])
{
	CoInitialize(nullptr);

	listDevices();

	IAudioClient *pAudioClient;
	IMMDevice *device;

	getDefaultDevice(&device);

    HRESULT hr = device->Activate(__uuidof(IAudioClient),
        CLSCTX_ALL, nullptr, (void**)&pAudioClient);
    if (FAILED(hr)) {
        printf("IMMDevice::Activate(IAudioClient) failed: hr = 0x%08x", hr);
        return hr;
    }

	REFERENCE_TIME hnsDefaultDevicePeriod;
    hr = pAudioClient->GetDevicePeriod(&hnsDefaultDevicePeriod, nullptr);
    if (FAILED(hr)) {
        printf("IAudioClient::GetDevicePeriod failed: hr = 0x%08x\n", hr);
        pAudioClient->Release();
        return hr;
    }

	// get the default device format
    WAVEFORMATEX *pwfx;
    hr = pAudioClient->GetMixFormat(&pwfx);
    if (FAILED(hr)) {
        printf("IAudioClient::GetMixFormat failed: hr = 0x%08x\n", hr);
        CoTaskMemFree(pwfx);
        pAudioClient->Release();
        return hr;
    }

    DVAR(pwfx->wFormatTag);
    DVAR(pwfx->wBitsPerSample);
    DVAR(pwfx->nBlockAlign);
    DVAR(pwfx->nAvgBytesPerSec);

    switch (pwfx->wFormatTag) {
        case WAVE_FORMAT_IEEE_FLOAT:
            pwfx->wFormatTag = WAVE_FORMAT_PCM;
            pwfx->wBitsPerSample = 16;
            pwfx->nBlockAlign = pwfx->nChannels * pwfx->wBitsPerSample / 8;
            pwfx->nAvgBytesPerSec = pwfx->nBlockAlign * pwfx->nSamplesPerSec;
            break;

        case WAVE_FORMAT_EXTENSIBLE:
            {
                // naked scope for case-local variable
                PWAVEFORMATEXTENSIBLE pEx = reinterpret_cast<PWAVEFORMATEXTENSIBLE>(pwfx);
                if (IsEqualGUID(KSDATAFORMAT_SUBTYPE_IEEE_FLOAT, pEx->SubFormat)) {
                    pEx->SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
                    pEx->Samples.wValidBitsPerSample = 16;
                    pwfx->wBitsPerSample = 16;
                    pwfx->nBlockAlign = pwfx->nChannels * pwfx->wBitsPerSample / 8;
                    pwfx->nAvgBytesPerSec = pwfx->nBlockAlign * pwfx->nSamplesPerSec;
                } else {
                    printf("Don't know how to coerce mix format to int-16\n");
                    CoTaskMemFree(pwfx);
                    pAudioClient->Release();
                    return E_UNEXPECTED;
                }
            }
            break;

        default:
            printf("Don't know how to coerce WAVEFORMATEX with wFormatTag = 0x%08x to int-16\n", pwfx->wFormatTag);
            CoTaskMemFree(pwfx);
            pAudioClient->Release();
            return E_UNEXPECTED;
    }

    DVAR(pwfx->wFormatTag);
    DVAR(pwfx->wBitsPerSample);
    DVAR(pwfx->nBlockAlign);
    DVAR(pwfx->nAvgBytesPerSec);

	hr = pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_LOOPBACK, 0, 0, pwfx, 0 );
    if (FAILED(hr)) {
        printf("IAudioClient::Initialize failed: hr = 0x%08x\n", hr);
        pAudioClient->Release();
        return hr;
    }

	IAudioCaptureClient *pAudioCaptureClient;
    hr = pAudioClient->GetService(__uuidof(IAudioCaptureClient), (void**)&pAudioCaptureClient);
    if (FAILED(hr)) {
        printf("IAudioClient::GetService(IAudioCaptureClient) failed: hr 0x%08x\n", hr);
        pAudioClient->Release();
        return hr;
    }


    hr = pAudioClient->Start();
    if (FAILED(hr)) {
        printf("IAudioClient::Start failed: hr = 0x%08x\n", hr);
        pAudioCaptureClient->Release();
        pAudioClient->Release();
        return hr;
    }


for (int i = 0; i < 10; ++i)
{

	UINT32 nNextPacketSize;
    hr = pAudioCaptureClient->GetNextPacketSize(&nNextPacketSize);
    if (FAILED(hr)) {
        printf("IAudioCaptureClient::GetNextPacketSize failed on pass %u after %u frames: hr = 0x%08x\n", 0, 0, hr);
        pAudioClient->Stop();
        pAudioCaptureClient->Release();
        pAudioClient->Release();
        return hr;
    }


    // get the captured data
    BYTE *pData;
    UINT32 nNumFramesToRead;
    DWORD dwFlags;

    hr = pAudioCaptureClient->GetBuffer(&pData, &nNumFramesToRead, &dwFlags, nullptr,
        nullptr);
    if (FAILED(hr)) {
        printf("IAudioCaptureClient::GetBuffer failed on pass %u after %u frames: hr = 0x%08x\n", 0, 0, hr);
        pAudioClient->Stop();
        pAudioCaptureClient->Release();
        pAudioClient->Release();
        return hr;
    }

    DVAR(nNumFramesToRead);


    // if (bFirstPacket && AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY == dwFlags) {
        // printf("Probably spurious glitch reported on first packet\n");
    if (0 != dwFlags && AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY != dwFlags) {
        printf("IAudioCaptureClient::GetBuffer set flags to 0x%08x on pass %u after %u frames\n", dwFlags, 0, 0);
        // pAudioClient->Stop();
        // pAudioCaptureClient->Release();
        // pAudioClient->Release();
        // return E_UNEXPECTED;
    }
    else
    	DVAR((int)*pData);

    if (0 == nNumFramesToRead) {
        printf("IAudioCaptureClient::GetBuffer said to read 0 frames on pass %u after %u frames\n", 0, 0);
        pAudioClient->Stop();
        pAudioCaptureClient->Release();
        pAudioClient->Release();
        return E_UNEXPECTED;
    }


    UINT32 nBlockAlign = pwfx->nBlockAlign;
    LONG lBytesToWrite = nNumFramesToRead * nBlockAlign;
    hr = pAudioCaptureClient->ReleaseBuffer(nNumFramesToRead);
}

	pAudioClient->Stop();
    pAudioCaptureClient->Release();
    pAudioClient->Release();


	CoUninitialize();

	return 0;
}