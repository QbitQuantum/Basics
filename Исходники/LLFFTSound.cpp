//-----------------------------------------------------------------------------
void LLFFTSound::update(float addedTime)
{
	if(!m_bInitialized || !m_bPlaying)
		return;

#ifdef _WINDOWS
	
	// update current waveform level
#if BASSVERSION == 0x204
	DWORD pos = BASS_ChannelGetPosition(m_dChannel, BASS_POS_BYTE);
	if (pos == BASS_ChannelGetLength(m_dChannel, BASS_POS_BYTE))
#else
	DWORD pos = BASS_ChannelGetPosition(m_dChannel);
	if (pos == BASS_ChannelGetLength(m_dChannel))
#endif
	{
		m_fCurrLevelLeft = 0.0f;
		m_fCurrLevelRight = 0.0f;
		m_bPlaying = false;
		BASS_ChannelStop(m_dChannel);
		// reset bands values
		for (int i=0; i< BANDS; i++)
			m_fBands[i] = 0.0f;

		// reset events queue
		resetEvent();
	}
	else
	{
		// update lever for each channel
		DWORD level = BASS_ChannelGetLevel(m_dChannel);
		m_fCurrLevelLeft = ((double)LOWORD(level) / 32768);		// range 0 to 1: left channel is low word
		m_fCurrLevelRight = ((double)HIWORD(level) / 32768);	// range 0 to 1: right channel is high word

		// update band spectrum
		float fft[1024];
		BASS_ChannelGetData(m_dChannel,fft,BASS_DATA_FFT2048); // get the FFT data

		int b0=0;
		int x,y;
#define FFTCAP 256.0f

		for (x=0; x<BANDS; x++) {
			float sum=0;
			int sc,b1 = pow(2,x*10.0/(BANDS-1));
			if (b1>1023) b1=1023;
			if (b1<=b0) b1=b0+1; // make sure it uses at least 1 FFT bin
			sc = 10 + b1 - b0;
			
			for (;b0<b1;b0++) sum+=fft[1+b0];
			
			y=(sqrt(sum/log10((double)sc))*1.7*FFTCAP)-4; // scale it
			
			if (y>FFTCAP) y=FFTCAP; // cap it
			
			// store band value
			m_fBands[x] = y;	
			m_fBands[x] /= FFTCAP;	// normalized band value (0.0 - 1.0)
		}

		// check event associated with this sound file: use pos variable to detect timing...
		float elapsedTime = BASS_ChannelBytes2Seconds(m_dChannel,pos); 

		if (m_iNumEvents && !m_bEventDone)
		{
			if (elapsedTime > 0.0f)
			{
				// there is possibility that multiple events have the same timestamp...
				// should do some kind of iteration.
				bool running = true;
				while(running)
				{
					if (m_fNextEventTime < elapsedTime)
					{
						// execute callback function
						i_CharacterEventCallback.execute(m_vEventVec[m_iNextEvent]);

						// move to next event
						m_iNextEvent++;
						if (m_iNextEvent == m_iNumEvents)
						{
							// reached the last event
							m_iNextEvent = 0;
							m_bEventDone = true;
							running = false;
						}
						m_fNextEventTime = m_vEventVec[m_iNextEvent]->eTime;

					}
					else
						running = false;
				}
			}
		}


	}
#endif
}