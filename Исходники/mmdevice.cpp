	void flip()
	{
		MMTIME	time;
		int		err;

		if (playing==0) return;
		if (timeout)
		{
			if (--timeout) return;
			buffer.play(device);
		}
		memset(&time,0,sizeof(MMTIME));
   		time.wType=TIME_BYTES;
		err=waveOutGetPosition(device,&time,sizeof(MMTIME));		

		if (time.wType!=TIME_BYTES) err=-666;else if (time.u.cb>0x10000000) err=-6667;
		if (err) {
//			printf("waveOutGetPosition failed err=%d\n",err);fflush(stdout);
			waveOutReset(device);
			mixpos=0;
			memset(buffer.data,0,buffersize*samplesize*32);
			buffer.play(device);
			return;
		}
		
		int wavepos=time.u.cb/samplesize;
		int writeahead=buffersize*lagbuffers;
		if (wavepos && wavepos+buffersize*2>mixpos)
		{
			timeout=250;
			memset(buffer.data,0,buffersize*samplesize*32);
			waveOutReset(device);
			if (lagbuffers<10) lagbuffers+=2;
			mixpos=buffersize*lagbuffers*2;
//			printf("collision");fflush(stdout);
			return;			
		}
		int seek=wavepos+writeahead;				
		while (mixpos<seek)
		{
			int f=(mixpos/buffersize)&31;
			if (mode==0) 
			{
				mix->mix8(buffer.data+f*buffersize);
			}
			else
			{
				mix->mix16((short *)buffer.data+f*buffersize);
			}
			mixpos+=buffersize;	
		}
	}