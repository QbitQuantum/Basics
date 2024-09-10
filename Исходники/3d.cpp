int FMOD_Main()
{
    void *extraDriverData = 0;
    Common_Init(&extraDriverData);

    FMOD::Studio::System system;
    FMOD_RESULT result = FMOD::Studio::System::create(&system);
    ERRCHECK(result);

    result = system.initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
    ERRCHECK(result);

    FMOD::Studio::Bank masterBank;
    ERRCHECK( system.loadBankFile(Common_MediaPath("Master Bank.bank"), &masterBank) );

    FMOD::Studio::Bank stringsBank;
    ERRCHECK( system.loadBankFile(Common_MediaPath("Master Bank.bank.strings"), &stringsBank) );

    FMOD::Studio::Bank vehiclesBank;
    ERRCHECK( system.loadBankFile(Common_MediaPath("Vehicles.bank"), &vehiclesBank) );
    
    FMOD::Studio::ID eventID = {0};
    ERRCHECK( system.lookupEventID("/Vehicles/Basic Engine", &eventID) );

    FMOD::Studio::EventDescription eventDescription;
    ERRCHECK( system.getEvent(&eventID, FMOD_STUDIO_LOAD_BEGIN_NOW, &eventDescription) );

    FMOD::Studio::EventInstance eventInstance;
    ERRCHECK( eventDescription.createInstance(&eventInstance) );

    FMOD::Studio::ParameterInstance rpm;
    ERRCHECK( eventInstance.getParameter("RPM", &rpm) );

    ERRCHECK( rpm.setValue(650) );

    ERRCHECK( eventInstance.start() );

    // Position the listener at the origin
    FMOD_3D_ATTRIBUTES attributes = { { 0 } };
    attributes.forward.z = 1.0f;
    attributes.up.y = 1.0f;
    ERRCHECK( system.setListenerAttributes(&attributes) );

    // Position the event 2 units in front of the listener
    attributes.position.z = 2.0f;
    ERRCHECK( eventInstance.set3DAttributes(&attributes) );
    
    initializeScreenBuffer();

    do
    {
        Common_Update();
        
        if (Common_BtnPress(BTN_LEFT))
        {
            attributes.position.x -= 1.0f;
            ERRCHECK( eventInstance.set3DAttributes(&attributes) );
        }
        
        if (Common_BtnPress(BTN_RIGHT))
        {
            attributes.position.x += 1.0f;
            ERRCHECK( eventInstance.set3DAttributes(&attributes) );
        }
        
        if (Common_BtnPress(BTN_UP))
        {
            attributes.position.z += 1.0f;
            ERRCHECK( eventInstance.set3DAttributes(&attributes) );
        }
        
        if (Common_BtnPress(BTN_DOWN))
        {
            attributes.position.z -= 1.0f;
            ERRCHECK( eventInstance.set3DAttributes(&attributes) );
        }

        result = system.update();
        ERRCHECK(result);
        
        updateScreenPosition(attributes.position);
        Common_Draw("==================================================");
        Common_Draw("Event 3D Example.");
        Common_Draw("Copyright (c) Firelight Technologies 2012-2013.");
        Common_Draw("==================================================");
        Common_Draw(screenBuffer);
        Common_Draw("Use the arrow keys (%s, %s, %s, %s) to control the event position", 
            Common_BtnStr(BTN_LEFT), Common_BtnStr(BTN_RIGHT), Common_BtnStr(BTN_UP), Common_BtnStr(BTN_DOWN));
        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    result = system.release();
    ERRCHECK(result);

    Common_Close();

    return 0;
}