APU_DX::APU_DX(void)
{
	buffer = NULL;
	active = false;
	buf.sample_rate(48000);
	buf.clock_rate(BASERATE);

	apu.output(&buf);
	time = 0;

	if (DS_OK != DirectSoundCreate(NULL, &lpDS, NULL))
		MessageBox(NULL, "DirectSoundCreate failed", "", MB_OK);
//	if (DS_OK != IDirectSound_SetCooperativeLevel(lpDS, NULL /*hWnd*/, DSSCL_PRIORITY))
//		MessageBox(NULL, "IDirectSound_SetCooperativeLevel failed", "", MB_OK);


	ZeroMemory(&wf, sizeof(WAVEFORMATEX));
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 1;
	wf.nSamplesPerSec = 48000;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.wBitsPerSample / 8 * wf.nChannels;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;



	bufferdesc.dwSize = sizeof(DSBUFFERDESC); 
	bufferdesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLVOLUME; 
	bufferdesc.dwBufferBytes = (wf.nAvgBytesPerSec * BUFFER_MSEC)/1000;

	bufferdesc.dwReserved = 0; 
	bufferdesc.lpwfxFormat = &wf; 

	if (DS_OK != lpDS->CreateSoundBuffer(&bufferdesc, &buffer, NULL))
	{
		//MessageBox(NULL, "CreateSoundBuffer failed", "", MB_OK);
		return;
	}
	active = true;

	loThreshold = (int)((wf.nAvgBytesPerSec / 60) * 1.5);
	hiThreshold = (int)(wf.nAvgBytesPerSec / 60);

	writeBufferSize = loThreshold;
	bufferOffset = bufferdesc.dwBufferBytes - writeBufferSize;
	samplesPerFrame = wf.nSamplesPerSec / 60.0;
	buffer->SetCurrentPosition(0);
	buffer->Play(0, 0, DSBPLAY_LOOPING);

	apu.dmc_reader( DMCRead, this );
}