int CheckDevice(int device,int hertz,int chan,int bits)
{
	MMRESULT res;
	HWAVEOUT audiodev;
	WAVEFORMATEX waveformat;

#ifdef MMPDEBUG
	printf("checking device %d with %d Hz, %d channels, %d bits... ",device,hertz,chan,bits);
#endif
	waveformat.wFormatTag=WAVE_FORMAT_PCM;
	waveformat.nChannels=chan;
	waveformat.wBitsPerSample=bits;
	waveformat.nSamplesPerSec=hertz;
	waveformat.nBlockAlign=(waveformat.nChannels*waveformat.wBitsPerSample)/8;
    waveformat.nAvgBytesPerSec=waveformat.nSamplesPerSec*waveformat.nBlockAlign;
	waveformat.cbSize=0;
	res=waveOutOpen(&audiodev,device,&waveformat,0,0,CALLBACK_NULL);
	waveOutReset(audiodev);
	waveOutClose(audiodev);
	if (res)
	{
#ifdef MMPDEBUG
		printf("didn't work.\n");
#endif
		UseDevice=(unsigned int)-1;
		return 1;
	}
#ifdef MMPDEBUG
	printf("worked!\n");
#endif
	return 0;
};