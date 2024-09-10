	s32 Init()
	{
		CoInitializeEx( NULL, COINIT_MULTITHREADED );

		//
		// Initialize DSound
		//
		GUID cGuid;

		try
		{
			if( m_Device.empty() )
				throw std::runtime_error( "screw it" );

			// Convert from unicode to ANSI:
			char guid[256];
			sprintf_s( guid, "%S", m_Device.c_str() );

			if( (FAILED(GUIDFromString( guid, &cGuid ))) ||
				FAILED( DirectSoundCreate8(&cGuid,&dsound,NULL) ) )
					throw std::runtime_error( "try again?" );
		}
		catch( std::runtime_error& )
		{
			// if the GUID failed, just open up the default dsound driver:
			if( FAILED(DirectSoundCreate8(NULL,&dsound,NULL) ) )
				throw std::runtime_error( "DirectSound failed to initialize!" );
		}

		if( FAILED(dsound->SetCooperativeLevel(GetDesktopWindow(),DSSCL_PRIORITY)) )
			throw std::runtime_error( "DirectSound Error: Cooperative level could not be set." );

		// Determine the user's speaker configuration, and select an expansion option as needed.
		// FAIL : Directsound doesn't appear to support audio expansion >_<

		DWORD speakerConfig = 2;
		//dsound->GetSpeakerConfig( &speakerConfig );

		IDirectSoundBuffer* buffer_;
 		DSBUFFERDESC desc;

		// Set up WAV format structure.

		memset(&wfx, 0, sizeof(WAVEFORMATEX));
		wfx.wFormatTag		= WAVE_FORMAT_PCM;
		wfx.nSamplesPerSec	= SampleRate;
		wfx.nChannels		= (WORD)speakerConfig;
		wfx.wBitsPerSample	= 16;
		wfx.nBlockAlign		= 2*(WORD)speakerConfig;
		wfx.nAvgBytesPerSec	= SampleRate * wfx.nBlockAlign;
		wfx.cbSize			= 0;

		uint BufferSizeBytes = BufferSize * wfx.nBlockAlign;

		// Set up DSBUFFERDESC structure.

		memset(&desc, 0, sizeof(DSBUFFERDESC));
		desc.dwSize = sizeof(DSBUFFERDESC);
		desc.dwFlags =  DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY;
		desc.dwBufferBytes = BufferSizeBytes * m_NumBuffers;
		desc.lpwfxFormat = &wfx;

		// Try a hardware buffer first, and then fall back on a software buffer if
		// that one fails.

		desc.dwFlags |= m_UseHardware ? DSBCAPS_LOCHARDWARE : DSBCAPS_LOCSOFTWARE;
		desc.dwFlags |= m_DisableGlobalFocus ? DSBCAPS_STICKYFOCUS : DSBCAPS_GLOBALFOCUS;

		if( FAILED(dsound->CreateSoundBuffer(&desc, &buffer_, 0) ) )
		{
			if( m_UseHardware )
			{
				desc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCSOFTWARE;
				desc.dwFlags |= m_DisableGlobalFocus ? DSBCAPS_STICKYFOCUS : DSBCAPS_GLOBALFOCUS;

				if( FAILED(dsound->CreateSoundBuffer(&desc, &buffer_, 0) ) )
					throw std::runtime_error( "DirectSound Error: Buffer could not be created." );
			}

			throw std::runtime_error( "DirectSound Error: Buffer could not be created." );
		}
		if(	FAILED(buffer_->QueryInterface(IID_IDirectSoundBuffer8,(void**)&buffer)) || buffer == NULL )
			throw std::runtime_error( "DirectSound Error: Interface could not be queried." );

		buffer_->Release();
		verifyc( buffer->QueryInterface(IID_IDirectSoundNotify8,(void**)&buffer_notify) );

		DSBPOSITIONNOTIFY not[MAX_BUFFER_COUNT];

		for(uint i=0;i<m_NumBuffers;i++)
		{
			buffer_events[i] = CreateEvent(NULL,FALSE,FALSE,NULL);
			not[i].dwOffset = (wfx.nBlockAlign + BufferSizeBytes*(i+1)) % desc.dwBufferBytes;
			not[i].hEventNotify = buffer_events[i];
		}

		buffer_notify->SetNotificationPositions(m_NumBuffers,not);

		LPVOID p1=0,p2=0;
		DWORD s1=0,s2=0;

		verifyc(buffer->Lock(0,desc.dwBufferBytes,&p1,&s1,&p2,&s2,0));
		assert(p2==0);
		memset(p1,0,s1);
		verifyc(buffer->Unlock(p1,s1,p2,s2));

		//Play the buffer !
		verifyc(buffer->Play(0,0,DSBPLAY_LOOPING));

		// Start Thread
		myLastWrite = 0;
		dsound_running = true;
		thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)RThread<StereoOut16>,this,0,&tid);
		SetThreadPriority(thread,THREAD_PRIORITY_ABOVE_NORMAL);

		return 0;
	}