int audioMultiPlayer::playSound(string songPath, string songName, bool firstStart, pthread_mutex_t* mut) {
    int key;

    /*
        Create a System object and initialize.
     */
    result = FMOD::System_Create(&system);
    utilities::ERRCHECK(result);

    result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
    utilities::ERRCHECK(result);

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    utilities::ERRCHECK(result);

    /* INIT SONG */
    result = system->createSound(songPath.c_str(), FMOD_SOFTWARE, 0, &sound1);
    utilities::ERRCHECK(result);

    

    if (firstStart) {
        printf("===================================================================\n");
        printf("Lecteur Audio (Mix)\n");
        printf("===================================================================\n");
        printf("1) %s\n", songName.c_str());
    } else if (!firstStart) {
		sleep(1);
        printf("2) %s\n", songName.c_str());
        printf("===================================================================\n");
        printf("\n");
        printf("'Space' -> FadIn/FadOut\n");
        printf("'Esc'   -> Quitter\n");
        printf("\n");
    }
	
	/* PLAY SONG */
    result = system->playSound(FMOD_CHANNEL_FREE, sound1, 0, &channel);
    utilities::ERRCHECK(result);
	
	if(!firstStart) {
		channel->setVolume(0.0f);
        playPause();
	}

    do {
        //FADIN
        if (flagFadIn) {
            float volume;
            channel->getVolume(&volume);
            channel->setVolume(volume + 0.0005f);
            usleep(1000);
            if (volume == 1.0f) {
                flagFadIn = false;
                pthread_mutex_unlock(mut);
                if (firstStart) {
                    printf("FadIn finish for first song (mutex unlock)\n");
                } else {
                    printf("FadIn finish for second song (mutex unlock)\n");
                }
                fflush(stdout);
            }
        }

        //FADOUT
        if (flagFadOut) {
            float volume;
            channel->getVolume(&volume);
            channel->setVolume(volume - 0.0005f);
            usleep(1000);
            if (volume == 0.0f) {
                flagFadOut = false;
                playPause();
                ualarm(1,0);
                if (firstStart) {
                    printf("FadOut finish for first song\n");
                } else {
                    printf("FadOut finish for second song\n");
                }
                fflush(stdout);
            }
        }

        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            bool playing = 0;
            bool paused = 0;

            if (channel) {
                FMOD::Sound *currentsound = 0;

                result = channel->isPlaying(&playing);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                    utilities::ERRCHECK(result);
                }

                result = channel->getPaused(&paused);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                    utilities::ERRCHECK(result);
                }

                result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                    utilities::ERRCHECK(result);
                }

                channel->getCurrentSound(&currentsound);
                if (currentsound) {
                    result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
                    if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN)) {
                        utilities::ERRCHECK(result);
                    }
                }
            }
        }
    } while (key != 27);

    printf("\n");

    release();
    return 0;
}