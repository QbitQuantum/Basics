int fs_ml_event_loop(void)
{
    // printf("fs_ml_event_loop\n");
    int result = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            fs_log("Received SDL_QUIT\n");
            fs_ml_quit();
#ifdef FS_EMU_DRIVERS
            printf("returning 1 from fs_ml_event_loop\n");
            result = 1;
#endif
            continue;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                on_resize(event.window.data1, event.window.data2);
            } else if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                event.type = SDL_QUIT;
                SDL_PushEvent(&event);
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                if (g_grab_input_on_activate) {
                    fs_log("Window focus gained - grabbing input\n");
                    g_grab_input_on_activate = false;
                    fs_ml_set_input_grab(true);
#ifdef MACOSX
                } else if (fs_ml_input_grab()) {
                    /* Input grab could be "lost" due to Cmd+Tab */
                    fs_log("Forcing re-grab of input on OS X\n");
                    fs_ml_set_input_grab(false);
                    fs_ml_set_input_grab(true);
#endif
                }
            }
            continue;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (g_fs_log_input) {
                fs_log("SDL key sym %d mod %d scancode %d state %d repeat %d\n",
                        event.key.keysym.sym, event.key.keysym.mod,
                        event.key.keysym.scancode, event.key.state,
                       event.key.repeat);
            }
            if (event.key.repeat) {
                continue;
            }
            if (event.key.keysym.sym == 0 && event.key.keysym.scancode == 0) {
                /* ignore "ghost key" seen on OS X which without this
                 * specific check will cause the A key to be mysteriously
                 * pressed. */
                if (g_fs_log_input) {
                    fs_log("- ignored key with keysym 0 and scancode 0\n");
                }
                continue;
            }
            /*
            if (event.key.keysym.sym == SDLK_F12) {
                g_f12_state = event.key.state ? FS_ML_KEY_MOD_F12 : 0;
                printf("-- g_f12_state is %d\n", g_f12_state);
            }
            else if (event.key.keysym.sym == SDLK_F11) {
                g_f11_state = event.key.state ? FS_ML_KEY_MOD_F11 : 0;
            }
            */

            const Uint8* key_state;
            int num_keys;
            key_state = SDL_GetKeyboardState(&num_keys);
            g_f11_state = key_state[SDL_SCANCODE_F11] ? FS_ML_KEY_MOD_F11 : 0;
            g_f12_state = key_state[SDL_SCANCODE_F12] ? FS_ML_KEY_MOD_F12 : 0;

            int key = -1;
            if (event.key.keysym.scancode <= LAST_SDL2_SCANCODE) {
                key = g_sdl2_keys[event.key.keysym.scancode];
            }
#if defined(MACOSX)
#elif defined(WINDOWS)
#else
            else if (event.key.keysym.sym == SDLK_MODE) {
                key = SDLK_RALT;
            }
#endif
            else {
                key = fs_ml_scancode_to_key(event.key.keysym.scancode);
            }

#ifdef USE_SDL2
            if (0) {
                // the below trick does not currently work for SDL2, as
                // there is no mapping yet for translated keys
            }
#else
            if (g_f12_state || g_f11_state) {
                // leave translated key code in keysym
            }
#endif
            else if (key >= 0) {
                if (g_fs_log_input) {
                    fs_log("- key code set to %d (was %d) based on "
                           "scancode %d\n", key, event.key.keysym.sym,
                           event.key.keysym.scancode);
                }
                event.key.keysym.sym = key;
            }

            int mod = event.key.keysym.mod;
            if (mod & KMOD_LSHIFT || mod & KMOD_RSHIFT)
                event.key.keysym.mod |= KMOD_SHIFT;
#if 0
            if (mod & KMOD_LALT || mod & KMOD_RALT)
                event.key.keysym.mod |= KMOD_ALT;
#endif
            if (mod & KMOD_LCTRL || mod & KMOD_RCTRL)
                event.key.keysym.mod |= KMOD_CTRL;
#if 0
            if (mod & KMOD_LMETA || mod & KMOD_RMETA)
                event.key.keysym.mod |= KMOD_META;
