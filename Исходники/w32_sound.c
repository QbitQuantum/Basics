FRBC2CI_API void SoundDev_Submit()
{
	LPWAVEHDR	h;
	int			wResult;

	while(1)
	{
		if(snd_completed==snd_sent)
		{
//			printf("Sound overrun\n");
			break;
		}

		if(!(lpWaveHdr[snd_completed&WAV_MASK].dwFlags&WHDR_DONE))
			break;

		snd_completed++;	// this buffer has been played
	}

	while(((snd_sent-snd_completed)>>sample16)<4)
	{
		h=lpWaveHdr+(snd_sent&WAV_MASK);

		snd_sent++;

		wResult=waveOutWrite(hWaveOut, h, sizeof(WAVEHDR)); 

		if(wResult!=MMSYSERR_NOERROR)
		{ 
			printf("Failed to write block to device\n");
			SoundDev_DeInit();
			return; 
		} 
	}
}