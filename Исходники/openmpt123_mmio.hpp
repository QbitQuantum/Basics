	mmio_stream_raii( const std::string & filename, const commandlineflags & flags_ ) : flags(flags_), mmio(NULL) {

		ZeroMemory( &waveformatex, sizeof( WAVEFORMATEX ) );
		waveformatex.cbSize = 0;
		waveformatex.wFormatTag = flags.use_float ? WAVE_FORMAT_IEEE_FLOAT : WAVE_FORMAT_PCM;
		waveformatex.nChannels = flags.channels;
		waveformatex.nSamplesPerSec = flags.samplerate;
		waveformatex.wBitsPerSample = flags.use_float ? 32 : 16;
		waveformatex.nBlockAlign = flags.channels * ( waveformatex.wBitsPerSample / 8 );
		waveformatex.nAvgBytesPerSec = waveformatex.nSamplesPerSec * waveformatex.nBlockAlign;

		#if defined(WIN32) && defined(UNICODE)
			wchar_t * tmp = wcsdup( utf8_to_wstring( filename ).c_str() );
			mmio = mmioOpen( tmp, NULL, MMIO_ALLOCBUF | MMIO_READWRITE | MMIO_CREATE );
			free( tmp );
			tmp = 0;
		#else
			char * tmp = strdup( filename.c_str() );
			mmio = mmioOpen( tmp, NULL, MMIO_ALLOCBUF | MMIO_READWRITE | MMIO_CREATE );
			free( tmp );
			tmp = 0;
		#endif
		
		ZeroMemory( &WAVE_chunk, sizeof( MMCKINFO ) );
		WAVE_chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		CHECKED(mmioCreateChunk( mmio, &WAVE_chunk, MMIO_CREATERIFF ));

			ZeroMemory( &fmt__chunk, sizeof( MMCKINFO ) );
			fmt__chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
			fmt__chunk.cksize = sizeof( WAVEFORMATEX );
			CHECKED(mmioCreateChunk( mmio, &fmt__chunk, 0 ));

				mmioWrite( mmio, (const char*)&waveformatex, sizeof( WAVEFORMATEX ) );

			CHECKED(mmioAscend( mmio, &fmt__chunk, 0 ));

			ZeroMemory( &data_chunk, sizeof( MMCKINFO ) );
			data_chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
			data_chunk.cksize = 0;
			CHECKED(mmioCreateChunk( mmio, &data_chunk, 0 ));

				ZeroMemory( &data_info, sizeof( MMIOINFO ) );
				CHECKED(mmioGetInfo( mmio, &data_info, 0 ));

	}