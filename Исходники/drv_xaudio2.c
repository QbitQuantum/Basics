static int XAudio2_Init(void) {
	UINT32 flags;
	DWORD thread_id;
	WAVEFORMATEX wfmt;

	memset(&wfmt, 0, sizeof(WAVEFORMATEX));
	wfmt.wFormatTag= (md_mode & DMODE_FLOAT)? WAVE_FORMAT_IEEE_FLOAT : WAVE_FORMAT_PCM;
	wfmt.nChannels = (md_mode & DMODE_STEREO)? 2: 1;
	wfmt.nSamplesPerSec = md_mixfreq;
	wfmt.wBitsPerSample = (md_mode & DMODE_FLOAT)? 32: (md_mode & DMODE_16BITS)? 16: 8;
	wfmt.nBlockAlign = (wfmt.wBitsPerSample * wfmt.nChannels) / 8;
	wfmt.nAvgBytesPerSec = wfmt.nSamplesPerSec * wfmt.nBlockAlign;
	if (wfmt.nSamplesPerSec < XAUDIO2_MIN_SAMPLE_RATE ||
	    wfmt.nSamplesPerSec > XAUDIO2_MAX_SAMPLE_RATE ||
	    wfmt.nChannels > XAUDIO2_MAX_AUDIO_CHANNELS) {
		return 1;
	}

	current_buf = 0;
	flags = 0;
#if defined(_DEBUG) && !defined(DRV_XAUDIO28)
/*	flags |= XAUDIO2_DEBUG_ENGINE;*/
#endif
#ifndef _XBOX
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	if (FAILED(XAudio2Create(&pXAudio2, flags, XAUDIO2_DEFAULT_PROCESSOR))) {
		goto fail;
	}
#if defined(DRV_XAUDIO28)
	if (FAILED(IXAudio2_CreateMasteringVoice(pXAudio2, &pMasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE,
						 0, NULL, NULL, AudioCategory_Other))) {
		goto fail;
	}
#else
	if (FAILED(IXAudio2_CreateMasteringVoice(pXAudio2, &pMasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL))) {
		goto fail;
	}
#endif
	if (FAILED(IXAudio2_CreateSourceVoice(pXAudio2, &pSourceVoice, &wfmt, 0, 1.0f, pcbVoice, NULL, NULL))) {
		goto fail;
	}
#ifndef __cplusplus
	if ((hBufferEvent = CreateEvent(NULL, FALSE, FALSE, "libmikmod XAudio2 Driver buffer Event")) == NULL) {
		goto fail;
	}
#endif
	if ((UpdateBufferHandle = CreateThread(NULL, 0, UpdateBufferProc, NULL, CREATE_SUSPENDED, &thread_id)) == NULL) {
		goto fail;
	}
#if defined HAVE_SSE2
	/* this test only works on Windows XP or later */
	if (IsProcessorFeaturePresent(PF_XMMI64_INSTRUCTIONS_AVAILABLE)) {
		md_mode|=DMODE_SIMDMIXER;
	}
#endif
	return VC_Init();

fail:
	if (pSourceVoice) {
		IXAudio2SourceVoice_DestroyVoice(pSourceVoice);
		pSourceVoice = NULL;
	}
	if (pMasterVoice) {
		IXAudio2MasteringVoice_DestroyVoice(pMasterVoice);
		pMasterVoice = NULL;
	}
	if (pXAudio2) {
		IXAudio2_Release(pXAudio2);
		pXAudio2 = NULL;
	}
#ifndef _XBOX
	CoUninitialize();
#endif
	return 1;
}