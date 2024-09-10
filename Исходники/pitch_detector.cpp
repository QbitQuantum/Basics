int PitchDetector::DetectPitch()
{
    FMOD::System          *system  = 0;
    FMOD::Sound           *sound   = 0;
    FMOD::Channel         *channel = 0;
    FMOD_RESULT            result;
    FMOD_CREATESOUNDEXINFO exinfo;
    int                    key, driver, recorddriver, numdrivers, count, bin;
    unsigned int           version;    
	
    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		return(-1);
    }

    /* 
        System initialization
    */
    printf("---------------------------------------------------------\n");    
    printf("Select OUTPUT type\n");    
    printf("---------------------------------------------------------\n");    
    printf("1 :  DirectSound\n");
    printf("2 :  Windows Multimedia WaveOut\n");
    printf("3 :  ASIO\n");
    printf("---------------------------------------------------------\n");
    printf("Press a corresponding number or ESC to quit\n");

    do
    {
        //key = _getch();
		key = '1'; //TODO: this uses the default io device rather than using user input
    } while (key != 27 && key < '1' && key > '5');
    
    switch (key)
    {
        case '1' :  result = system->setOutput(FMOD_OUTPUTTYPE_DSOUND);
                    break;
        case '2' :  result = system->setOutput(FMOD_OUTPUTTYPE_WINMM);
                    break;
        case '3' :  result = system->setOutput(FMOD_OUTPUTTYPE_ASIO);
                    break;
        default  :  return(0); 
    }  
    ERRCHECK(result);
    
    /*
        Enumerate playback devices
    */

    result = system->getNumDrivers(&numdrivers);
    ERRCHECK(result);

    printf("---------------------------------------------------------\n");    
    printf("Choose a PLAYBACK driver\n");
    printf("---------------------------------------------------------\n");    
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = system->getDriverInfo(count, name, 256, 0);
        ERRCHECK(result);

        printf("%d : %s\n", count + 1, name);
    }
    printf("---------------------------------------------------------\n");
    printf("Press a corresponding number or ESC to quit\n");

    do
    {
        //key = _getch();
		key = '1'; //TODO: io devices
        if (key == 27)
        {
            return(0);
        }
        driver = key - '1';
    } while (driver < 0 || driver >= numdrivers);

    result = system->setDriver(driver);
    ERRCHECK(result);

    /*
        Enumerate record devices
    */

    result = system->getRecordNumDrivers(&numdrivers);
    ERRCHECK(result);

    printf("---------------------------------------------------------\n");    
    printf("Choose a RECORD driver\n");
    printf("---------------------------------------------------------\n");    
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = system->getRecordDriverInfo(count, name, 256, 0);
        ERRCHECK(result);

        printf("%d : %s\n", count + 1, name);
    }
    printf("---------------------------------------------------------\n");
    printf("Press a corresponding number or ESC to quit\n");

    recorddriver = 0;
    do
    {
        //key = _getch();
		key = '1'; //TODO: io devices
        if (key == 27)
        {
            return(0);
        }
        recorddriver = key - '1';
    } while (recorddriver < 0 || recorddriver >= numdrivers);

    printf("\n");
 
    result = system->setSoftwareFormat(OUTPUT_RATE, FMOD_SOUND_FORMAT_PCM16, 1, 0, FMOD_DSP_RESAMPLER_LINEAR);
    ERRCHECK(result);

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    /*
        Create a sound to record to.
    */
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));

    exinfo.cbsize           = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.numchannels      = 1;
    exinfo.format           = FMOD_SOUND_FORMAT_PCM16;
    exinfo.defaultfrequency = OUTPUT_RATE;
    exinfo.length           = exinfo.defaultfrequency * sizeof(short) * exinfo.numchannels * 5;
    
    result = system->createSound(0, FMOD_2D | FMOD_SOFTWARE | FMOD_LOOP_NORMAL | FMOD_OPENUSER, &exinfo, &sound);
    ERRCHECK(result);

    /*
        Start the interface
    */
    printf("=========================================================================\n");
    printf("Pitch detection example.  Copyright (c) Firelight Technologies 2004-2011.\n");
    printf("=========================================================================\n");
    printf("\n");
    printf("Record something through the selected recording device and FMOD will\n");
    printf("Determine the pitch.  Sustain the tone for at least a second to get an\n");
    printf("accurate reading.\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");

    result = system->recordStart(recorddriver, sound, true);
    ERRCHECK(result);
    
    Sleep(100);      /* Give it some time to record something */
    
    result = system->playSound(FMOD_CHANNEL_REUSE, sound, false, &channel);
    ERRCHECK(result);

    /* Dont hear what is being recorded otherwise it will feedback.  Spectrum analysis is done before volume scaling in the DSP chain */
    result = channel->setVolume(0);
    ERRCHECK(result);

    bin = 0;

    /*
        Main loop.
    */
    do
    {
        static float spectrum[SPECTRUM_SIZE];
        float       dominantHz = 0;
        float       max;
        int         dominantNote = 0;
        float       binSize = BIN_SIZE;
		bool		hasUpdated = false;
		char		windowTitle[sizeof("Pitch Detector: ---")] = "Pitch Detector: ---";
		int			noteIndex;
		double		noteDeviation;
		
        if (_kbhit())
        {
            key = _getch();
        }

        result = channel->getSpectrum(spectrum, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE);
        ERRCHECK(result);

        max = 0;

        for (count = 0; count < SPECTRUM_SIZE; count++)
        {
            if (spectrum[count] > 0.01f && spectrum[count] > max)
            {
                max = spectrum[count];
                bin = count;
				hasUpdated = true;
            }
        }        

        dominantHz  = (float)bin * BIN_SIZE;       /* dominant frequency min */

        dominantNote = 0;
        for (count = 0; count < 120; count++)
        {
             if (dominantHz >= noteFreq[count] && dominantHz < noteFreq[count + 1])
             {
                /* which is it closer to.  This note or the next note */
                if (fabs(dominantHz - noteFreq[count]) < fabs(dominantHz - noteFreq[count+1]))
                {
                    dominantNote = count;
                }
                else
                {
                    dominantNote = count + 1;
                }
                break;
             }
        }

        printf("Detected rate : %7.1f -> %7.1f hz.  Detected musical note. %-3s (%7.1f hz)\r", 
			dominantHz, ((float)bin + 0.99f) * BIN_SIZE, note[dominantNote], noteFreq[dominantNote]);

		// Sets the window title to Pitch Detector: (NOTE)(#|)([0-9]) \| (KEY_MAPPING)
		string noteStr = note[dominantNote];
		noteStr = noteStr[0];
		string keyMapping = " | " + mappingsInterface->GetBoxText(noteStr);
		strncpy(windowTitle + sizeof("Pitch Detector: ") - 1, note[dominantNote], 3);
		if (!hasUpdated) 
		{
			strncpy(windowTitle + sizeof("Pitch Detector: ") - 1, "---", 3);
			keyMapping = "";
		}
		string windowTitleStr = windowTitle;
		emit UpdateTitleSignal(QString((windowTitleStr + keyMapping).c_str()));

		// Sets the feedback of what note is being played
		if (!hasUpdated) 
		{
			noteIndex = -1;
			noteDeviation = 0;
		} 
		else
		{
			noteIndex = NoteToIndex(dominantNote);
			noteDeviation = GetNoteDeviation(dominantHz, dominantNote);
		}
		emit UpdateNoteDisplaySignal(noteIndex, noteDeviation);

        system->update();
        Sleep(10);
    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = sound->release();
    ERRCHECK(result);

    result = system->release();
    ERRCHECK(result);
	return 0;
}