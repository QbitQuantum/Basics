int FMOD_Main()
{
    FMOD::System       *system;
    FMOD::Sound        *sound;
    FMOD::Channel      *channel;
    FMOD::DSP          *mydsp;
    FMOD::ChannelGroup *mastergroup;
    FMOD_RESULT         result;
    unsigned int        version;
    void               *extradriverdata = 0;

    Common_Init(&extradriverdata);

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    }

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    ERRCHECK(result);

    result = system->createSound(Common_MediaPath("drumloop.wav"), FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound);
    ERRCHECK(result);

    result = system->playSound(sound, 0, false, &channel);
    ERRCHECK(result);

    /*
        Create the DSP effect.
    */  
    { 
        FMOD_DSP_DESCRIPTION dspdesc; 
        memset(&dspdesc, 0, sizeof(dspdesc));
        
        strncpy(dspdesc.name, "My first DSP unit", sizeof(dspdesc.name));
        dspdesc.version = 0x00010000;
        dspdesc.numinputbuffers = 1;
        dspdesc.numoutputbuffers = 1;
        dspdesc.read = myDSPCallback; 
        dspdesc.userdata = (void *)0x12345678; 

        result = system->createDSP(&dspdesc, &mydsp); 
        ERRCHECK(result); 
    } 

    /*
        Attach the DSP, inactive by default.
    */
    result = mydsp->setBypass(true);
    ERRCHECK(result);

    result = system->getMasterChannelGroup(&mastergroup);
    ERRCHECK(result);

    result = mastergroup->addDSP(0, mydsp, 0);
    ERRCHECK(result);

    /*
        Main loop.
    */
    do
    {
        bool bypass;

        Common_Update();

        result = mydsp->getBypass(&bypass);
        ERRCHECK(result);

        if (Common_BtnPress(BTN_ACTION1))
        {
            bypass = !bypass;
            
            result = mydsp->setBypass(bypass);
            ERRCHECK(result);
        }

        result = system->update();
        ERRCHECK(result);

        Common_Draw("==================================================");
        Common_Draw("Custom DSP Example.");
        Common_Draw("Copyright (c) Firelight Technologies 2004-2014.");
        Common_Draw("==================================================");
        Common_Draw("");
        Common_Draw("Press %s to toggle filter bypass", Common_BtnStr(BTN_ACTION1));
        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));
        Common_Draw("");
        Common_Draw("Filter is %s", bypass ? "inactive" : "active");

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    /*
        Shut down
    */
    result = sound->release();
    ERRCHECK(result);

    result = mastergroup->removeDSP(mydsp);
    ERRCHECK(result);
    result = mydsp->release();
    ERRCHECK(result);

    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    Common_Close();

    return 0;
}