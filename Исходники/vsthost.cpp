int CALLBACK _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	int argc = 0;
	LPWSTR * argv = CommandLineToArgvW( GetCommandLineW(), &argc );

	if ( argv == NULL || argc != 3 ) return 1;

	wchar_t * end_char = 0;
	unsigned in_sum = wcstoul( argv[ 2 ], &end_char, 16 );
	if ( end_char == argv[ 2 ] || *end_char ) return 2;

	unsigned test_sum = 0;
	end_char = argv[ 1 ];
	while ( *end_char )
	{
		test_sum += (TCHAR)( *end_char++ * 820109 );
	}

#ifdef NDEBUG
	if ( test_sum != in_sum ) return 3;
#endif

	unsigned code = 0;

	HMODULE hDll = NULL;
	main_func pMain = NULL;
	AEffect * pEffect[3] = {0, 0, 0};

	audioMasterData effectData[3] = { { 0 }, { 1 }, { 2 } };

	std::vector<uint8_t> blState;

	uint32_t max_num_outputs = 2;
	uint32_t sample_rate = 44100;

	std::vector<uint8_t> chunk;
	std::vector<float> sample_buffer;

	null_file = CreateFile( _T("NUL"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL );

	pipe_in = GetStdHandle( STD_INPUT_HANDLE );
	pipe_out = GetStdHandle( STD_OUTPUT_HANDLE );

	SetStdHandle( STD_INPUT_HANDLE, null_file );
	SetStdHandle( STD_OUTPUT_HANDLE, null_file );

	{
		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_WIN95_CLASSES | ICC_COOL_CLASSES | ICC_STANDARD_CLASSES;
		if ( !InitCommonControlsEx( &icc ) ) return 4;
	}

	if ( FAILED( CoInitialize( NULL ) ) ) return 5;

#ifndef _DEBUG
	SetUnhandledExceptionFilter( myExceptFilterProc );
#endif

	size_t dll_name_len = wcslen( argv[ 1 ] );
	dll_dir = ( char * ) malloc( dll_name_len + 1 );
	wcstombs( dll_dir, argv[ 1 ], dll_name_len );
	dll_dir[ dll_name_len ] = '\0';
	char * slash = strrchr( dll_dir, '\\' );
	*slash = '\0';

	hDll = LoadLibraryW( argv[ 1 ] );
	if ( !hDll )
	{
		code = 6;
		goto exit;
	}

	pMain = (main_func) GetProcAddress( hDll, "main" );
	if ( !pMain )
	{
		code = 7;
		goto exit;
	}

#if 0
	MessageBox( GetDesktopWindow(), argv[ 1 ], _T("HUUUURRRRRR"), 0 );
#endif

	pEffect[ 0 ] = pMain( &audioMaster );
	if ( !pEffect[ 0 ] || pEffect[ 0 ]->magic != kEffectMagic )
	{
		code = 8;
		goto exit;
	}

	pEffect[ 0 ]->user = &effectData[ 0 ];

	pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effOpen, 0, 0, 0, 0 );

	if ( pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effGetPlugCategory, 0, 0, 0, 0 ) != kPlugCategSynth ||
		pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effCanDo, 0, 0, "sendVstMidiEvent", 0 ) == 0 )
	{
		code = 9;
		goto exit;
	}

	max_num_outputs = min( pEffect[ 0 ]->numOutputs, 2 );

	{
		char name_string[256] = { 0 };
		char vendor_string[256] = { 0 };
		char product_string[256] = { 0 };
		uint32_t name_string_length;
		uint32_t vendor_string_length;
		uint32_t product_string_length;
		uint32_t vendor_version;
		uint32_t unique_id;

		pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effGetEffectName, 0, 0, &name_string, 0 );
		pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effGetVendorString, 0, 0, &vendor_string, 0 );
		pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effGetProductString, 0, 0, &product_string, 0 );
		name_string_length = strlen( name_string );
		vendor_string_length = strlen( vendor_string );
		product_string_length = strlen( product_string );
		vendor_version = pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effGetVendorVersion, 0, 0, 0, 0 );
		unique_id = pEffect[ 0 ]->uniqueID;

		put_code( 0 );
		put_code( name_string_length );
		put_code( vendor_string_length );
		put_code( product_string_length );
		put_code( vendor_version );
		put_code( unique_id );
		put_code( max_num_outputs );
		if ( name_string_length ) put_bytes( name_string, name_string_length );
		if ( vendor_string_length ) put_bytes( vendor_string, vendor_string_length );
		if ( product_string_length ) put_bytes( product_string, product_string_length );
	}

	float     ** float_list_in;
	float     ** float_list_out;
	float      * float_null;
	float      * float_out;

	for (;;)
	{
		uint32_t command = get_code();
		if ( !command ) break;

		switch ( command )
		{
		case 1: // Get Chunk
			getChunk( pEffect[ 0 ], chunk );

			put_code( 0 );
			put_code( chunk.size() );
			put_bytes( chunk.data(), chunk.size() );
			break;

		case 2: // Set Chunk
			{
				uint32_t size = get_code();
				chunk.resize( size );
				if ( size ) get_bytes( chunk.data(), size );

				setChunk( pEffect[ 0 ], chunk );
				setChunk( pEffect[ 1 ], chunk );
				setChunk( pEffect[ 2 ], chunk );

				put_code( 0 );
			}
			break;

		case 3: // Has Editor
			{
				uint32_t has_editor = ( pEffect[ 0 ]->flags & effFlagsHasEditor ) ? 1 : 0;

				put_code( 0 );
				put_code( has_editor );
			}
			break;

		case 4: // Display Editor Modal
			{
				if ( pEffect[ 0 ]->flags & effFlagsHasEditor )
				{
					MyDLGTEMPLATE t;
					t.style = WS_POPUPWINDOW | WS_DLGFRAME | DS_MODALFRAME | DS_CENTER;
					DialogBoxIndirectParam ( 0, &t, GetDesktopWindow(), (DLGPROC)EditorProc, (LPARAM)( pEffect[ 0 ] ) );
					getChunk( pEffect[ 0 ], chunk );
					setChunk( pEffect[ 1 ], chunk );
					setChunk( pEffect[ 2 ], chunk );
				}

				put_code( 0 );
			}
			break;

		case 5: // Set Sample Rate
			{
				uint32_t size = get_code();
				if ( size != sizeof(sample_rate) )
				{
					code = 10;
					goto exit;
				}

				sample_rate = get_code();

				put_code( 0 );
			}
			break;

		case 6: // Reset
			{
				if ( pEffect[ 2 ] )
				{
					if ( blState.size() ) pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effStopProcess, 0, 0, 0, 0 );
					pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effClose, 0, 0, 0, 0 );
					pEffect[ 2 ] = NULL;
				}
				if ( pEffect[ 1 ] )
				{
					if ( blState.size() ) pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effStopProcess, 0, 0, 0, 0 );
					pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effClose, 0, 0, 0, 0 );
					pEffect[ 1 ] = NULL;
				}
				if ( blState.size() ) pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effStopProcess, 0, 0, 0, 0 );
				pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effClose, 0, 0, 0, 0 );

				blState.resize( 0 );

				freeChain();

				pEffect[ 0 ] = pMain( &audioMaster );
				if ( !pEffect[ 0 ] )
				{
					code = 8;
					goto exit;
				}
				pEffect[ 0 ]->user = &effectData[ 0 ];
				pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effOpen, 0, 0, 0, 0 );
				setChunk( pEffect[ 0 ], chunk );

				put_code( 0 );
			}
			break;

		case 7: // Send MIDI Event
			{
				myVstEvent * ev = ( myVstEvent * ) calloc( sizeof( myVstEvent ), 1 );
				if ( evTail ) evTail->next = ev;
				evTail = ev;
				if ( !evChain ) evChain = ev;

				uint32_t b = get_code();

				ev->port = (b & 0x7F000000) >> 24;
				if (ev->port > 2) ev->port = 2;
				ev->ev.midiEvent.type = kVstMidiType;
				ev->ev.midiEvent.byteSize = sizeof(ev->ev.midiEvent);
				memcpy(&ev->ev.midiEvent.midiData, &b, 3);

				put_code( 0 );
			}
			break;

		case 8: // Send System Exclusive Event
			{
				myVstEvent * ev = ( myVstEvent * ) calloc( sizeof( myVstEvent ), 1 );
				if ( evTail ) evTail->next = ev;
				evTail = ev;
				if ( !evChain ) evChain = ev;

				uint32_t size = get_code();
				uint32_t port = size >> 24;
				size &= 0xFFFFFF;

				ev->port = port;
				if (ev->port > 2) ev->port = 2;
				ev->ev.sysexEvent.type = kVstSysExType;
				ev->ev.sysexEvent.byteSize = sizeof(ev->ev.sysexEvent);
				ev->ev.sysexEvent.dumpBytes = size;
				ev->ev.sysexEvent.sysexDump = (char*) malloc( size );

				get_bytes( ev->ev.sysexEvent.sysexDump, size );

				put_code( 0 );
			}
			break;

		case 9: // Render Samples
			{
				if ( !pEffect[ 1 ] )
				{
					pEffect[ 1 ] = pMain( &audioMaster );
					if ( !pEffect[ 1 ] )
					{
						code = 11;
						goto exit;
					}
					pEffect[ 1 ]->user = &effectData[ 1 ];
					pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effOpen, 0, 0, 0, 0 );
					setChunk( pEffect[ 1 ], chunk );
				}
				if ( !pEffect[ 2 ] )
				{
					pEffect[ 2 ] = pMain( &audioMaster );
					if ( !pEffect[ 2 ] )
					{
						code = 11;
						goto exit;
					}
					pEffect[ 2 ]->user = &effectData[ 2 ];
					pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effOpen, 0, 0, 0, 0 );
					setChunk( pEffect[ 2 ], chunk );
				}

				if ( !blState.size() )
				{
					pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effSetSampleRate, 0, 0, 0, float(sample_rate) );
					pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effSetBlockSize, 0, BUFFER_SIZE, 0, 0 );
					pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effMainsChanged, 0, 1, 0, 0 );
					pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effStartProcess, 0, 0, 0, 0 );

					pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effSetSampleRate, 0, 0, 0, float(sample_rate) );
					pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effSetBlockSize, 0, BUFFER_SIZE, 0, 0 );
					pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effMainsChanged, 0, 1, 0, 0 );
					pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effStartProcess, 0, 0, 0, 0 );

					pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effSetSampleRate, 0, 0, 0, float(sample_rate) );
					pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effSetBlockSize, 0, BUFFER_SIZE, 0, 0 );
					pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effMainsChanged, 0, 1, 0, 0 );
					pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effStartProcess, 0, 0, 0, 0 );

					size_t buffer_size = sizeof(float*) * ( pEffect[ 0 ]->numInputs + pEffect[ 0 ]->numOutputs * 3 ); // float lists
					buffer_size += sizeof(float) * BUFFER_SIZE;                                // null input
					buffer_size += sizeof(float) * BUFFER_SIZE * pEffect[ 0 ]->numOutputs * 3;          // outputs

					blState.resize( buffer_size );

					float_list_in  = (float**) blState.data();
					float_list_out = float_list_in + pEffect[ 0 ]->numInputs;
					float_null     = (float*) ( float_list_out + pEffect[ 0 ]->numOutputs * 3 );
					float_out      = float_null + BUFFER_SIZE;

					for ( unsigned i = 0; i < pEffect[ 0 ]->numInputs; ++i )      float_list_in [ i ] = float_null;
					for ( unsigned i = 0; i < pEffect[ 0 ]->numOutputs * 3; ++i ) float_list_out[ i ] = float_out + BUFFER_SIZE * i;

					memset( float_null, 0, sizeof(float) * BUFFER_SIZE );

					sample_buffer.resize( BUFFER_SIZE * max_num_outputs );
				}

				if ( need_idle )
				{
					pEffect[ 0 ]->dispatcher( pEffect[ 0 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );
					pEffect[ 1 ]->dispatcher( pEffect[ 1 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );
					pEffect[ 2 ]->dispatcher( pEffect[ 2 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );

					if ( !idle_started )
					{
						unsigned idle_run = BUFFER_SIZE * 128;

						while ( idle_run )
						{
							unsigned count_to_do = min( idle_run, BUFFER_SIZE );
							unsigned num_outputs = pEffect[ 0 ]->numOutputs;

							pEffect[ 0 ]->processReplacing( pEffect[ 0 ], float_list_in, float_list_out, count_to_do );
							pEffect[ 1 ]->processReplacing( pEffect[ 1 ], float_list_in, float_list_out + num_outputs, count_to_do );
							pEffect[ 2 ]->processReplacing( pEffect[ 2 ], float_list_in, float_list_out + num_outputs * 2, count_to_do );

							pEffect[ 0 ]->dispatcher( pEffect[ 0 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );
							pEffect[ 1 ]->dispatcher( pEffect[ 1 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );
							pEffect[ 2 ]->dispatcher( pEffect[ 2 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );

							idle_run -= count_to_do;
						}
					}
				}

				VstEvents * events[ 3 ] = {0};

				if ( evChain )
				{
					unsigned event_count[ 3 ] = {0};
					myVstEvent * ev = evChain;
					while ( ev )
					{
						event_count[ ev->port ]++;
						ev = ev->next;
					}

					if ( event_count[ 0 ] )
					{
						events[ 0 ] = ( VstEvents * ) malloc( sizeof(long) + sizeof(long) + sizeof(VstEvent*) * event_count[ 0 ] );

						events[ 0 ]->numEvents = event_count[ 0 ];
						events[ 0 ]->reserved = 0;

						ev = evChain;

						for ( unsigned i = 0; ev; )
						{
							if ( !ev->port ) events[ 0 ]->events[ i++ ] = (VstEvent*) &ev->ev;
							ev = ev->next;
						}

						pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effProcessEvents, 0, 0, events[ 0 ], 0 );
					}

					if ( event_count[ 1 ] )
					{
						events[ 1 ] = ( VstEvents * ) malloc( sizeof(long) + sizeof(long) + sizeof(VstEvent*) * event_count[ 1 ] );

						events[ 1 ]->numEvents = event_count[ 1 ];
						events[ 1 ]->reserved = 0;

						ev = evChain;

						for ( unsigned i = 0; ev; )
						{
							if ( ev->port == 1 ) events[ 1 ]->events[ i++ ] = (VstEvent*) &ev->ev;
							ev = ev->next;
						}

						pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effProcessEvents, 0, 0, events[ 1 ], 0 );
					}

					if ( event_count[ 2 ] )
					{
						events[ 2 ] = ( VstEvents * ) malloc( sizeof(long) + sizeof(long) + sizeof(VstEvent*) * event_count[ 2 ] );

						events[ 2 ]->numEvents = event_count[ 2 ];
						events[ 2 ]->reserved = 0;

						ev = evChain;

						for ( unsigned i = 0; ev; )
						{
							if ( ev->port == 2 ) events[ 2 ]->events[ i++ ] = (VstEvent*) &ev->ev;
							ev = ev->next;
						}

						pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effProcessEvents, 0, 0, events[ 2 ], 0 );
					}
				}

				if ( need_idle )
				{
					pEffect[ 0 ]->dispatcher( pEffect[ 0 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );
					pEffect[ 1 ]->dispatcher( pEffect[ 1 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );
					pEffect[ 2 ]->dispatcher( pEffect[ 2 ], DECLARE_VST_DEPRECATED (effIdle), 0, 0, 0, 0 );

					if ( !idle_started )
					{
						if ( events[ 0 ] ) pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effProcessEvents, 0, 0, events[ 0 ], 0 );
						if ( events[ 1 ] ) pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effProcessEvents, 0, 0, events[ 1 ], 0 );
						if ( events[ 2 ] ) pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effProcessEvents, 0, 0, events[ 2 ], 0 );

						idle_started = true;
					}
				}

				uint32_t count = get_code();

				put_code( 0 );

				while( count )
				{
					unsigned count_to_do = min( count, BUFFER_SIZE );
					unsigned num_outputs = pEffect[ 0 ]->numOutputs;

					pEffect[ 0 ]->processReplacing( pEffect[ 0 ], float_list_in, float_list_out, count_to_do );
					pEffect[ 1 ]->processReplacing( pEffect[ 1 ], float_list_in, float_list_out + num_outputs, count_to_do );
					pEffect[ 2 ]->processReplacing( pEffect[ 2 ], float_list_in, float_list_out + num_outputs * 2, count_to_do );

					float * out = sample_buffer.data();

					if ( max_num_outputs == 2 )
					{
						for ( unsigned i = 0; i < count_to_do; ++i )
						{
							float sample = ( float_out[ i ] + float_out[ i + BUFFER_SIZE * num_outputs ] + float_out[ i + BUFFER_SIZE * num_outputs * 2 ] );
							out[ 0 ] = sample;
							sample = ( float_out[ i + BUFFER_SIZE ] + float_out[ i + BUFFER_SIZE + BUFFER_SIZE * num_outputs ] + float_out[ i + BUFFER_SIZE + BUFFER_SIZE * num_outputs * 2 ] );
							out[ 1 ] = sample;
							out += 2;
						}
					}
					else
					{
						for ( unsigned i = 0; i < count_to_do; ++i )
						{
							float sample = ( float_out[ i ] + float_out[ i + BUFFER_SIZE * num_outputs ] + float_out[ i + BUFFER_SIZE * num_outputs * 2 ] );
							out[ 0 ] = sample;
							out++;
						}
					}

					put_bytes( sample_buffer.data(), sizeof(float) * count_to_do * max_num_outputs );

					count -= count_to_do;
				}

				if ( events[ 0 ] ) free( events[ 0 ] );
				if ( events[ 1 ] ) free( events[ 1 ] );
				if ( events[ 2 ] ) free( events[ 2 ] );

				freeChain();
			}
			break;

		default:
			code = 12;
			goto exit;
			break;
		}
	}

exit:
	if ( pEffect[ 2 ] )
	{
		if ( blState.size() ) pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effStopProcess, 0, 0, 0, 0 );
		pEffect[ 2 ]->dispatcher( pEffect[ 2 ], effClose, 0, 0, 0, 0 );
	}
	if ( pEffect[ 1 ] )
	{
		if ( blState.size() ) pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effStopProcess, 0, 0, 0, 0 );
		pEffect[ 1 ]->dispatcher( pEffect[ 1 ], effClose, 0, 0, 0, 0 );
	}
	if ( pEffect[ 0 ] )
	{
		if ( blState.size() ) pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effStopProcess, 0, 0, 0, 0 );
		pEffect[ 0 ]->dispatcher( pEffect[ 0 ], effClose, 0, 0, 0, 0 );
	}
	freeChain();
	if ( hDll ) FreeLibrary( hDll );
	CoUninitialize();
	if ( argv ) LocalFree( argv );

	put_code( code );

	if ( null_file )
	{
		CloseHandle( null_file );

		SetStdHandle( STD_INPUT_HANDLE, pipe_in );
		SetStdHandle( STD_OUTPUT_HANDLE, pipe_out );
	}

	return code;
}