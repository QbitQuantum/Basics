void 
SDL_EVDEV_Poll(void)
{
    struct input_event events[32];
    int i, len;
    SDL_evdevlist_item *item;
    SDL_Scancode scan_code;
    int mouse_button;
    SDL_Mouse *mouse;
#ifdef SDL_INPUT_LINUXKD
    Uint16 modstate;
    struct kbentry kbe;
    static char keysym[8];
    char *end;
    Uint32 kval;
#endif

    if (!_this) {
        return;
    }

#if SDL_USE_LIBUDEV
    SDL_UDEV_Poll();
#endif

    mouse = SDL_GetMouse();

    for (item = _this->first; item != NULL; item = item->next) {
        while ((len = read(item->fd, events, (sizeof events))) > 0) {
            len /= sizeof(events[0]);
            for (i = 0; i < len; ++i) {
                switch (events[i].type) {
                case EV_KEY:
                    if (events[i].code >= BTN_MOUSE && events[i].code < BTN_MOUSE + SDL_arraysize(EVDEV_MouseButtons)) {
                        mouse_button = events[i].code - BTN_MOUSE;
                        if (events[i].value == 0) {
                            SDL_SendMouseButton(mouse->focus, mouse->mouseID, SDL_RELEASED, EVDEV_MouseButtons[mouse_button]);
                        } else if (events[i].value == 1) {
                            SDL_SendMouseButton(mouse->focus, mouse->mouseID, SDL_PRESSED, EVDEV_MouseButtons[mouse_button]);
                        }
                        break;
                    }

                    /* Probably keyboard */
                    scan_code = SDL_EVDEV_translate_keycode(events[i].code);
                    if (scan_code != SDL_SCANCODE_UNKNOWN) {
                        if (events[i].value == 0) {
                            SDL_SendKeyboardKey(SDL_RELEASED, scan_code);
                        } else if (events[i].value == 1 || events[i].value == 2 /* Key repeated */) {
                            SDL_SendKeyboardKey(SDL_PRESSED, scan_code);
#ifdef SDL_INPUT_LINUXKD
                            if (_this->console_fd >= 0) {
                                kbe.kb_index = events[i].code;
                                /* Convert the key to an UTF-8 char */
                                /* Ref: http://www.linuxjournal.com/article/2783 */
                                modstate = SDL_GetModState();
                                kbe.kb_table = 0;
                                
                                /* Ref: http://graphics.stanford.edu/~seander/bithacks.html#ConditionalSetOrClearBitsWithoutBranching */
                                kbe.kb_table |= -((modstate & KMOD_LCTRL) != 0) & (1 << KG_CTRLL | 1 << KG_CTRL);
                                kbe.kb_table |= -((modstate & KMOD_RCTRL) != 0) & (1 << KG_CTRLR | 1 << KG_CTRL);
                                kbe.kb_table |= -((modstate & KMOD_LSHIFT) != 0) & (1 << KG_SHIFTL | 1 << KG_SHIFT);
                                kbe.kb_table |= -((modstate & KMOD_RSHIFT) != 0) & (1 << KG_SHIFTR | 1 << KG_SHIFT);
                                kbe.kb_table |= -((modstate & KMOD_LALT) != 0) & (1 << KG_ALT);
                                kbe.kb_table |= -((modstate & KMOD_RALT) != 0) & (1 << KG_ALTGR);

                                if (ioctl(_this->console_fd, KDGKBENT, (unsigned long)&kbe) == 0 && 
                                    ((KTYP(kbe.kb_value) == KT_LATIN) || (KTYP(kbe.kb_value) == KT_ASCII) || (KTYP(kbe.kb_value) == KT_LETTER))) 
                                {
                                    kval = KVAL(kbe.kb_value);
                                    
                                    /* While there's a KG_CAPSSHIFT symbol, it's not useful to build the table index with it
                                     * because 1 << KG_CAPSSHIFT overflows the 8 bits of kb_table 
                                     * So, we do the CAPS LOCK logic here. Note that isalpha depends on the locale!
                                     */
                                    if (modstate & KMOD_CAPS && isalpha(kval)) {
                                        if (isupper(kval)) {
                                            kval = tolower(kval);
                                        } else {
                                            kval = toupper(kval);
                                        }
                                    }
                                     
                                    /* Convert to UTF-8 and send */
                                    end = SDL_UCS4ToUTF8(kval, keysym);
                                    *end = '\0';
                                    SDL_SendKeyboardText(keysym);
                                }
                            }
#endif /* SDL_INPUT_LINUXKD */
                        }
                    }
                    break;
                case EV_ABS:
                    switch(events[i].code) {
                    case ABS_X:
                        SDL_SendMouseMotion(mouse->focus, mouse->mouseID, SDL_FALSE, events[i].value, mouse->y);
                        break;
                    case ABS_Y:
                        SDL_SendMouseMotion(mouse->focus, mouse->mouseID, SDL_FALSE, mouse->x, events[i].value);
                        break;
                    default:
                        break;
                    }
                    break;
                case EV_REL:
                    switch(events[i].code) {
                    case REL_X:
                        SDL_SendMouseMotion(mouse->focus, mouse->mouseID, SDL_TRUE, events[i].value, 0);
                        break;
                    case REL_Y:
                        SDL_SendMouseMotion(mouse->focus, mouse->mouseID, SDL_TRUE, 0, events[i].value);
                        break;
                    case REL_WHEEL:
                        SDL_SendMouseWheel(mouse->focus, mouse->mouseID, 0, events[i].value, SDL_MOUSEWHEEL_NORMAL);
                        break;
                    case REL_HWHEEL:
                        SDL_SendMouseWheel(mouse->focus, mouse->mouseID, events[i].value, 0, SDL_MOUSEWHEEL_NORMAL);
                        break;
                    default:
                        break;
                    }
                    break;
                case EV_SYN:
                    switch (events[i].code) {
                    case SYN_DROPPED:
                        SDL_EVDEV_sync_device(item);
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
        }    
    }
}