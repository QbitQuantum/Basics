Spectrum::Spectrum(bool &creationSucceeded)
{
	creationSucceeded = false;

	//
	if(FMOD::System_Create(&system_) == FMOD_OK)
	{
		//
		if((system_->setOutput(FMOD_OUTPUTTYPE_AUTODETECT) == FMOD_OK) && (system_->setDriver(DEFAULT_SOUND_DRIVER) == FMOD_OK))
		{
			//
			if(system_->init(NUM_RECORDING_CHANNELS, FMOD_INIT_NORMAL, NULL) == FMOD_OK)
			{
				FMOD::Sound *sound;
				FMOD_CREATESOUNDEXINFO soundInfo;

				ZeroMemory(&soundInfo, sizeof(FMOD_CREATESOUNDEXINFO));
				soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
				soundInfo.length = (unsigned int)(sizeof(int) * NUM_RECORDING_SAMPLES * NUM_RECORDING_SECONDS);
				soundInfo.numchannels = NUM_RECORDING_CHANNELS;
				soundInfo.defaultfrequency = NUM_RECORDING_SAMPLES;
				soundInfo.format = FMOD_SOUND_FORMAT_PCM16;

				//
				if(system_->createSound(NULL, FMOD_2D | FMOD_OPENUSER | FMOD_LOOP_NORMAL | FMOD_SOFTWARE, &soundInfo, &sound) == FMOD_OK)
				{
					//
					system_->recordStart(SOUND_IDENTIFIER, sound, true);
					system_->playSound(FMOD_CHANNEL_FREE, sound, false, &channel_);

					//
					FMOD::ChannelGroup *channelGroup;
					system_->createChannelGroup("silentChannel", &channelGroup);
					channel_->setChannelGroup(channelGroup);
					channelGroup->setMute(true);

					creationSucceeded = true;
				}
			}
		}
	}

	//Left Initialisation
	leftSpectrum_ = new float[SPECTRUM_WIDTH];
	leftInstantSpectrum_ = new float[SPECTRUM_WIDTH];
	previousLeftSpectrum_ = new float[SPECTRUM_WIDTH];

	ZeroMemory(leftSpectrum_, sizeof(float) * SPECTRUM_WIDTH);
	ZeroMemory(leftInstantSpectrum_, sizeof(float) * SPECTRUM_WIDTH);	
	ZeroMemory(previousLeftSpectrum_, sizeof(float) * SPECTRUM_WIDTH);

	//Right Initialisation
	rightSpectrum_ = new float[SPECTRUM_WIDTH];
	rightInstantSpectrum_ = new float[SPECTRUM_WIDTH];
	previousRightSpectrum_ = new float[SPECTRUM_WIDTH];

	ZeroMemory(rightSpectrum_, sizeof(float) * SPECTRUM_WIDTH);
	ZeroMemory(rightInstantSpectrum_, sizeof(float) * SPECTRUM_WIDTH);	
	ZeroMemory(previousRightSpectrum_, sizeof(float) * SPECTRUM_WIDTH);	


	bandResponceCollections_ = new list<ResponceCollection>();

	spectrumVolume_ = CLAMP(1.0f, MIN_ADAPTIVE_MULTIPLIER, MAX_ADAPTIVE_MULTIPLIER);
	adaptiveVolumeEnabled_ = false;

	peakVolumeHistory_ = NULL;
	modifySpectrumResponce(1.0f);

	pulseThreshold_ = PULSE_THRESHOLD;
	smoothingFactor_ = SMOOTHING_FACTOR;
}