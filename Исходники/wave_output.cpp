int WaveOutput::Open(int32_t rate, uint32_t chn, int32_t bits, int32_t bufferlenms, int32_t prebufferms)
{
	//int8_t	str[256];
	int32_t	error,i;


	if (chn>2) return -1;						//No more than stereo

	if (open) Close();						//Verify device was closed

	//if (cfg.changed)	{
		blk.num=4;//cfg.numBlk;
		blk.min=2*1024;//cfg.minBlk*1024;
		blk.max=64*1024;//cfg.maxBlk*1024;
    SafeDeleteArray(&buffer.pOut);
    buffer.pOut= new uint8_t[(blk.num * blk.max)];
  //}

	//Build format structure -------------------
	wav.fmt.Format.wFormatTag				= WAVE_FORMAT_EXTENSIBLE;
	wav.fmt.Format.nChannels				= chn;
	wav.fmt.Format.nSamplesPerSec			= rate;
	wav.fmt.Format.wBitsPerSample			= (bits+7)&~7;		//Round bits per sample up to nearest byte
	wav.fmt.Format.nBlockAlign			= chn * wav.fmt.Format.wBitsPerSample>>3;
	wav.fmt.Format.nAvgBytesPerSec		= wav.fmt.Format.nBlockAlign * wav.fmt.Format.nSamplesPerSec;
	wav.fmt.Format.cbSize					= 22;
	wav.fmt.Samples.wValidBitsPerSample	= bits;
	wav.fmt.dwChannelMask					= chn==2 ? 3 : 4;	//Select left & right (stereo) or center (mono)
	wav.fmt.SubFormat						= KSDATAFORMAT_SUBTYPE_PCM;

  int cfbufferLen = 2000;
	//Check size of ring buffer ----------------
	buffer.size=(wav.fmt.Format.nSamplesPerSec *
				wav.fmt.Format.nBlockAlign * 
				cfbufferLen) / 1000;

	if (buffer.asize < buffer.size)				//If allocated size is less than needed size
	{
		//buffer.pIn=realloc(buffer.pIn,buffer.size);
    SafeDeleteArray(&buffer.pIn);
    buffer.pIn = new uint8_t[buffer.size];
		buffer.asize=buffer.size;
	}

	//Open audio device ------------------------
  int cfg_direct = 0;//WAVE_FORMAT_DIRECT
	error=waveOutOpen(&wav.handle,device,(tWAVEFORMATEX*)&wav.fmt,DWORD_PTR(WaveOutDone),DWORD_PTR(this),CALLBACK_FUNCTION|WAVE_ALLOWSYNC|cfg_direct);
	switch (error)
	{
	case(MMSYSERR_NOERROR):
		wav.idle=(uint32_t)~0>>(32-blk.num);		//All blocks are free

		//Initialize wave blocks ---------------
		for (i=0;i<blk.num;i++)
		{
			memset(&wav.hdr[i],0,sizeof(WAVEHDR));

			wav.hdr[i].lpData=(LPSTR)buffer.pOut+(blk.max*i);
			wav.hdr[i].dwBufferLength=blk.max;
			waveOutPrepareHeader(wav.handle,&wav.hdr[i],sizeof(WAVEHDR));

			wav.hdr[i].dwBufferLength=0;
			wav.hdr[i].dwUser=(DWORD_PTR)(1<<i);			//Bit corresponding to block
			wav.hdr[i].dwFlags|=WHDR_DONE;
		}

		memset(&wav.time,0,sizeof(MMTIME));
		wav.time.wType=TIME_SAMPLES;
		wav.samples=0;
		wav.smpCnt=0;

		buffer.bytes=0;							//No bytes have been written

		buffer.length=0;							//Nothing is in input buffer
		buffer.queued_length=0;
		buffer.write=0;
		buffer.read=0;

		blk.cnt=0;
		blk.size=0;

		paused=0;								//Output isn't paused
		open=1;								//Device is open

		return ((buffer.size / wav.fmt.Format.nBlockAlign) * 1000) / wav.fmt.Format.nSamplesPerSec;

	case(MMSYSERR_ALLOCATED):
		//sprintf(str,"%s is already in use",wav.cap.szPname);
		//MessageBox(outMod.hMainWindow,str,"WaveOut WDM",MB_ICONERROR|MB_OK);
		break;

	case(MMSYSERR_BADDEVICEID):
		//sprintf(str,"Invalid output device ID [%i].  Check your configuration.",cfg.device);
		//MessageBox(outMod.hMainWindow,str,"WaveOut WDM",MB_ICONERROR|MB_OK);
		break;

	case(MMSYSERR_NODRIVER):
		//sprintf(str,"No driver is loaded for %s",wav.cap.szPname);
		//MessageBox(outMod.hMainWindow,str,"WaveOut WDM",MB_ICONERROR|MB_OK);
		break;

	case(MMSYSERR_NOMEM):
		//MessageBox(outMod.hMainWindow,"Unable to allocate memory for output device","WaveOut WDM",MB_ICONERROR|MB_OK);
		break;

	case(WAVERR_BADFORMAT):
		//MessageBox(outMod.hMainWindow,"The extensible format is not supported by your driver.  Get the WDM drivers for your soundcard.","WaveOut WDM",MB_ICONERROR|MB_OK);
		break;

	default:
		//sprintf(str,"Unknown error [%i] trying to open output device %s",error,wav.cap.szPname);
		//MessageBox(outMod.hMainWindow,str,"WaveOut WDM",MB_ICONERROR|MB_OK);
    break;
	}

	return S_FALSE;
}