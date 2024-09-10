BMID_API int BGBMID_SoundDev_RecDeInit()
{
	int i;

	waveInStop(hWaveIn);

	waveInReset(hWaveIn);

	if(lpInWaveHdr)
	{
		for(i=0; i<WAV_BUFFERS; i++)
			waveInUnprepareHeader(hWaveIn, lpInWaveHdr+i, sizeof(WAVEHDR));
	}

	waveInClose(hWaveIn);

	if(hInWaveHdr)
	{
		GlobalUnlock(hInWaveHdr); 
		GlobalFree(hInWaveHdr);
	}

	if(hInData)
	{
		GlobalUnlock(hInData);
		GlobalFree(hInData);
	}

	return(0);
}