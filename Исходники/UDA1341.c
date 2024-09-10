void RecordChannelOnOff(void)
{
	static int ChannelOn = 0;
	int err;
	WAVEFORMATEX fmt;
	WAVEHDR hdr;
	HWAVEIN hwi = 1;
	
	fmt.nSamplesPerSec  = 22050;
	fmt.wBitsPerSample  = 16;
	fmt.wFormatTag		= WAVE_FORMAT_PCM;
	fmt.nChannels		= 2;
	fmt.nBlockAlign     = fmt.wBitsPerSample*fmt.nChannels/8;	
	fmt.nAvgBytesPerSec	= fmt.nSamplesPerSec*fmt.nBlockAlign;
	
	hdr.lpData = (LPSTR)0x30800000;//_NONCACHE_STARTADDRESS;
	hdr.dwBufferLength = BUF_SIZE;
	
	if(!ChannelOn)
	{
		err = waveInOpen(&hwi,
					0,
					&fmt,
					0,
					0,
					0);
		Uart_Printf("\nerr = %x\n", err);
		if(!err)
		{
			waveInAddBuffer(hwi, &hdr, 0);
			waveInStart(hwi);
			Uart_Printf("Record channel on\n");
			ChannelOn = 1;
		}
	}
	else
	{
		waveInClose(hwi);
		Uart_Printf("Record channel off\n");
		ChannelOn = 0;
	}
}