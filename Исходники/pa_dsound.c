/************************************************************************************
** Extract capabilities info from each device.
*/
static BOOL CALLBACK Pa_EnumProc(LPGUID lpGUID, 
				         LPCTSTR lpszDesc,
				         LPCTSTR lpszDrvName, 
				         LPVOID lpContext )
{
	HRESULT    hr;
	LPDIRECTSOUND          lpDirectSound;
#if SUPPORT_AUDIO_CAPTURE
	LPDIRECTSOUNDCAPTURE   lpDirectSoundCapture;
#endif /* SUPPORT_AUDIO_CAPTURE */
	int        isInput  = (int) lpContext;  /* Passed from Pa_CountDevices() */
	internalPortAudioDevice *pad;
		
	if( sDeviceIndex >= sNumDevices )
	{
		sEnumerationError = paInternalError;
		return FALSE;
	}
	pad = &sDevices[sDeviceIndex];
/* Copy GUID to static array. Set pointer. */
	if( lpGUID == NULL )
	{
		pad->pad_lpGUID = NULL;
	}
	else
	{
		memcpy( &pad->pad_GUID, lpGUID, sizeof(GUID) );
		pad->pad_lpGUID = &pad->pad_GUID;
	}
	pad->pad_Info.sampleRates = pad->pad_SampleRates;  /* Point to array. */
/* Allocate room for descriptive name. */
	if( lpszDesc != NULL )
	{
		int len = strlen(lpszDesc);
		pad->pad_Info.name = (char *)malloc( len+1 );
		if( pad->pad_Info.name == NULL )
		{
			sEnumerationError = paInsufficientMemory;
			return FALSE;
		}
		memcpy( (void *) pad->pad_Info.name, lpszDesc, len+1 );
	}
#if SUPPORT_AUDIO_CAPTURE
	if( isInput )
	{
	/********** Input ******************************/
		DSCCAPS     caps;
		if( lpGUID == NULL ) sDefaultInputDeviceID = sDeviceIndex;
		hr = DirectSoundCaptureCreate(  lpGUID, &lpDirectSoundCapture,   NULL );
		if( hr != DS_OK )
		{
			pad->pad_Info.maxInputChannels = 0;
			DBUG(("Cannot create Capture for %s. Result = 0x%x\n", lpszDesc, hr ));
		}
		else
		{
	/* Query device characteristics. */
			caps.dwSize = sizeof(caps);
			IDirectSoundCapture_GetCaps( lpDirectSoundCapture, &caps );
			/* printf("caps.dwFormats = 0x%x\n", caps.dwFormats ); */
			pad->pad_Info.maxInputChannels = caps.dwChannels;
	/* Determine sample rates from flags. */
			if( caps.dwChannels == 2 )
			{
				int index = 0;
				if( caps.dwFormats & WAVE_FORMAT_1S16) pad->pad_SampleRates[index++] = 11025.0;
				if( caps.dwFormats & WAVE_FORMAT_2S16) pad->pad_SampleRates[index++] = 22050.0;
				if( caps.dwFormats & WAVE_FORMAT_4S16) pad->pad_SampleRates[index++] = 44100.0;
				pad->pad_Info.numSampleRates = index;
			}
			else if( caps.dwChannels == 1 )
			{
				int index = 0;
				if( caps.dwFormats & WAVE_FORMAT_1M16) pad->pad_SampleRates[index++] = 11025.0;
				if( caps.dwFormats & WAVE_FORMAT_2M16) pad->pad_SampleRates[index++] = 22050.0;
				if( caps.dwFormats & WAVE_FORMAT_4M16) pad->pad_SampleRates[index++] = 44100.0;
				pad->pad_Info.numSampleRates = index;
			}
			else pad->pad_Info.numSampleRates = 0;
			IDirectSoundCapture_Release( lpDirectSoundCapture );
		}
	}
	else
#endif /* SUPPORT_AUDIO_CAPTURE */
	{
	/********** Output ******************************/
		DSCAPS     caps;
		if( lpGUID == NULL ) sDefaultOutputDeviceID = sDeviceIndex;
	/* Create interfaces for each object. */
		hr = DirectSoundCreate(  lpGUID, &lpDirectSound,   NULL );
		if( hr != DS_OK )
		{
			pad->pad_Info.maxOutputChannels = 0;
			DBUG(("Cannot create dsound for %s. Result = 0x%x\n", lpszDesc, hr ));
		}
		else
		{
		/* Query device characteristics. */
			caps.dwSize = sizeof(caps);
			IDirectSound_GetCaps( lpDirectSound, &caps );
			pad->pad_Info.maxOutputChannels = ( caps.dwFlags & DSCAPS_PRIMARYSTEREO ) ? 2 : 1;
		/* Get sample rates. */
			pad->pad_SampleRates[0] = (double) caps.dwMinSecondarySampleRate;
			pad->pad_SampleRates[1] = (double) caps.dwMaxSecondarySampleRate;
			if( caps.dwFlags & DSCAPS_CONTINUOUSRATE ) pad->pad_Info.numSampleRates = -1;
			else if( caps.dwMinSecondarySampleRate == caps.dwMaxSecondarySampleRate )
			{
				if( caps.dwMinSecondarySampleRate == 0 )
				{
			/*
			** On my Thinkpad 380Z, DirectSoundV6 returns min-max=0 !!
			** But it supports continuous sampling.
			** So fake range of rates, and hope it really supports it.
			*/
					pad->pad_SampleRates[0] = 11025.0f;
					pad->pad_SampleRates[1] = 48000.0f;
					pad->pad_Info.numSampleRates = -1; /* continuous range */
					
					DBUG(("PA - Reported rates both zero. Setting to fake values for device #%d\n", sDeviceIndex ));
				}
				else
				{
					pad->pad_Info.numSampleRates = 1;
				}
			}
			else if( (caps.dwMinSecondarySampleRate < 1000.0) && (caps.dwMaxSecondarySampleRate > 50000.0) )
			{
			/* The EWS88MT drivers lie, lie, lie. The say they only support two rates, 100 & 100000.
			** But we know that they really support a range of rates!
			** So when we see a ridiculous set of rates, assume it is a range.
			*/
				pad->pad_Info.numSampleRates = -1;
				DBUG(("PA - Sample rate range used instead of two odd values for device #%d\n", sDeviceIndex ));
			}
			else pad->pad_Info.numSampleRates = 2;
			IDirectSound_Release( lpDirectSound );
		}
	}
	pad->pad_Info.nativeSampleFormats = paInt16;
	sDeviceIndex++;
	return( TRUE );
}