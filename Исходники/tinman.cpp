void TinMan::Run()
{
	FMOD::Sound * primarySound = GetRandomSound();
	FMOD::Channel * primaryChannel;
	result = system->playSound(FMOD_CHANNEL_FREE, primarySound, true, &primaryChannel);
	ERRCHECK();
	primaryChannel->setVolume(0.f);
	primaryChannel->setPaused(false);

	FMOD::Sound * secondarySound = 0;
	FMOD::Channel * secondaryChannel = 0;

	const unsigned int crossfadeTime = 2500;

	time_t voiceStartTime = time(0) + 10 + (rand() % 20);

	while(true)
	{
		system->update();

		bool isPlaying = false;
		result = primaryChannel->isPlaying(&isPlaying);
		if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
		{
				ERRCHECK();
		}

		if(isPlaying)
		{
			unsigned int primaryPos = 0;
			unsigned int primaryLen = 0;

			result = primaryChannel->getPosition(&primaryPos, FMOD_TIMEUNIT_MS);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
					ERRCHECK();
			}

			result = primarySound->getLength(&primaryLen, FMOD_TIMEUNIT_MS);
			ERRCHECK();

			float volume = 1.f;
			if(primaryPos < crossfadeTime)
			{
				volume = std::max(0.f, std::min((float)(primaryPos)/(float)crossfadeTime, 1.f));
			}
			else if(primaryPos > primaryLen - crossfadeTime)
			{
				volume = std::max(0.f, std::min((float)(primaryLen - primaryPos)/(float)crossfadeTime, 1.f));
			}

			//std::cout<<std::time(0)<<" "<<voiceStartTime<<" "<<primaryPos<<"/"<<primaryLen<<" "<<volume<<"\n";

			result = primaryChannel->setVolume(volume);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
					ERRCHECK();
			}

			if(primaryPos > primaryLen - crossfadeTime)
			{
				if(!secondaryChannel)
				{
					secondarySound = GetRandomSound();
					result = system->playSound(FMOD_CHANNEL_FREE, secondarySound, true, &secondaryChannel);
					ERRCHECK();
					result = secondaryChannel->setVolume(1.f - volume);
					ERRCHECK();
					result = secondaryChannel->setPaused(false);
					ERRCHECK();
				}
				else
				{
					secondaryChannel->setVolume(1.f - volume);
					if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
					{
							ERRCHECK();
					}
				}
			}
		}
		else
		{
			if(secondaryChannel && secondarySound)
			{
				primaryChannel = secondaryChannel;
				primarySound = secondarySound;
				secondaryChannel = 0;
			}
			else
			{
				// for some reason all channels are stopped
				primarySound = GetRandomSound();
				result = system->playSound(FMOD_CHANNEL_FREE, primarySound, 0, &primaryChannel);
				ERRCHECK();
			}
		}

		if(time(0) >= voiceStartTime)
		{
			voiceStartTime = time(0) + 15 + (rand() % 25);
			PlayVoice();
		}

		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}
}