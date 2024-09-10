// Starting a sound means adding it
//  to the current list of active sounds
//  in the internal channels.
// As the SFX info struct contains
//  e.g. a pointer to the raw data,
//  it is ignored.
// As our sound handling does not handle
//  priority, it is ignored.
// Pitching (that is, increased speed of playback) is set
//
int I_StartSound2 ( int id, int player, mobj_t *origin, mobj_t *listener_origin, int pitch, int priority ) {
	if ( !soundHardwareInitialized ) {
		return id;
	}
	
	int i;
	 XAUDIO2_VOICE_STATE state;
	activeSound_t* sound = 0;
	int oldest = 0, oldestnum = -1;

	// these id's should not overlap
	if ( id == sfx_sawup || id == sfx_sawidl || id == sfx_sawful || id == sfx_sawhit || id == sfx_stnmov ) {
		// Loop all channels, check.
		for (i=0 ; i < NUM_SOUNDBUFFERS ; i++)
		{
			sound = &activeSounds[i];

			if (sound->valid && ( sound->id == id && sound->player == player ) ) {
				I_StopSound( sound->id, player );
				break;
			}
		}
	}

	// find a valid channel, or one that has finished playing
	for (i = 0; i < NUM_SOUNDBUFFERS; ++i) {
		sound = &activeSounds[i];
		
		if (!sound->valid)
			break;

		if (!oldest || oldest > sound->start) {
			oldestnum = i;
			oldest = sound->start;
		}

		sound->m_pSourceVoice->GetState( &state );
		if ( state.BuffersQueued == 0 ) {
			break;
		}
	}

	// none found, so use the oldest one
	if (i == NUM_SOUNDBUFFERS)
	{
		i = oldestnum;
		sound = &activeSounds[i];
	}

	// stop the sound with a FlushPackets
	sound->m_pSourceVoice->Stop();
	sound->m_pSourceVoice->FlushSourceBuffers();

	// Set up packet
	XAUDIO2_BUFFER Packet = { 0 };
	Packet.Flags = XAUDIO2_END_OF_STREAM;
	Packet.AudioBytes = lengths[id];
	Packet.pAudioData = (BYTE*)S_sfx[id].data;
	Packet.PlayBegin = 0;
	Packet.PlayLength = 0;
	Packet.LoopBegin = XAUDIO2_NO_LOOP_REGION;
	Packet.LoopLength = 0;
	Packet.LoopCount = 0;
	Packet.pContext = NULL;


	// Set voice volumes
	sound->m_pSourceVoice->SetVolume( x_SoundVolume );

	// Set voice pitch
	sound->m_pSourceVoice->SetFrequencyRatio( 1 + ((float)pitch-128.f)/95.f );

	// Set initial spatialization
	if ( origin && origin != listener_origin ) {
		// Update Emitter Position
		sound->m_Emitter.Position.x = (float)(origin->x >> FRACBITS);
		sound->m_Emitter.Position.y = 0.f;
		sound->m_Emitter.Position.z = (float)(origin->y >> FRACBITS);

		// Calculate 3D positioned speaker volumes
		DWORD dwCalculateFlags = X3DAUDIO_CALCULATE_MATRIX;
		X3DAudioCalculate( X3DAudioInstance, &doom_Listener, &sound->m_Emitter, dwCalculateFlags, &sound->m_DSPSettings );

		// Pan the voice according to X3DAudio calculation
		sound->m_pSourceVoice->SetOutputMatrix( NULL, 1, numOutputChannels, sound->m_DSPSettings.pMatrixCoefficients );

		sound->localSound = false;
	} else {