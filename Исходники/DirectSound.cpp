void DXAudioInput::run() {
	LPDIRECTSOUNDCAPTURE8      pDSCapture;
	LPDIRECTSOUNDCAPTUREBUFFER pDSCaptureBuffer;
	LPDIRECTSOUNDNOTIFY8       pDSNotify;

	DWORD dwBufferSize;
	bool bOk;
	DWORD dwReadyBytes = 0;
	DWORD dwLastReadPos = 0;
	DWORD dwReadPosition;
	DWORD dwCapturePosition;

	LPVOID aptr1, aptr2;
	DWORD nbytes1, nbytes2;

	HRESULT       hr;
	WAVEFORMATEX  wfx;
	DSCBUFFERDESC dscbd;

	pDSCapture = NULL;
	pDSCaptureBuffer = NULL;
	pDSNotify = NULL;

	bOk = false;

	bool failed = false;
	float safety = 2.0f;
	bool didsleep = false;
	bool firstsleep = false;

	Timer t;

	ZeroMemory(&wfx, sizeof(wfx));
	wfx.wFormatTag = WAVE_FORMAT_PCM;

	ZeroMemory(&dscbd, sizeof(dscbd));
	dscbd.dwSize = sizeof(dscbd);

	dscbd.dwBufferBytes = dwBufferSize = iFrameSize * sizeof(short) * NBUFFBLOCKS;
	dscbd.lpwfxFormat = &wfx;

	wfx.nChannels = 1;
	wfx.nSamplesPerSec = iSampleRate;
	wfx.nBlockAlign = 2;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	wfx.wBitsPerSample = 16;

	// Create IDirectSoundCapture using the preferred capture device
	if (! g.s.qbaDXInput.isEmpty()) {
		LPGUID lpguid = reinterpret_cast<LPGUID>(g.s.qbaDXInput.data());
		if (FAILED(hr = DirectSoundCaptureCreate8(lpguid, &pDSCapture, NULL))) {
			failed = true;
		}
	}

	if (! pDSCapture && FAILED(hr = DirectSoundCaptureCreate8(&DSDEVID_DefaultVoiceCapture, &pDSCapture, NULL)))
		qWarning("DXAudioInput: DirectSoundCaptureCreate failed: hr=0x%08lx", hr);
	else if (FAILED(hr = pDSCapture->CreateCaptureBuffer(&dscbd, &pDSCaptureBuffer, NULL)))
		qWarning("DXAudioInput: CreateCaptureBuffer failed: hr=0x%08lx", hr);
	else if (FAILED(hr = pDSCaptureBuffer->QueryInterface(IID_IDirectSoundNotify, reinterpret_cast<void **>(&pDSNotify))))
		qWarning("DXAudioInput: QueryInterface (Notify) failed: hr=0x%08lx", hr);
	else
		bOk = true;



	if (failed)
		g.mw->msgBox(tr("Opening chosen DirectSound Input failed. Default device will be used."));

	qWarning("DXAudioInput: Initialized");

	if (! bOk)
		goto cleanup;

	if (FAILED(hr = pDSCaptureBuffer->Start(DSCBSTART_LOOPING))) {
		qWarning("DXAudioInput: Start failed: hr=0x%08lx", hr);
	} else {
		while (bRunning) {
			firstsleep = true;
			didsleep = false;

			do {
				if (FAILED(hr = pDSCaptureBuffer->GetCurrentPosition(&dwCapturePosition, &dwReadPosition))) {
					qWarning("DXAudioInput: GetCurrentPosition failed: hr=0x%08lx", hr);
					bRunning = false;
					break;
				}
				if (dwReadPosition < dwLastReadPos)
					dwReadyBytes = (dwBufferSize - dwLastReadPos) + dwReadPosition;
				else
					dwReadyBytes = dwReadPosition - dwLastReadPos;

				if (static_cast<int>(dwReadyBytes) < sizeof(short) * iFrameSize) {
					double msecleft = 20.0 - (dwReadyBytes * 20.0) / (sizeof(short) * iFrameSize);

					if (didsleep)
						safety *= 1.1f;
					else if (firstsleep)
						safety *= 0.998f;

					int msec = static_cast<int>(msecleft + (firstsleep ? safety : 0.0));

					msleep(msec);

					didsleep = true;
					firstsleep = false;
				}
			} while (static_cast<int>(dwReadyBytes) < sizeof(short) * iFrameSize);

			// Desynchonized?
			if (dwReadyBytes > (dwBufferSize / 2)) {
				qWarning("DXAudioInput: Lost synchronization");
				dwLastReadPos = dwReadPosition;
			} else if (bRunning) {
				if (FAILED(hr = pDSCaptureBuffer->Lock(dwLastReadPos, sizeof(short) * iFrameSize, &aptr1, &nbytes1, &aptr2, &nbytes2, 0))) {
					qWarning("DXAudioInput: Lock from %ld (%d bytes) failed: hr=0x%08lx",dwLastReadPos, sizeof(short) * iFrameSize, hr);
					bRunning = false;
					break;
				}

				if (aptr1 && nbytes1)
					CopyMemory(psMic, aptr1, nbytes1);

				if (aptr2 && nbytes2)
					CopyMemory(psMic+nbytes1/2, aptr2, nbytes2);

				if (FAILED(hr = pDSCaptureBuffer->Unlock(aptr1, nbytes1, aptr2, nbytes2))) {
					qWarning("DXAudioInput: Unlock failed: hr=0x%08lx", hr);
					bRunning = false;
					break;
				}

				dwLastReadPos = (dwLastReadPos + sizeof(short) * iFrameSize) % dwBufferSize;

				encodeAudioFrame();
			}
		}
		if (! FAILED(hr))
			pDSCaptureBuffer->Stop();
	}
	if (FAILED(hr)) {
		g.mw->msgBox(tr("Lost DirectSound input device."));
	}

cleanup:
	if (! bOk) {
		g.mw->msgBox(tr("Opening chosen DirectSound Input device failed. No microphone capture will be done."));
	}
	if (pDSNotify)
		pDSNotify->Release();
	if (pDSCaptureBuffer)
		pDSCaptureBuffer->Release();
	if (pDSCapture)
		pDSCapture->Release();
}