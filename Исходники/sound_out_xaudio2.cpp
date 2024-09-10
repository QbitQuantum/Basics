	virtual const char* open( void * hwnd, unsigned sample_rate, unsigned nch, unsigned max_samples_per_frame, unsigned num_frames )
	{
		this->hwnd = hwnd;
		this->sample_rate = sample_rate;
		this->nch = nch;
		this->max_samples_per_frame = max_samples_per_frame;
		this->num_frames = num_frames;

#ifdef HAVE_KS_HEADERS
		WAVEFORMATEXTENSIBLE wfx;
		wfx.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
		wfx.Format.nChannels = nch; //1;
		wfx.Format.nSamplesPerSec = sample_rate;
		wfx.Format.nBlockAlign = 2 * nch; //2;
		wfx.Format.nAvgBytesPerSec = wfx.Format.nSamplesPerSec * wfx.Format.nBlockAlign;
		wfx.Format.wBitsPerSample = 16;
		wfx.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE)-sizeof(WAVEFORMATEX);
		wfx.Samples.wValidBitsPerSample = 16;
		wfx.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
		wfx.dwChannelMask = nch == 2 ? KSAUDIO_SPEAKER_STEREO : KSAUDIO_SPEAKER_MONO;
#else
		WAVEFORMATEX wfx;
		wfx.wFormatTag = WAVE_FORMAT_PCM;
		wfx.nChannels = nch; //1;
		wfx.nSamplesPerSec = sample_rate;
		wfx.nBlockAlign = 2 * nch; //2;
		wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
		wfx.wBitsPerSample = 16;
		wfx.cbSize = 0;
#endif
        HRESULT hr = XAudio2Create( &xaud, 0 );
		if (FAILED(hr)) return "Creating XAudio2 interface";
		hr = xaud->CreateMasteringVoice(
			&mVoice,
			nch,
			sample_rate,
			0,
			NULL,
			NULL );
		if (FAILED(hr)) return "Creating XAudio2 mastering voice";
		hr = xaud->CreateSourceVoice( &sVoice, &wfx, 0, 4.0f, &notify );
		if (FAILED(hr)) return "Creating XAudio2 source voice";
		hr = sVoice->Start( 0 );
		if (FAILED(hr)) return "Starting XAudio2 voice";
		hr = sVoice->SetFrequencyRatio((float)1.0f);
		if (FAILED(hr)) return "Setting XAudio2 voice frequency ratio";
		buffered_count = 0;
		buffer_read_cursor = 0;
		buffer_write_cursor = 0;
		samples_played = 0;
		sample_buffer = new int16_t[ max_samples_per_frame * num_frames ];
		samples_in_buffer = new UINT64[ num_frames ];
		memset( samples_in_buffer, 0, sizeof( UINT64 ) * num_frames );
		return NULL;
	}