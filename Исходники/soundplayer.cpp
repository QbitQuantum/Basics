void CSoundPlayer::Close()
{
	if (NULL != soundObj.pWaveHdr && soundObj.initWaveHdr == 0x01)
	{
		MMRESULT	mmhr;
		for( unsigned int i=0; i<soundObj.waveHdrNum; i++ ) 
		{
			//if (soundObj.pWaveHdr[i].dwBufferLength < 1)		continue;

			soundObj.pWaveHdr[i].dwFlags = 0;
			mmhr = waveOutUnprepareHeader( soundObj.hWaveOut, &soundObj.pWaveHdr[i], sizeof(WAVEHDR) );
			soundObj.pWaveHdr[i].dwBufferLength = 0;
		}
	}
	soundObj.initWaveHdr = 0x00;

	if (NULL != soundObj.hWaveOut)
	{
		waveOutClose(soundObj.hWaveOut);
		soundObj.hWaveOut = NULL;
	}
	//if( soundObj.hNotify ) CloseHandle( soundObj.hNotify );
	//soundObj.hNotify = NULL;
}