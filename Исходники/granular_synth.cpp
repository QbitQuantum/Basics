int FMOD_Main()
{
    FMOD::Channel    *channel[2] = { 0,0 };
    FMOD_RESULT       result;
    int               outputrate, slot = 0;
    unsigned int      version;
    void             *extradriverdata = 0;
    bool              paused = false;

    Common_Init(&extradriverdata);
    
    result = FMOD::System_Create(&gSystem);
    ERRCHECK(result);
    
    result = gSystem->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    }
    
    result = gSystem->init(100, FMOD_INIT_NORMAL, extradriverdata);
    ERRCHECK(result);
       
    result = gSystem->getSoftwareFormat(&outputrate, 0, 0);
    ERRCHECK(result);   
   
#if !defined(USE_STREAMS)
    for (unsigned int count = 0; count < NUMSOUNDS; count++)
    {
        result = gSystem->createSound(soundname[count], FMOD_IGNORETAGS, 0, &sound[count]);
        ERRCHECK(result);
    }
#endif

    /*
        Kick off the first 2 sounds.  First one is immediate, second one will be triggered to start after the first one.
    */
    channel[slot] = queue_next_sound(outputrate, channel[1-slot], rand()%NUMSOUNDS, slot);
    slot = 1-slot;  /* flip */
    channel[slot] = queue_next_sound(outputrate, channel[1-slot], rand()%NUMSOUNDS, slot);
    slot = 1-slot;  /* flip */

    do
    {
        bool isplaying = false;

        Common_Update();

        if (Common_BtnPress(BTN_ACTION1))
        {
            FMOD::ChannelGroup *mastergroup;

            paused = !paused;

            result = gSystem->getMasterChannelGroup(&mastergroup);
            ERRCHECK(result);
            result = mastergroup->setPaused(paused);
            ERRCHECK(result);
        }

        result = gSystem->update();
        ERRCHECK(result);

        /*
            Replace the sound that just finished with a new sound, to create endless seamless stitching!
        */
        result = channel[slot]->isPlaying(&isplaying);
        if (result != FMOD_ERR_INVALID_HANDLE)
        {
            ERRCHECK(result);
        }

        if (!isplaying && !paused)
        {
#ifdef USE_STREAMS
            /* 
                Release the sound that isn't playing any more. 
            */
            result = sound[slot]->release();       
            ERRCHECK(result);
            sound[slot] = 0;
#endif

            /*
                Replace sound that just ended with a new sound, queued up to trigger exactly after the other sound ends.
            */
            channel[slot] = queue_next_sound(outputrate, channel[1-slot], rand()%NUMSOUNDS, slot);
            slot = 1-slot;  /* flip */
        }

        Common_Draw("==================================================");
        Common_Draw("Granular Synthesis SetDelay Example.");
        Common_Draw("Copyright (c) Firelight Technologies 2004-2014.");
        Common_Draw("==================================================");
        Common_Draw("");
        Common_Draw("Toggle #define USE_STREAM on/off in code to switch between streams and static samples.");
        Common_Draw("");
        Common_Draw("Press %s to pause", Common_BtnStr(BTN_ACTION1));
        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));
        Common_Draw("");
        Common_Draw("Channels are %s", paused ? "paused" : "playing");

        Common_Sleep(10);   /* If you wait too long, ie longer than the length of the shortest sound, you will get gaps. */
    } while (!Common_BtnPress(BTN_QUIT));

    /*
        Shut down
    */
    for (unsigned int count = 0; count < sizeof(sound) / sizeof(sound[0]); count++)
    {
        if (sound[count])
        {
            result = sound[count]->release();
            ERRCHECK(result);
        }
    }
    
    result = gSystem->release();
    ERRCHECK(result);

    Common_Close();

    return 0;
}