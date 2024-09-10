int CMemPlay::Write(char *buf,int len)
{

	// check device open
	if (bDeviceopen==FALSE) return(0);

// TRACE("Write(%d bytes)\n",len);

	// copy to transfer buffer
	if (len > (int)iWavebufsize) len = iWavebufsize;
	if (len > 0) {
		memcpy(pWavehdr[iBufindex]->lpData,buf,len);
		pWavehdr[iBufindex]->dwBufferLength = len;

		// write to device
		pWavehdr[iBufindex]->dwFlags = (DWORD)WHDR_PREPARED;
		if (waveOutWrite(hWaveout, pWavehdr[iBufindex],sizeof(WAVEHDR))) {
			Stop();
			return(0);
		}
		nPending++;
//		TRACE("nPending=%d\n",nPending);
		iBufindex = (iBufindex+1)%NBUFFERS;
	}
	else
		iMorebuffers = OFF;

	return(len);
}