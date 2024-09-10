/*
========================
idSoundHardware_XAudio2::Init
========================
*/
void idSoundHardware_XAudio2::Init() {

	cmdSystem->AddCommand( "listDevices", listDevices_f, 0, "Lists the connected sound devices", NULL );

	DWORD xAudioCreateFlags = 0;

// RB: not available on Windows 8 SDK
#if !defined(USE_WINRT) && defined(_DEBUG)
	xAudioCreateFlags |= XAUDIO2_DEBUG_ENGINE;
#endif
// RB end

	XAUDIO2_PROCESSOR xAudioProcessor = XAUDIO2_DEFAULT_PROCESSOR;

// RB: not available on Windows 8 SDK
	if ( FAILED( XAudio2Create( &pXAudio2, xAudioCreateFlags, xAudioProcessor ) ) ){
#if !defined(USE_WINRT) && defined(_DEBUG)
		if ( xAudioCreateFlags & XAUDIO2_DEBUG_ENGINE ) {
			// in case the debug engine isn't installed
			xAudioCreateFlags &= ~XAUDIO2_DEBUG_ENGINE;
			if ( FAILED( XAudio2Create( &pXAudio2, xAudioCreateFlags, xAudioProcessor ) ) ) {		
				idLib::FatalError( "Failed to create XAudio2 engine.  Try installing the latest DirectX." );
				return;
			}
		} else 
#endif
// RB end
		{
			idLib::FatalError( "Failed to create XAudio2 engine.  Try installing the latest DirectX." );
			return;
		}
	}
#ifdef _DEBUG
	XAUDIO2_DEBUG_CONFIGURATION debugConfiguration = { 0 };
	debugConfiguration.TraceMask = XAUDIO2_LOG_WARNINGS;
	debugConfiguration.BreakMask = XAUDIO2_LOG_ERRORS;
	pXAudio2->SetDebugConfiguration( &debugConfiguration );
#endif

	// Register the sound engine callback
	pXAudio2->RegisterForCallbacks( &soundEngineCallback );
	soundEngineCallback.hardware = this;
    DWORD outputSampleRate = 44100; // Max( (DWORD)XAUDIO2FX_REVERB_MIN_FRAMERATE, Min( (DWORD)XAUDIO2FX_REVERB_MAX_FRAMERATE, deviceDetails.OutputFormat.Format.nSamplesPerSec ) );

	idCmdArgs args;
	listDevices_f( args );

    // RB: not available on Windows 8 SDK
#if defined(USE_WINRT) //(_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
    AudioDevice defaultDevice;
    std::vector<AudioDevice> vAudioDevices = EnumerateAudioDevices(&defaultDevice);

    if (!vAudioDevices.empty()) {

        AudioDevice selectedDevice;

        int preferredDevice = s_device.GetInteger();
        bool validPreference = (preferredDevice >= 0 && preferredDevice < (int)vAudioDevices.size());
        // Do we select a device automatically?
        if (validPreference)
        {
            // Use the user's selected device
            selectedDevice = vAudioDevices[preferredDevice];
        }
        else if (!defaultDevice.id.empty())
        {
            // Fall back to the default device if there is one
            selectedDevice = defaultDevice;
        }
        else
        {
            // Fall back to first device
            selectedDevice = vAudioDevices[0];
        }
        
        if (SUCCEEDED(pXAudio2->CreateMasteringVoice(&pMasterVoice,
                                                     XAUDIO2_DEFAULT_CHANNELS,
                                                     outputSampleRate,
                                                     0,
                                                     selectedDevice.id.c_str(),
                                                     NULL,
                                                     AudioCategory_GameEffects)))
        {
            XAUDIO2_VOICE_DETAILS deviceDetails;
            pMasterVoice->GetVoiceDetails(&deviceDetails);

            pMasterVoice->SetVolume(DBtoLinear(s_volume_dB.GetFloat()));

            outputChannels = deviceDetails.InputChannels;
            DWORD win8_channelMask;
            pMasterVoice->GetChannelMask(&win8_channelMask);

            channelMask = (unsigned int)win8_channelMask;
            idLib::Printf( "Using device %S\n", selectedDevice.name );
        }
        else {
            idLib::Warning("Failed to create master voice");
            pXAudio2->Release();
            pXAudio2 = NULL;
            return;
        }
     }

#else	
    UINT32 deviceCount = 0;
	if( pXAudio2->GetDeviceCount( &deviceCount ) != S_OK || deviceCount == 0 )
	{
		idLib::Warning( "No audio devices found" );
		pXAudio2->Release();
		pXAudio2 = NULL;
		return;
	}
	
	int preferredDevice = s_device.GetInteger();
	if( preferredDevice < 0 || preferredDevice >= ( int )deviceCount )
	{
		int preferredChannels = 0;
		for( unsigned int i = 0; i < deviceCount; i++ )
		{
			XAUDIO2_DEVICE_DETAILS deviceDetails;
			if( pXAudio2->GetDeviceDetails( i, &deviceDetails ) != S_OK )
			{
				continue;
			}
	
			if( deviceDetails.Role & DefaultGameDevice )
			{
				// if we find a device the user marked as their preferred 'game' device, then always use that
				preferredDevice = i;
				preferredChannels = deviceDetails.OutputFormat.Format.nChannels;
				break;
			}
	
			if( deviceDetails.OutputFormat.Format.nChannels > preferredChannels )
			{
				preferredDevice = i;
				preferredChannels = deviceDetails.OutputFormat.Format.nChannels;
			}
		}
	}
	
	idLib::Printf( "Using device %d\n", preferredDevice );
	
	XAUDIO2_DEVICE_DETAILS deviceDetails;
	if( pXAudio2->GetDeviceDetails( preferredDevice, &deviceDetails ) != S_OK )
	{
		// One way this could happen is if a device is removed between the loop and this line of code
		// Highly unlikely but possible
		idLib::Warning( "Failed to get device details" );
		pXAudio2->Release();
		pXAudio2 = NULL;
		return;
	}
	

	if( FAILED( pXAudio2->CreateMasteringVoice( &pMasterVoice, XAUDIO2_DEFAULT_CHANNELS, outputSampleRate, 0, preferredDevice, NULL ) ) )
	{
		idLib::Warning( "Failed to create master voice" );
		pXAudio2->Release();
		pXAudio2 = NULL;
		return;
	}
	pMasterVoice->SetVolume( DBtoLinear( s_volume_dB.GetFloat() ) );
	
	outputChannels = deviceDetails.OutputFormat.Format.nChannels;
	channelMask = deviceDetails.OutputFormat.dwChannelMask;

#endif // #if (_WIN32_WINNT < 0x0602 /*_WIN32_WINNT_WIN8*/)

	idSoundVoice::InitSurround( outputChannels, channelMask );

	// ---------------------
	// Initialize the Doom classic sound system.
	// ---------------------
	I_InitSoundHardware( outputChannels, channelMask );

	// ---------------------
	// Create VU Meter Effect
	// ---------------------
	IUnknown * vuMeter = NULL;
	XAudio2CreateVolumeMeter( &vuMeter, 0 );

	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	descriptor.InitialState = true;
	descriptor.OutputChannels = outputChannels;
	descriptor.pEffect = vuMeter;

	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;

	pMasterVoice->SetEffectChain( &chain );

	vuMeter->Release();

	// ---------------------
	// Create VU Meter Graph
	// ---------------------

	vuMeterRMS = console->CreateGraph( outputChannels );
	vuMeterPeak = console->CreateGraph( outputChannels );
	vuMeterRMS->Enable( false );
	vuMeterPeak->Enable( false );

	memset( vuMeterPeakTimes, 0, sizeof( vuMeterPeakTimes ) );

	vuMeterPeak->SetFillMode( idDebugGraph::GRAPH_LINE );
	vuMeterPeak->SetBackgroundColor( idVec4( 0.0f, 0.0f, 0.0f, 0.0f ) );

	vuMeterRMS->AddGridLine( 0.500f, idVec4( 0.5f, 0.5f, 0.5f, 1.0f ) );
	vuMeterRMS->AddGridLine( 0.250f, idVec4( 0.5f, 0.5f, 0.5f, 1.0f ) );
	vuMeterRMS->AddGridLine( 0.125f, idVec4( 0.5f, 0.5f, 0.5f, 1.0f ) );

	const char * channelNames[] = { "L", "R", "C", "S", "Lb", "Rb", "Lf", "Rf", "Cb", "Ls", "Rs" };
	for ( int i = 0, ci = 0; ci < sizeof( channelNames ) / sizeof( channelNames[0] ); ci++ ) {
		if ( ( channelMask & BIT( ci ) ) == 0 ) {
			continue;
		}
		vuMeterRMS->SetLabel( i, channelNames[ ci ] );
		i++;
	}

	// ---------------------
	// Create submix buffer
	// ---------------------
	if ( FAILED( pXAudio2->CreateSubmixVoice( &pSubmixVoice, 1, outputSampleRate, 0, 0, NULL, NULL ) ) ) {
		idLib::FatalError( "Failed to create submix voice" );
	}

	// XAudio doesn't really impose a maximum number of voices
	voices.SetNum( voices.Max() );
	freeVoices.SetNum( voices.Max() );
	zombieVoices.SetNum( 0 );
	for ( int i = 0; i < voices.Num(); i++ ) {
		freeVoices[i] = &voices[i];
	}
// RB end
}