#endif

            /* Filter out other modidifers */
            event.key.keysym.mod &=
                        KMOD_SHIFT | KMOD_ALT | KMOD_CTRL | KMOD_META;
            /* Add F11/F12 modifier state */
            event.key.keysym.mod |= g_f11_state | g_f12_state;

            //printf("%d %d %d %d\n", event.key.keysym.mod,
            //        KMOD_ALT, KMOD_LALT, KMOD_RALT);
            break;
        //case SDL_MOUSEBUTTONDOWN:
        //    printf("--- mousebutton down ---\n");
        }
        fs_ml_event *new_event = NULL;

        if (event.type == SDL_KEYDOWN) {
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_KEYDOWN;
            new_event->key.keysym.sym = event.key.keysym.sym;
            new_event->key.keysym.mod = event.key.keysym.mod;
            new_event->key.state = event.key.state;
        }
        else if (event.type == SDL_KEYUP) {
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_KEYUP;
            new_event->key.keysym.sym = event.key.keysym.sym;
            new_event->key.keysym.mod = event.key.keysym.mod;
            new_event->key.state = event.key.state;
        }
        else if (event.type == SDL_JOYBUTTONDOWN) {
            if (g_fs_log_input) {
                fs_log("SDL_JOYBUTTONDOWN which %d button %d state %d\n",
                       event.jbutton.which, event.jbutton.button,
                       event.jbutton.state);
            }
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_JOYBUTTONDOWN;
            new_event->jbutton.which = \
                    g_fs_ml_sdl_joystick_index_map[event.jbutton.which];
            new_event->jbutton.button = event.jbutton.button;
            new_event->jbutton.state = event.jbutton.state;
        }
        else if (event.type == SDL_JOYBUTTONUP) {
            if (g_fs_log_input) {
                fs_log("SDL_JOYBUTTONUP which %d button %d state %d\n",
                       event.jbutton.which, event.jbutton.button,
                       event.jbutton.state);
            }
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_JOYBUTTONUP;
            new_event->jbutton.which = \
                    g_fs_ml_sdl_joystick_index_map[event.jbutton.which];
            new_event->jbutton.button = event.jbutton.button;
            new_event->jbutton.state = event.jbutton.state;
        }
        else if (event.type == SDL_JOYAXISMOTION) {
            /* Not logging axis motion, too much noise */
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_JOYAXISMOTION;
            new_event->jaxis.which = \
                    g_fs_ml_sdl_joystick_index_map[event.jaxis.which];
            new_event->jaxis.axis = event.jaxis.axis;
            new_event->jaxis.value = event.jaxis.value;
        }
        else if (event.type == SDL_JOYHATMOTION) {
            if (g_fs_log_input) {
                fs_log("SDL_JOYHATMOTION which %d hat %d value %d\n",
                       event.jhat.which, event.jhat.hat, event.jhat.value);
            }
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_JOYHATMOTION;
            new_event->jhat.which = \
                    g_fs_ml_sdl_joystick_index_map[event.jhat.which];
            new_event->jhat.hat = event.jhat.hat;
            new_event->jhat.value = event.jhat.value;
        }
        else if (event.type == SDL_MOUSEMOTION) {
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_MOUSEMOTION;
            new_event->motion.device = g_fs_ml_first_mouse_index;
            new_event->motion.xrel = event.motion.xrel;
            new_event->motion.yrel = event.motion.yrel;
            /* Absolute window coordinates */
            new_event->motion.x = event.motion.x;
            new_event->motion.y = event.motion.y;
            //printf("ISREL %d\n", SDL_GetRelativeMouseMode());

            if (g_fs_log_input) {
                fs_log("SDL mouse event x: %4d y: %4d xrel: %4d yrel: %4d\n", 
                    event.motion.x, event.motion.y,
                    event.motion.xrel, event.motion.yrel);
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_MOUSEBUTTONDOWN;
            new_event->button.device = g_fs_ml_first_mouse_index;
            new_event->button.button = event.button.button;
#ifdef MACOSX
            if (new_event->button.button == 1) {
                int mod = SDL_GetModState();
                if (mod & KMOD_ALT) {
                    new_event->button.button = 2;
                }
                else if (mod & KMOD_CTRL) {
                    new_event->button.button = 3;
                }
            }
#endif
            new_event->button.state = event.button.state;
        }
        else if (event.type == SDL_MOUSEBUTTONUP) {
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_MOUSEBUTTONUP;
            new_event->button.device = g_fs_ml_first_mouse_index;
            new_event->button.button = event.button.button;
#ifdef MACOSX
            if (new_event->button.button == 1) {
                int mod = SDL_GetModState();
                if (mod & KMOD_ALT) {
                    new_event->button.button = 2;
                }
                else if (mod & KMOD_CTRL) {
                    new_event->button.button = 3;
                }
            }
#endif
            new_event->button.state = event.button.state;
        }
        else if (event.type == SDL_MOUSEWHEEL) {
            /*
            if (event.wheel.which == SDL_TOUCH_MOUSEID) {

            }
            */
            if (event.wheel.y) {
                if (g_fs_log_input) {
                    fs_log("SDL mouse event y-scroll: %4d\n",
                        event.wheel.y);
                }
                new_event = fs_ml_alloc_event();
                new_event->type = FS_ML_MOUSEBUTTONDOWN;
                if (event.wheel.y > 0) {
                    new_event->button.button = FS_ML_BUTTON_WHEELUP;
                }
                else {
                    new_event->button.button = FS_ML_BUTTON_WHEELDOWN;
                }
                new_event->button.device = g_fs_ml_first_mouse_index;
                new_event->button.state = 1;
            }
        }
        else if (event.type == SDL_TEXTINPUT) {
            new_event = fs_ml_alloc_event();
            new_event->type = FS_ML_TEXTINPUT;
            memcpy(&(new_event->text.text), &(event.text.text),
                   MIN(TEXTINPUTEVENT_TEXT_SIZE, SDL_TEXTINPUTEVENT_TEXT_SIZE));
            new_event->text.text[TEXTINPUTEVENT_TEXT_SIZE - 1] = 0;
        }

        if (new_event) {
            fs_ml_post_event(new_event);
        }
    }
    return result;
}