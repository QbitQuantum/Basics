void SDLSound::nextSong()
{
    static Mix_Music *music = 0;
    if (music != 0) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = 0;
    }

    if(currentsong == musicfiles.end()) {
        // create a new random playlist
        std::random_shuffle(musicfiles.begin(), musicfiles.end());
        currentsong = musicfiles.begin();
    }

    musics_t::iterator lastsong = currentsong;
    do {
        const char* toplay = currentsong->c_str();
        currentsong++;
#if 0
        /*
         * SDL_Mixer has not Mix_LoadMUS_RW
         */
        try {
            ReadFile *file = FileSystem::openRead(toplay);
            music = Mix_LoadMUS_RW(file->getSDLRWOps(), 1);
            if (music) {
                if (Mix_PlayMusic(music, 1) == 0) {
                    LOG (("Start playing song '%s'", toplay));
                    break; // break while cycle
                } else {
                    LOG (("Failed to play song '%s': %s",
                          toplay, Mix_GetError()));
                }
            } else {
                LOG (("Failed to load mus_rw '%s': %s",
                      toplay, Mix_GetError()));
            }
        } catch (Exception &e) {
            LOG (("Failed to load song '%s': %s",
                  toplay, e.getMessage()));
        }
#else
        music = Mix_LoadMUS(toplay);
        if (music) {
            if (Mix_PlayMusic(music, 1) == 0) {
                LOG (("Start playing song '%s'", toplay));
                break; // break while cycle
            } else {
                LOG (("Failed to play song '%s': %s",
                      toplay, Mix_GetError()));
            }
        } else {
            LOG (("Failed to load song '%s': %s",
                  toplay, Mix_GetError()));
        }
#endif

        if(currentsong == musicfiles.end()) {
            currentsong = musicfiles.begin();
        }
    } while(currentsong != lastsong);
}