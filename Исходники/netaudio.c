// ////////////////////////////////////////////////////////////////////////
BOOL NETinitAudioCapture(VOID)
{
	HRESULT				hr;
	WAVEFORMATEX        wfx;

	NetPlay.bAllowCaptureRecord = FALSE;

	hr = DirectSoundCaptureCreate(	NULL,&lpDirectSoundCapture,	NULL);
	if(hr != DS_OK)
	{
		DBPRINTF(("NETPLAY:Failed to create capture interface."));
		if(hr == DSERR_NOAGGREGATION)
		{
			DBPRINTF(("DSERR_NOAGGREGATION"));
		}
		if(hr == DSERR_OUTOFMEMORY)
		{
			DBPRINTF(("DSERR_OUTOFMEMORY"));
		}
		if(hr == DSERR_INVALIDPARAM)
		{
			DBPRINTF(("DSERR_INVALIDPARAM"));
		}
		return FALSE;
	}
	
	ZeroMemory(&captureBuff, sizeof(captureBuff));
	lpDirectSoundCaptureBuffer = NULL;
 
	wfx.wFormatTag			= WAVE_FORMAT_PCM; 	//set audio format
	wfx.nChannels			= AUDIOCHANNELS;
	wfx.nSamplesPerSec		= SAMPLERATE;			
	wfx.nAvgBytesPerSec		= SAMPLERATE * (BITSPERSAMPLE /8) * AUDIOCHANNELS  ;	
	wfx.nBlockAlign			= (AUDIOCHANNELS * BITSPERSAMPLE) / 8 ; 
	wfx.wBitsPerSample		= BITSPERSAMPLE;	
	wfx.cbSize				= 0;	

	captureBuff.dwSize		= sizeof(DSCBUFFERDESC);
	captureBuff.dwFlags		= DSCBCAPS_WAVEMAPPED;
	captureBuff.dwBufferBytes= SAMPLETIME * wfx.nAvgBytesPerSec;		// SAMPLETIME second’s worth of audio
	captureBuff.lpwfxFormat =  &wfx;
 
	hr = IDirectSoundCapture_CreateCaptureBuffer(lpDirectSoundCapture,
												&captureBuff,
												&lpDirectSoundCaptureBuffer,
												NULL);	
	if(hr != DS_OK)
	{
		if( hr == DSERR_INVALIDPARAM)
		{DBPRINTF(("NETPLAY:no capturebuffer,inv param"));
		}
		if( hr == DSERR_BADFORMAT)
		{DBPRINTF(("NETPLAY:no capturebuffer,badformat"));
		}
		if( hr == DSERR_GENERIC)
		{DBPRINTF(("NETPLAY:no capturebuffer,generic"));
		}
		if( hr == DSERR_NODRIVER)
		{DBPRINTF(("NETPLAY:no capturebuffer,nodriver"));
		}
		if( hr == DSERR_OUTOFMEMORY)
		{DBPRINTF(("NETPLAY:no capturebuffer,memory"));	
		}
		if( hr == DSERR_UNINITIALIZED)
		{DBPRINTF(("NETPLAY:no capturebuffer,uninit"));
		}
		return FALSE;
	}

	NetPlay.bAllowCaptureRecord = TRUE;
//	allowCapture = TRUE;
	return(TRUE);
}