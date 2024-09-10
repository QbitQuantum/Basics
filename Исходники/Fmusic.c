signed char FMUSIC_PlaySong(FMUSIC_MODULE *mod)
{
	int				count;
	FMUSIC_CHANNEL	*cptr;
	int				totalblocks; 

	if (!mod) 
    {
		return FALSE;
    }

	lastmodplay = mod ;
	volumeUpdateSpeed = 30 ;
	FMUSIC_StopSong(mod);

	if (!FSOUND_File_OpenCallback || !FSOUND_File_CloseCallback || !FSOUND_File_ReadCallback || !FSOUND_File_SeekCallback || !FSOUND_File_TellCallback)
    {
		return FALSE;
    }

	// ========================================================================================================
	// INITIALIZE SOFTWARE MIXER 
	// ========================================================================================================

	FSOUND_OOMixRate    = 1.0f / (float)FSOUND_MixRate;
	FSOUND_BlockSize    = ((FSOUND_MixRate * FSOUND_LATENCY / 1000) + 3) & 0xFFFFFFFC;	// Number of *samples*
	FSOUND_BufferSize   = FSOUND_BlockSize * (FSOUND_BufferSizeMs / FSOUND_LATENCY);	// make it perfectly divisible by granularity
	FSOUND_BufferSize <<= 1;	// double buffer

	mix_volumerampsteps      = FSOUND_MixRate * FSOUND_VOLUMERAMP_STEPS / 44100;
	mix_1overvolumerampsteps = 1.0f / mix_volumerampsteps;
    totalblocks              = FSOUND_BufferSize / FSOUND_BlockSize;

	//=======================================================================================
	// ALLOC GLOBAL CHANNEL POOL
	//=======================================================================================
	memset(FSOUND_Channel, 0, sizeof(FSOUND_CHANNEL) * 256);

	// ========================================================================================================
	// SET UP CHANNELS
	// ========================================================================================================

	for (count=0; count < 256; count++)
	{
		FSOUND_Channel[count].index = count;
		FSOUND_Channel[count].speedhi = 1;
	}

	mod->globalvolume       = mod->defaultglobalvolume;
	mod->globalWantedVolume = mod->globalvolume ;
 	mod->speed              = (int)mod->defaultspeed;
	mod->row                = 0;
	mod->order              = 0;
	mod->nextorder          = -1;
	mod->nextrow            = -1;
	mod->mixer_samplesleft  = 0;
	mod->tick               = 0;
	mod->patterndelay       = 0;
	mod->time_ms            = 0;

	FMUSIC_SetBPM(mod, mod->defaultbpm);

	memset(FMUSIC_Channel, 0, mod->numchannels * sizeof(FMUSIC_CHANNEL));
//	memset(FSOUND_Channel, 0, 256 * sizeof(FSOUND_CHANNEL));

	for (count=0; count < mod->numchannels; count++)
	{
		cptr = &FMUSIC_Channel[count];
		cptr->cptr = &FSOUND_Channel[count];
	}

	FMUSIC_PlayingSong = mod;

	FMUSIC_TimeInfo = FSOUND_Memory_Calloc(sizeof(FMUSIC_TIMMEINFO) * totalblocks);

	// ========================================================================================================
	// PREPARE THE OUTPUT
	// ========================================================================================================
	{
		WAVEFORMATEX	pcmwf;
		UINT			hr;

		// ========================================================================================================
		// INITIALIZE WAVEOUT
		// ========================================================================================================
		pcmwf.wFormatTag		= WAVE_FORMAT_PCM; 
		pcmwf.nChannels			= 2;
		pcmwf.wBitsPerSample	= 16; 
		pcmwf.nBlockAlign		= pcmwf.nChannels * pcmwf.wBitsPerSample / 8;
		pcmwf.nSamplesPerSec	= FSOUND_MixRate;
		pcmwf.nAvgBytesPerSec	= pcmwf.nSamplesPerSec * pcmwf.nBlockAlign; 
		pcmwf.cbSize			= 0;

		hr = waveOutOpen(&FSOUND_WaveOutHandle, WAVE_MAPPER, &pcmwf, 0, 0, 0);

		if (hr) 
        {
			return FALSE;
        }
	}

	{
		WAVEHDR	*wavehdr;
		int	length = 0;

		// CREATE AND START LOOPING WAVEOUT BLOCK
		wavehdr = &FSOUND_MixBlock.wavehdr;

		length = FSOUND_BufferSize;
		length <<= 2;	// 16bits

		FSOUND_MixBlock.data = FSOUND_Memory_Calloc(length);
		
		wavehdr->dwFlags			= WHDR_BEGINLOOP | WHDR_ENDLOOP;
		wavehdr->lpData				= (LPSTR)FSOUND_MixBlock.data;
		wavehdr->dwBufferLength		= length;
		wavehdr->dwBytesRecorded	= 0;
		wavehdr->dwUser				= 0;
		wavehdr->dwLoops			= -1;
		waveOutPrepareHeader(FSOUND_WaveOutHandle, wavehdr, sizeof(WAVEHDR));
	}

	// ========================================================================================================
	// ALLOCATE MIXBUFFER
	// ========================================================================================================

	FSOUND_MixBufferMem = (signed char *)FSOUND_Memory_Calloc((FSOUND_BufferSize << 3) + 256);
	FSOUND_MixBuffer = (signed char *)(((unsigned int)FSOUND_MixBufferMem + 15) & 0xFFFFFFF0);

	// ========================================================================================================
	// PREFILL THE MIXER BUFFER 
	// ========================================================================================================

	do 
	{
		FSOUND_Software_Fill();
	} while (FSOUND_Software_FillBlock);

	// ========================================================================================================
	// START THE OUTPUT
	// ========================================================================================================

	waveOutWrite(FSOUND_WaveOutHandle, &FSOUND_MixBlock.wavehdr, sizeof(WAVEHDR));

	{
		DWORD	FSOUND_dwThreadId;

		// ========================================================================================================
		// CREATE THREADS / TIMERS (last)
		// ========================================================================================================
		FSOUND_Software_Exit = FALSE;

		FSOUND_Software_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FSOUND_Software_DoubleBufferThread, 0,0, &FSOUND_dwThreadId);

		SetThreadPriority(FSOUND_Software_hThread, THREAD_PRIORITY_TIME_CRITICAL);	// THREAD_PRIORITY_HIGHEST);
	}
	return TRUE;
}