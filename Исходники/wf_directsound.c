int wf_directsound_activate(RdpsndServerContext* context)
{
	HRESULT hr;
	wfInfo* wfi;
	
	LPDIRECTSOUNDCAPTUREBUFFER  pDSCB;

	wfi = wf_info_get_instance();
	if (!wfi)
	{
		WLog_ERR(TAG, "Failed to wfi instance");
		return 1;
	}
	WLog_DBG(TAG, "RDPSND (direct sound) Activated");
	hr = DirectSoundCaptureCreate8(NULL, &cap, NULL);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "Failed to create sound capture device");
		return 1;
	}

	WLog_INFO(TAG, "Created sound capture device");
	dscbd.dwSize = sizeof(DSCBUFFERDESC);
	dscbd.dwFlags = 0;
	dscbd.dwBufferBytes = wfi->agreed_format->nAvgBytesPerSec;
	dscbd.dwReserved = 0;
	dscbd.lpwfxFormat = wfi->agreed_format;
	dscbd.dwFXCount = 0;
	dscbd.lpDSCFXDesc = NULL;

	hr = cap->lpVtbl->CreateCaptureBuffer(cap, &dscbd, &pDSCB, NULL);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "Failed to create capture buffer");
	}

	WLog_INFO(TAG, "Created capture buffer");
	hr = pDSCB->lpVtbl->QueryInterface(pDSCB, &IID_IDirectSoundCaptureBuffer8, (LPVOID*)&capBuf);
	if (FAILED(hr))
	{
		WLog_ERR(TAG, "Failed to QI capture buffer");
	}
	WLog_INFO(TAG, "Created IDirectSoundCaptureBuffer8");
	pDSCB->lpVtbl->Release(pDSCB);
	lastPos = 0;

	CreateThread(NULL, 0, wf_rdpsnd_directsound_thread, latestPeer, 0, NULL);

	return 0;
}