int FMOD_Main()
{
    FMOD::System     *system;
    FMOD::Sound      *sound1, *sound2;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    unsigned int      version;
    int               selection = 0;
    void             *extradriverdata = 0;
    FMOD_SPEAKERMODE  speakermode = FMOD_SPEAKERMODE_STEREO;
    
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

    result = system->getSoftwareFormat(0, &speakermode, 0);
    ERRCHECK(result);

    result = system->createSound(Common_MediaPath("drumloop.wav"), FMOD_2D | FMOD_LOOP_OFF, 0, &sound1);
    ERRCHECK(result);

    result = system->createSound(Common_MediaPath("stereo.ogg"), FMOD_2D | FMOD_LOOP_OFF,  0, &sound2);
    ERRCHECK(result);

    /*
        Main loop.
    */
    do
    {
        Common_Update();

        if (Common_BtnPress(BTN_UP) && (selection != 0))
        {
            selection--;
        }
        
        if (Common_BtnPress(BTN_DOWN) && (selection != (SELECTION_COUNT - 1)))
        {
            selection++;
        }

        if (Common_BtnPress(BTN_ACTION1) && isSelectionAvailable(speakermode, selection))
        {
            if (selection == 0) /* Mono front left */
            {
                result = system->playSound(sound1, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixLevelsOutput(1.0f, 0, 0, 0, 0, 0, 0, 0);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
            else if (selection == 1) /* Mono front right */
            {
                result = system->playSound(sound1, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixLevelsOutput(0, 1.0f, 0, 0, 0, 0, 0, 0);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
            else if (selection == 2) /* Mono center */
            {
                result = system->playSound(sound1, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixLevelsOutput(0, 0, 1.0f, 0, 0, 0, 0, 0);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
            else if (selection == 3) /* Mono surround left */
            {
                result = system->playSound(sound1, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixLevelsOutput(0, 0, 0, 0, 1.0f, 0, 0, 0);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
            else if (selection == 4) /* Mono surround right */
            {
                result = system->playSound(sound1, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixLevelsOutput(0, 0, 0, 0, 0, 1.0f, 0, 0);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
            else if (selection == 5) /* Mono rear left */
            {
                result = system->playSound(sound1, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixLevelsOutput(0, 0, 0, 0, 0, 0, 1.0f, 0);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
            else if (selection == 6) /* Mono rear right */
            {
                result = system->playSound(sound1, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixLevelsOutput(0, 0, 0, 0, 0, 0, 0, 1.0f);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
            else if (selection == 7) /* Stereo front */
            {
                result = system->playSound(sound2, 0, false, &channel);
                ERRCHECK(result);
            }
            else if (selection == 8) /* Stereo front channel swapped */
            {
                float matrix[] = { 0.0f, 1.0f,
                                   1.0f, 0.0f };

                result = system->playSound(sound2, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixMatrix(matrix, 2, 2);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
            else if (selection == 9) /* Stereo (right only) center */
            {
                float matrix[] = { 0.0f, 0.0f,
                                   0.0f, 0.0f,
                                   0.0f, 1.0f };

                result = system->playSound(sound2, 0, true, &channel);
                ERRCHECK(result);

                result = channel->setMixMatrix(matrix, 3, 2);
                ERRCHECK(result);

                result = channel->setPaused(false);
                ERRCHECK(result);
            }
        }

        result = system->update();
        ERRCHECK(result);

        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            bool         playing = false;
            bool         paused = false;
            int          channelsplaying = 0;

            if (channel)
            {
                FMOD::Sound *currentsound = 0;

                result = channel->isPlaying(&playing);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                result = channel->getPaused(&paused);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }
               
                channel->getCurrentSound(&currentsound);
                if (currentsound)
                {
                    result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
                    if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                    {
                        ERRCHECK(result);
                    }
                }
            }

            result = system->getChannelsPlaying(&channelsplaying);
            ERRCHECK(result);

            Common_Draw("==================================================");
            Common_Draw("Multiple Speaker Example.");
            Common_Draw("Copyright (c) Firelight Technologies 2004-2015.");
            Common_Draw("==================================================");
            Common_Draw("");
            Common_Draw("Speaker mode is set to %s%s", SPEAKERMODE_STRING[speakermode], speakermode < FMOD_SPEAKERMODE_7POINT1 ? " causing some speaker options to be unavailable" : "");
            Common_Draw("");
            Common_Draw("Press %s or %s to select mode", Common_BtnStr(BTN_UP), Common_BtnStr(BTN_DOWN));
            Common_Draw("Press %s to play the sound", Common_BtnStr(BTN_ACTION1));
            for (int i = 0; i < SELECTION_COUNT; i++)
            {
                bool disabled = !isSelectionAvailable(speakermode, i);
                Common_Draw("[%c] %s%s", (selection == i) ? (disabled ? '-' : 'X') : ' ', disabled ? "[N/A] " : "", SELECTION_STRING[i]);
            }
            Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));
            Common_Draw("");
            Common_Draw("Time %02d:%02d:%02d/%02d:%02d:%02d : %s", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
            Common_Draw("Channels playing: %d", channelsplaying);
        }

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    /*
        Shut down
    */
    result = sound1->release();
    ERRCHECK(result);
    result = sound2->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    Common_Close();

    return 0;
}