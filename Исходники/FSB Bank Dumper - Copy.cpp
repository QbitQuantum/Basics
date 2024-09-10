int FMOD_Main()
{
	cout << "Tellale Music Extractor" << endl;
	cout << "FMOD Bank Extractor" << endl;
	cout << "Copyright (c) 2015 Bennyboy" << endl;
	cout << "Http://quickandeasysoftware.net" << endl << endl;

	//cout << "Dumping to " << argv[0] << endl << endl;
	cout << "Dumping will take some time, please be patient." << endl << endl;




	void *extraDriverData = 0;
	Common_Init(&extraDriverData);

	//Studio high level system
	FMOD::Studio::System* system = NULL;
	FMOD_RESULT result = FMOD::Studio::System::create(&system);
	ERRCHECK(result);

	//Low level system
	//FMOD::System* lowLevel;
	//system->getLowLevelSystem(&lowLevel);

	//Set output to wav file. NRT means we control the playback speed with update()
	//lowLevel->setOutput(FMOD_OUTPUTTYPE_WAVWRITER_NRT);    




	//Initialise the system. 
	result = system->initialize(32, FMOD_STUDIO_INIT_ALLOW_MISSING_PLUGINS, FMOD_INIT_NORMAL, extraDriverData);
	ERRCHECK(result);


	//Load all .bank files from dir into vector
	std::vector<std::string> FilesInDir;
	GetBankFilesInDirectory(FilesInDir, "C:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/studio/examples/test/");


	//Create vector to hold all the bank instances
	std::vector<FMOD::Studio::Bank* > vbank_;
	int FileArraySize = FilesInDir.size();

	//Set size of the vector to the number of banks and initialise each bank to null 
	vbank_.resize(FileArraySize);
	for (int i = 0; i <= FileArraySize - 1; i++)
	{
		vbank_[i] = NULL; //initialise banks
	}

	//Loop through and load the banks from our bank instances
	for (int i = 0; i <= FileArraySize - 1; i++)
	{
		system->loadBankFile(FilesInDir[i].c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &vbank_[i]);
		//Bank loading is asynchronous - so make sure its finished loading before we do operations on it. Easier just to wait here after we load each bank.
		FMOD_STUDIO_LOADING_STATE  bankloadingState = FMOD_STUDIO_LOADING_STATE_LOADING;
		while (bankloadingState != FMOD_STUDIO_LOADING_STATE_LOADED)
		{
			system->update();
			ERRCHECK(vbank_[i]->getLoadingState(&bankloadingState));
		}
	}


	//Preload all samples in all banks
	//for ( int i = 0 ; i <= FileArraySize-1 ; i++ )
	//{
	//	vbank_[i]->loadSampleData();
	//	FMOD_STUDIO_LOADING_STATE  loadingState = FMOD_STUDIO_LOADING_STATE_UNLOADED;
	//	while (loadingState !=FMOD_STUDIO_LOADING_STATE_LOADED)
	//	{
	//		if (vbank_[i]->getSampleLoadingState(&loadingState)  == FMOD_OK)
	//		{
	//			system->update();
	//		}
	//		else
	//		{}
	//	}
	//}


	//Create an array to hold all the Event ID's
	std::vector<std::string> idVector;

	//Get all the event ID's from the banks and store them in idVector
	for (int i = 0; i <= FileArraySize - 1; i++)
	{
		int eventCount = 0;
		int maxLen = 255;
		char buffer[255 + 1];

		vbank_[i]->getEventCount(&eventCount); //get the number of events in the bank

											   //Create an array to hold the eventdescriptions
		FMOD::Studio::EventDescription** eventArray = (FMOD::Studio::EventDescription**)malloc(eventCount * sizeof(void*));

		//Fill the array with the events from the bank
		result = vbank_[i]->getEventList(eventArray, eventCount, &eventCount);
		if (result == FMOD_OK)
		{
			for (int j = 0; j < eventCount; j++)
			{
				//Get the ID
				result = eventArray[j]->getPath(buffer, maxLen, 0);
				if (result == FMOD_OK)
				{
					//OutputDebugString(buffer); OutputDebugString("\n");
					if (strncmp(buffer, "event", 5) == 0) //only add "event" ID's
					{
						idVector.push_back(buffer); //add it as a new element at the end of the vector
					}
				}
				else
				{
					OutputDebugString("OI! couldnt get ID!");
				}
			}
		}

		free(eventArray);
	}


	//Free the system so we can create a new one and control the output filename
	result = system->release();
	ERRCHECK(result);


	//Loop through each ID
	for (int i = 0; i <= idVector.size() - 1; i++)
	{

		//Studio high level system
		FMOD::Studio::System* system = NULL;
		FMOD_RESULT result = FMOD::Studio::System::create(&system);
		ERRCHECK(result);

		//Low level system
		FMOD::System* lowLevel;
		system->getLowLevelSystem(&lowLevel);

		//Set output to wav file. NRT means we control the playback speed with update()
		lowLevel->setOutput(FMOD_OUTPUTTYPE_WAVWRITER_NRT);


		//Extract filename
		std::string tempString = idVector[i];//.c_str();
		std::string filename;
		unsigned found = tempString.find_last_of("/\\");
		filename = tempString.substr(found + 1);
		filename.append(".wav");



		//Initialise the system. 
		//Need STREAM_FROM_UPDATE as we're using WAVWRITER_NRT. Need the synchronous here?? Thread unsafe for low level - dunno
		result = system->initialize(32, FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE, FMOD_INIT_STREAM_FROM_UPDATE | FMOD_INIT_THREAD_UNSAFE, (char*)filename.c_str());
		ERRCHECK(result);


		//Loop through and load the banks from our bank instances (banks already stored in array earlier)
		for (int j = 0; j <= FileArraySize - 1; j++)
		{
			system->loadBankFile(FilesInDir[j].c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &vbank_[j]);

			//Bank loading is asynchronous - so make sure its finished loading before we do operations on it. Easier just to wait here after we load each bank.
			system->update();
			FMOD_STUDIO_LOADING_STATE  bankloadingState = FMOD_STUDIO_LOADING_STATE_LOADING;
			ERRCHECK(vbank_[j]->getLoadingState(&bankloadingState));
			while (bankloadingState == FMOD_STUDIO_LOADING_STATE_LOADING)
			{

				ERRCHECK(vbank_[j]->getLoadingState(&bankloadingState));
			}
		}




		//Playback and save the file
		outputEventByID(system, idVector[i].c_str());


		//Free the system so we can create a new one and control the output filename
		result = system->release();
		ERRCHECK(result);
		lowLevel->release();
	}




	Common_Close();

	return 0;
}