void *DSOUND_Capture_Init (int rate)
{
	dsndcapture_t *result;
	DSCBUFFERDESC bufdesc = {0};
	WAVEFORMATEX  wfxFormat = {0};

	Com_DPrintf("DSOUND_Capture_Init: rate %d\n", rate);

	wfxFormat.wFormatTag = WAVE_FORMAT_PCM;
    wfxFormat.nChannels = 1;
    wfxFormat.nSamplesPerSec = rate;
	wfxFormat.wBitsPerSample = 8*inputwidth;
    wfxFormat.nBlockAlign = wfxFormat.nChannels * (wfxFormat.wBitsPerSample / 8);
	wfxFormat.nAvgBytesPerSec = wfxFormat.nSamplesPerSec * wfxFormat.nBlockAlign;
    wfxFormat.cbSize = 0;

	bufdesc.dwSize = sizeof(bufdesc);
	bufdesc.dwBufferBytes = bufferbytes;
	bufdesc.dwFlags = 0;
	bufdesc.dwReserved = 0;
	bufdesc.lpwfxFormat = &wfxFormat;

	result = Z_Malloc(sizeof(*result));
	if (FAILED(DirectSoundCaptureCreate(NULL, &result->DSCapture, NULL)))
	{
		Com_Printf_State (PRINT_FAIL, "DirectSound: Couldn't create a capture device\n");
	}
	else if (FAILED(IDirectSoundCapture_CreateCaptureBuffer(result->DSCapture, &bufdesc, &result->DSCaptureBuffer, NULL)))
	{
		Com_Printf_State (PRINT_FAIL, "DirectSound: Couldn't create a capture buffer\n");	
	}
	else
	{
		Com_DPrintf("DSOUND_Capture_Init: OK\n");
		return result;	
	}

	// failure, lets clean up.

	if (result->DSCapture)
	{
		IDirectSoundCapture_Release(result->DSCapture);	
	}

	Z_Free(result);

	return NULL;
}