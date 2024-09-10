int FMOD_Main()
{
    void *extraDriverData = 0;
    Common_Init(&extraDriverData);

    RunData data;
    Common_Mutex_Create(&data.criticalSection);

    FMOD::Studio::System* system;
    ERRCHECK( FMOD::Studio::System::create(&system) );
    FMOD::System* lowLevelSystem;
    ERRCHECK( system->getLowLevelSystem(&lowLevelSystem) );
    ERRCHECK( lowLevelSystem->setCallback(SystemCallback) );
    ERRCHECK( lowLevelSystem->setUserData(&data) );

    ERRCHECK( system->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData) );

    for (int i=0; i<BANK_COUNT; ++i)
    {
        data.banks[i] = NULL;
    }

    bool wantSampleLoad = false;

    do
    {
        Common_Update();
        
        if (Common_BtnPress(BTN_ACTION1))
        {
            // Start loading all the banks
            for (int i=0; i<BANK_COUNT; ++i)
            {
                if (data.banks[i] == NULL || !data.banks[i]->isValid())
                {
                    FMOD_RESULT result = system->loadBankFile(Common_MediaPath(BANK_NAMES[i]), FMOD_STUDIO_LOAD_BANK_NONBLOCKING, &data.banks[i]);
                    if (result != FMOD_OK)
                    {
                    }
                }
            }
        }
        if (Common_BtnPress(BTN_ACTION2))
        {
            // Unload all banks
            for (int i=0; i<BANK_COUNT; ++i)
            {
                FMOD_RESULT result = data.banks[i]->unload();
                if (result != FMOD_OK)
                {
                }
            }
        }
        if (Common_BtnPress(BTN_MORE))
        {
            wantSampleLoad = !wantSampleLoad;
        }
        // Load bank sample data

        for (int i=0; i<BANK_COUNT; ++i)
        {
            FMOD_STUDIO_LOADING_STATE bankLoadState = FMOD_STUDIO_LOADING_STATE_UNLOADED;
            FMOD_STUDIO_LOADING_STATE sampleLoadState = FMOD_STUDIO_LOADING_STATE_UNLOADED;
            if (data.banks[i] && data.banks[i]->isValid())
            {
                data.banks[i]->getLoadingState(&bankLoadState);
                data.banks[i]->getSampleLoadingState(&sampleLoadState);
            }
            if (bankLoadState == FMOD_STUDIO_LOADING_STATE_LOADED)
            {
                if (wantSampleLoad && sampleLoadState == FMOD_STUDIO_LOADING_STATE_UNLOADED)
                {
                    ERRCHECK(data.banks[i]->loadSampleData());
                }
                else if (!wantSampleLoad && (sampleLoadState == FMOD_STUDIO_LOADING_STATE_LOADING || sampleLoadState == FMOD_STUDIO_LOADING_STATE_LOADED))
                {
                    ERRCHECK(data.banks[i]->unloadSampleData());
                }
            }
        }


        ERRCHECK( system->update() );

        Common_Draw("==================================================");
        Common_Draw("Bank Load Example.");
        Common_Draw("Copyright (c) Firelight Technologies 2014-2014.");
        Common_Draw("==================================================");
        Common_Draw("Name              Handle  Bank-State  Sample-State");

        for (int i=0; i<BANK_COUNT; ++i)
        {
            FMOD_STUDIO_LOADING_STATE bankLoadState = FMOD_STUDIO_LOADING_STATE_UNLOADED;
            FMOD_STUDIO_LOADING_STATE sampleLoadState = FMOD_STUDIO_LOADING_STATE_UNLOADED;
            if (data.banks[i] && data.banks[i]->isValid())
            {
                data.banks[i]->getLoadingState(&bankLoadState);
                data.banks[i]->getSampleLoadingState(&sampleLoadState);
            }
            char namePad[64];
            int bankNameLen = strlen(BANK_NAMES[i]);
            memset(namePad, ' ', 63);
            namePad[16] = '\0';
            strncpy(namePad, BANK_NAMES[i], bankNameLen);

            Common_Draw("%s  %s %s   %s",
                    namePad, getHandleStateString(data.banks[i]), getLoadingStateString(bankLoadState), getLoadingStateString(sampleLoadState));
        }
        Common_Draw("");
        Common_Draw("Press %s to load banks, %s to unload banks", Common_BtnStr(BTN_ACTION1), Common_BtnStr(BTN_ACTION2));
        Common_Draw("Press %s to toggle sample data: %s", Common_BtnStr(BTN_MORE), wantSampleLoad ? "loaded" : "unloaded");
        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));

        {
            Common_Mutex_Enter(&data.criticalSection);
            int errorCount = (int)data.errorStrings.size();
            Common_Draw("Errors (%d):", errorCount);
			int startIndex = errorCount - 6;
			if (startIndex < 0) startIndex = 0;
            for (int i=startIndex; i<errorCount; ++i)
            {
                Common_Draw(" %s", data.errorStrings[i].c_str());
            }
            Common_Mutex_Leave(&data.criticalSection);
        }

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));
    
    for (int i=0; i<BANK_COUNT; ++i)
    {
        if (data.banks[i] != NULL && data.banks[i]->isValid())
        {
            data.banks[i]->unload();
        }
    }

    ERRCHECK( system->release() );

    Common_Mutex_Destroy(&data.criticalSection);
    Common_Close();

    return 0;
}