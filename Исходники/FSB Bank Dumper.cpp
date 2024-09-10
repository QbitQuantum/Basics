bool outputEventByID(FMOD::Studio::System* system, const char* ID)
{
	FMOD_RESULT result;

	FMOD::Studio::ID eventID = { 0 };
	ERRCHECK(system->lookupID(ID, &eventID));  //Lookup the ID string from the banks

	//Use the ID to get the event
	FMOD::Studio::EventDescription* eventDescription = NULL;
	ERRCHECK(system->getEventByID(&eventID, &eventDescription));

	// Create an instance of the event
	FMOD::Studio::EventInstance* eventInstance = NULL;
	ERRCHECK(eventDescription->createInstance(&eventInstance));
	
	//Preload sample data - otherwise some sounds just dont play
	//eventDescription->loadSampleData(); Done need this -  docs say it starts loading sample as soon as eventinstance created
	FMOD_STUDIO_LOADING_STATE  loadingState = FMOD_STUDIO_LOADING_STATE_LOADING;
	system->update();
	ERRCHECK(eventDescription->getSampleLoadingState(&loadingState));
	while (loadingState != FMOD_STUDIO_LOADING_STATE_LOADED)
	{
		ERRCHECK(eventDescription->getSampleLoadingState(&loadingState));
		system->update();
	}

	
	int length = 0;
	result = eventDescription->getLength(&length);
	if (length == 0)
	{
		return false; 
	}


	cout << "Dumping " << ID << endl;

	int TimelinePos = 0;
	int LastPos = -1;
	bool played = false;

	while (TimelinePos < length)
	{
		if (!played)
		{
			ERRCHECK(eventInstance->start()); //Start playback
			played = true;
		}
		
		eventInstance->getTimelinePosition(&TimelinePos);
		//char buffer[255 + 1];
		//sprintf(buffer, "Timeline Position is %d\n", TimelinePos);
		//OutputDebugString(buffer);

		if (LastPos > TimelinePos) //Looping sounds repeat and have wrong getlength value eg mus_loop_tense never reaches timelinepos 
		{						   //Seems to report a longer length than reality. So if we dont manually stop it, the track loops forever
			break;
		}
		LastPos = TimelinePos;
		system->update();
		Sleep(1);   //Crucial! Slows it down enough so that sounds start and end at correct time
					//Big hack but still cant fix it. Tried with callbacks and other methods - this
					//Is the only way that 'reliably' works
	}

	eventInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE); //FMOD_STUDIO_STOP_ALLOWFADEOUT 
	FMOD_STUDIO_PLAYBACK_STATE playbackState = FMOD_STUDIO_PLAYBACK_STOPPING;
	while (playbackState != FMOD_STUDIO_PLAYBACK_STOPPED)
	{
		eventInstance->getPlaybackState(&playbackState);
		system->update();
	}

	eventInstance->release(); //necessary?????
	eventDescription->unloadSampleData();

	system->update();
	loadingState = FMOD_STUDIO_LOADING_STATE_LOADED;
	while (loadingState != FMOD_STUDIO_LOADING_STATE_UNLOADED)
	{
		if (eventDescription->getSampleLoadingState(&loadingState) == FMOD_OK)
		{
			//system->update();
		}
		else
		{
		}
	}

	//eventDescription->releaseAllInstances;
	return true;
}