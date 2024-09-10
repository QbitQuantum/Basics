/* IDirectMusicPerformance8 Interface part follow: */
static HRESULT WINAPI IDirectMusicPerformance8Impl_InitAudio (LPDIRECTMUSICPERFORMANCE8 iface, 
						      IDirectMusic** ppDirectMusic, 
						      IDirectSound** ppDirectSound, 
						      HWND hWnd, 
						      DWORD dwDefaultPathType, 
						      DWORD dwPChannelCount, 
						      DWORD dwFlags, 
						      DMUS_AUDIOPARAMS* pParams) {

	IDirectSound* dsound = NULL;
	HRESULT hr = S_OK;
	
        IDirectMusicPerformance8Impl *This = (IDirectMusicPerformance8Impl *)iface;
	FIXME("(%p, %p, %p, %p, %x, %u, %x, %p): to check\n", This, ppDirectMusic, ppDirectSound, hWnd, dwDefaultPathType, dwPChannelCount, dwFlags, pParams);

	if (This->pDirectMusic || This->pDirectSound)
	  return DMUS_E_ALREADY_INITED;

	if (NULL != ppDirectSound && NULL != *ppDirectSound) {
	  dsound = *ppDirectSound;
	} else {
	  hr = DirectSoundCreate8 (NULL, (LPDIRECTSOUND8*) &dsound, NULL);
          FIXME("return dsound(%p,%d)\n", dsound, hr);
	  if (FAILED(hr) || !dsound)
	    return DSERR_NODRIVER;
	  if (ppDirectSound)
	    *ppDirectSound = dsound;  
	}
	
	IDirectMusicPerformance8Impl_Init(iface, ppDirectMusic, dsound, hWnd);

	/* Init increases the ref count of the dsound object. Decrement it if the app doesn't want a pointer to the object. */
	if (NULL == ppDirectSound) {
	  IDirectSound_Release(This->pDirectSound);
	}

	/* as seen in msdn we need params init before audio path creation */
	if (NULL != pParams) {
	  This->pParams = *pParams;
	} else {
	  /* TODO, how can i fill the struct as seen on msdn */
	  memset(&This->pParams, 0, sizeof(DMUS_AUDIOPARAMS));
	  This->pParams.dwSize = sizeof(DMUS_AUDIOPARAMS);
	  This->pParams.fInitNow = FALSE;
	  This->pParams.dwValidData = DMUS_AUDIOPARAMS_FEATURES | DMUS_AUDIOPARAMS_VOICES | DMUS_AUDIOPARAMS_SAMPLERATE | DMUS_AUDIOPARAMS_DEFAULTSYNTH;
	  This->pParams.dwVoices = 64;
	  This->pParams.dwSampleRate = (DWORD) 22.050; 
	  This->pParams.dwFeatures = dwFlags;
	  This->pParams.clsidDefaultSynth = CLSID_DirectMusicSynthSink;
	}
	hr = IDirectMusicPerformance8_CreateStandardAudioPath(iface, dwDefaultPathType, dwPChannelCount, FALSE, &This->pDefaultPath);

	PostMessageToProcessMsgThread(This, PROCESSMSG_START);

	return hr;
}