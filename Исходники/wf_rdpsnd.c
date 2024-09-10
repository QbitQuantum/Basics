static void wf_peer_rdpsnd_activated(rdpsnd_server_context* context)
{
	HRESULT hr;
	
	LPDIRECTSOUNDCAPTUREBUFFER  pDSCB;
	WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 2, 44100, BYTESPERSEC, 4, 16, 0};


	printf("RDPSND Activated\n");

	hr = DirectSoundCaptureCreate8(NULL, &cap, NULL);

	if (FAILED(hr))
	{
		_tprintf(_T("Failed to create sound capture device\n"));
		return;
	}
	_tprintf(_T("Created sound capture device\n"));

	dscbd.dwSize = sizeof(DSCBUFFERDESC);
	dscbd.dwFlags = 0;
	dscbd.dwBufferBytes = BYTESPERSEC;
	dscbd.dwReserved = 0;
	dscbd.lpwfxFormat = &wfx;
	dscbd.dwFXCount = 0;
	dscbd.lpDSCFXDesc = NULL;

	hr = cap->lpVtbl->CreateCaptureBuffer(cap, &dscbd, &pDSCB, NULL);

	if (FAILED(hr))
	{
		_tprintf(_T("Failed to create capture buffer\n"));
	}
	_tprintf(_T("Created capture buffer"));

	hr = pDSCB->lpVtbl->QueryInterface(pDSCB, &IID_IDirectSoundCaptureBuffer8, (LPVOID*)&capBuf);
	if (FAILED(hr))
	{
		_tprintf(_T("Failed to QI capture buffer\n"));
	}
	_tprintf(_T("Created IDirectSoundCaptureBuffer8\n"));
	pDSCB->lpVtbl->Release(pDSCB); 

	context->SelectFormat(context, 4);
	context->SetVolume(context, 0x7FFF, 0x7FFF);
	capturePos = 0;

	CreateThread(NULL, 0, wf_rdpsnd_thread, latestPeer, 0, NULL);


}