DWORD WINAPI wf_rdpsnd_wasapi_thread(LPVOID lpParam)
{
	IMMDeviceEnumerator *pEnumerator = NULL;
	IMMDevice *pDevice = NULL;
	IAudioClient *pAudioClient = NULL;
	IAudioCaptureClient *pCaptureClient = NULL;
	WAVEFORMATEX *pwfx = NULL;
	HRESULT hr;
	REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
	REFERENCE_TIME hnsActualDuration;
	UINT32 bufferFrameCount;
	UINT32 numFramesAvailable;
	UINT32 packetLength = 0;
	UINT32 dCount = 0;
	BYTE *pData;

	wfPeerContext* context;
	wfInfo* wfi;

	wfi = wf_info_get_instance();
	context = (wfPeerContext*)lpParam;

	CoInitialize(NULL);
	hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (void **) &pEnumerator);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to cocreate device enumerator\n"));
		exit(1);
	}

	hr = pEnumerator->lpVtbl->GetDevice(pEnumerator, devStr, &pDevice);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to cocreate get device\n"));
		exit(1);
	}

	hr = pDevice->lpVtbl->Activate(pDevice, &IID_IAudioClient, CLSCTX_ALL, NULL, (void **)&pAudioClient);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to activate audio client\n"));
		exit(1);
	}

	hr = pAudioClient->lpVtbl->GetMixFormat(pAudioClient, &pwfx);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to get mix format\n"));
		exit(1);
	}

	pwfx->wFormatTag = wfi->agreed_format->wFormatTag;
	pwfx->nChannels = wfi->agreed_format->nChannels;
	pwfx->nSamplesPerSec = wfi->agreed_format->nSamplesPerSec;
	pwfx->nAvgBytesPerSec = wfi->agreed_format->nAvgBytesPerSec;
	pwfx->nBlockAlign = wfi->agreed_format->nBlockAlign;
	pwfx->wBitsPerSample = wfi->agreed_format->wBitsPerSample;
	pwfx->cbSize = wfi->agreed_format->cbSize;

	hr = pAudioClient->lpVtbl->Initialize(
		pAudioClient, AUDCLNT_SHAREMODE_SHARED, 0,
		hnsRequestedDuration, 0, pwfx, NULL);

	if (FAILED(hr))
	{
		_tprintf(_T("Failed to initialize the audio client\n"));
		exit(1);
	}

	hr = pAudioClient->lpVtbl->GetBufferSize(pAudioClient, &bufferFrameCount);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to get buffer size\n"));
		exit(1);
	}

	hr = pAudioClient->lpVtbl->GetService(pAudioClient, &IID_IAudioCaptureClient, (void **) &pCaptureClient);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to get the capture client\n"));
		exit(1);
	}

	hnsActualDuration = (UINT32)REFTIMES_PER_SEC * bufferFrameCount / pwfx->nSamplesPerSec;

	hr = pAudioClient->lpVtbl->Start(pAudioClient);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to start capture\n"));
		exit(1);
	}

	dCount = 0;
	while(wfi->snd_stop == FALSE)
	{
		DWORD flags;

		Sleep(hnsActualDuration/REFTIMES_PER_MILLISEC/2);

		hr = pCaptureClient->lpVtbl->GetNextPacketSize(pCaptureClient, &packetLength);
		if (FAILED(hr))
		{
			_tprintf(_T("Failed to get packet length\n"));
			exit(1);
		}

		while (packetLength != 0)
		{
			hr = pCaptureClient->lpVtbl->GetBuffer(pCaptureClient, &pData, &numFramesAvailable, &flags, NULL, NULL);
			if (FAILED(hr))
			{
				_tprintf(_T("Failed to get buffer\n"));
				exit(1);
			}

			//Here we are writing the audio data
			//not sure if this flag is ever set by the system; msdn is not clear about it
			if (!(flags & AUDCLNT_BUFFERFLAGS_SILENT))
				context->rdpsnd->SendSamples(context->rdpsnd, pData, packetLength, (UINT16)(GetTickCount() & 0xffff));

			hr = pCaptureClient->lpVtbl->ReleaseBuffer(pCaptureClient, numFramesAvailable);
			if (FAILED(hr))
			{
				_tprintf(_T("Failed to release buffer\n"));
				exit(1);
			}

			hr = pCaptureClient->lpVtbl->GetNextPacketSize(pCaptureClient, &packetLength);
			if (FAILED(hr))
			{
				_tprintf(_T("Failed to get packet length\n"));
				exit(1);
			}
		}
	}

	pAudioClient->lpVtbl->Stop(pAudioClient);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to stop audio client\n"));
		exit(1);
	}

	CoTaskMemFree(pwfx);

	if (pEnumerator != NULL)
		pEnumerator->lpVtbl->Release(pEnumerator);

	if (pDevice != NULL)
		pDevice->lpVtbl->Release(pDevice);

	if (pAudioClient != NULL)
		pAudioClient->lpVtbl->Release(pAudioClient);

	if (pCaptureClient != NULL)
		pCaptureClient->lpVtbl->Release(pCaptureClient);

	CoUninitialize();

	return 0;
}