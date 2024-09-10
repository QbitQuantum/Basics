static int get_key(AIN_DeviceID ID, int *keycode, int *offset)
{
    static char *window_text;
    struct Window *window;
    AIN_InputEvent *event;
    int done = 0;

    window_text = translate_text(IDS_PRESS_KEY_BUTTON);
    *keycode = *offset = -1; /* no key */

    if (ID != -1) {
        ai_handle[0] = AIN_ObtainDevice(CTX, ID);
        if (ai_handle[0] != NULL) {
            AIN_SetDeviceParameter(CTX, ai_handle[0], AINDP_EVENT, TRUE);
        }
    }

    window = OpenWindowTags(NULL,
                            WA_Title, (ULONG)"",
                            WA_Flags, WFLG_NOCAREREFRESH|WFLG_DRAGBAR|WFLG_DEPTHGADGET|WFLG_CLOSEGADGET|WFLG_RMBTRAP|WFLG_GIMMEZEROZERO,
                            WA_IDCMP, IDCMP_CLOSEWINDOW|WFLG_REPORTMOUSE|IDCMP_RAWKEY|IDCMP_CHANGEWINDOW,
                            WA_Left, 100,
                            WA_Top, 100,
                            WA_Width, 100,
                            WA_Height, 40,
                            WA_Activate, TRUE,
                            TAG_DONE);

    if (window != NULL) {
        struct IntuiMessage *imsg = NULL;
        ULONG imCode, imClass;

        /* Resize window and set pens */
        int length = TextLength(window->RPort, window_text, strlen(window_text));

        ChangeWindowBox(window, 100, 100, window->BorderLeft+length+window->BorderRight+8, window->BorderTop+window->IFont->tf_YSize*2+window->BorderBottom);
        SetAPen(window->RPort, 1);
        SetBPen(window->RPort, 0);

        /* Wait until window has been resized */
        while (done == 0) {
            /* Wait for messages */
            Wait((1L << window->UserPort->mp_SigBit) | (1L << ai_port->mp_SigBit));

            /* Check for IDCMP messages */
            while ((imsg = (struct IntuiMessage *)GetMsg(window->UserPort))) {
                imClass = imsg->Class;
                imCode = imsg->Code;

                ReplyMsg((struct Message *)imsg);

                if (imClass == IDCMP_CHANGEWINDOW) {
                    Move(window->RPort, 4, window->IFont->tf_YSize);
                    Text(window->RPort, window_text, strlen(window_text));
                } else if (imClass == IDCMP_RAWKEY) {
                    imCode &= 0x7f;
                    if (imCode != 69) {
                        *keycode = imCode;
                    }
                    done = 1; /* KEY ok */
                } else if (imClass == IDCMP_CLOSEWINDOW) {
                    done = -1; /* cancel */
                }
            }

            /* Check for AI messages */
            if (ai_handle[0] != NULL) {
                while ((event = AIN_GetEvent(CTX))) {
                    switch(event->Type) {
                        case AINET_AXIS:
                            if ((event->Value >= (ONOFF_VALUE)) || (event->Value <= (-(ONOFF_VALUE)))) {
                                *offset = event->Index;
                                done = 2; /* AI ok */
                            }
                            break;
                        case AINET_BUTTON:
                            *offset = event->Index;
                            done = 2; /* AI ok */
                            break;
                        case AINET_HAT:
                            *offset = event->Index;
                            done = 2; /* AI ok */
                            break;
                        default:
                            break;
                    }

                    AIN_FreeEvent(CTX, event);
                }
            }
        }
        CloseWindow(window);
    }

    if (ai_handle[0] != NULL) {
        AIN_SetDeviceParameter(CTX, ai_handle[0], AINDP_EVENT, FALSE);
        /* Remove pending AI messages */
        while ((event = AIN_GetEvent(CTX))) {
            AIN_FreeEvent(CTX, event);
        }
        AIN_ReleaseDevice(CTX, ai_handle[0]);
        ai_handle[0] = NULL;
    }

    return done;
}