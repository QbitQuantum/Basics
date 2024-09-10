int FMOD_Main()
{
    void *extraDriverData = NULL;
    Common_Init(&extraDriverData);

    FMOD::Studio::System* system = NULL;
    ERRCHECK( FMOD::Studio::System::create(&system) );

    // The example Studio project is authored for 5.1 sound, so set up the system output mode to match
    FMOD::System* lowLevelSystem = NULL;
    ERRCHECK( system->getLowLevelSystem(&lowLevelSystem) );
    ERRCHECK( lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0) );

    ERRCHECK( system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData) );

    FMOD::Studio::Bank* masterBank = NULL;
    ERRCHECK( system->loadBankFile(Common_MediaPath("Master Bank.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );

    FMOD::Studio::Bank* stringsBank = NULL;
    ERRCHECK( system->loadBankFile(Common_MediaPath("Master Bank.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );

    FMOD::Studio::Bank* ambienceBank = NULL;
    ERRCHECK( system->loadBankFile(Common_MediaPath("Character.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &ambienceBank) );

    FMOD::Studio::EventDescription* eventDescription = NULL;
    ERRCHECK( system->getEvent("event:/Character/Radio/Command", &eventDescription) );

    FMOD::Studio::EventInstance* eventInstance = NULL;
    ERRCHECK( eventDescription->createInstance(&eventInstance) );
    
    ProgrammerSoundContext programmerSoundContext;
    ERRCHECK( system->getLowLevelSystem(&programmerSoundContext.system) );

    ERRCHECK( eventInstance->setUserData(&programmerSoundContext) );
    ERRCHECK( eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );

    ERRCHECK( eventInstance->setVolume(0.75f) );

    do
    {
        Common_Update();

        if (Common_BtnPress(BTN_ACTION1))
        {
            programmerSoundContext.soundName = Common_MediaPath("640166main_MECO.ogg");
            ERRCHECK( eventInstance->start() );
        }

        if (Common_BtnPress(BTN_ACTION2))
        {
            programmerSoundContext.soundName = Common_MediaPath("640169main_Press to ATO.ogg");
            ERRCHECK( eventInstance->start() );
        }

        if (Common_BtnPress(BTN_ACTION3))
        {
            programmerSoundContext.soundName = Common_MediaPath("640148main_APU Shutdown.ogg");
            ERRCHECK( eventInstance->start() );
        }

        if (Common_BtnPress(BTN_ACTION4))
        {
            programmerSoundContext.soundName = Common_MediaPath("640165main_Lookin At It.ogg");
            ERRCHECK( eventInstance->start() );
        }

        ERRCHECK( system->update() );

        Common_Draw("==================================================");
        Common_Draw("Programmer Sound Example.");
        Common_Draw("Copyright (c) Firelight Technologies 2016-2016.");
        Common_Draw("==================================================");
        Common_Draw("");
        Common_Draw("Press %s to play event with sound 1", Common_BtnStr(BTN_ACTION1));
        Common_Draw("Press %s to play event with sound 2", Common_BtnStr(BTN_ACTION2));
        Common_Draw("Press %s to play event with sound 3", Common_BtnStr(BTN_ACTION3));
        Common_Draw("Press %s to play event with sound 4", Common_BtnStr(BTN_ACTION4));
        Common_Draw("");
        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    ERRCHECK( system->release() );

    Common_Close();

    return 0;
}