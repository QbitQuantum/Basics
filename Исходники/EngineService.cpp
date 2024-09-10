	void EngineService::AcceptVisitor( JobFiber& /*fiber*/, const ConfigurationBroadcastVisitor ) {
		enum : UINT32 {
			XAudio2CreateFlags = (ETIsDebugModeEnabled() ? XAUDIO2_DEBUG_ENGINE : 0)
		};

		ComPointer<IXAudio2>	audio;

		_log( MessageSeverity::Message, "Creating XAudio2 instance." ET_UTF8_NEWLINE_LITERAL );

		if( FAILED( XAudio2Create( audio.GetInterfacePointer(), XAudio2CreateFlags, XAUDIO2_DEFAULT_PROCESSOR ) ) ) {
			_log( MessageSeverity::Error, "Unable to create XAudio2 instance!" ET_UTF8_NEWLINE_LITERAL );

			return;
		}

		if( FAILED( audio->RegisterForCallbacks( this ) ) ) {
			_log( MessageSeverity::Error, "Unable to register XAudio2 device callbacks!" ET_UTF8_NEWLINE_LITERAL );
			return;
		}

		if( FAILED( audio->StartEngine() ) ) {
			_log( MessageSeverity::Error, "Unable to start XAudio2 engine!" ET_UTF8_NEWLINE_LITERAL );
			return;
		}

		_log( MessageSeverity::Message, "Created XAudio2 instance." ET_UTF8_NEWLINE_LITERAL );

	//	Commit changes to the service.
		_audio = eastl::move( audio );
	}