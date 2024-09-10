static void *display_deltacast_init(struct module *parent, const char *fmt, unsigned int flags)
{
        UNUSED(parent);
        struct state_deltacast *s;
        ULONG             Result,DllVersion,NbBoards,ChnType;
        ULONG             BrdId = 0;

        s = (struct state_deltacast *)calloc(1, sizeof(struct state_deltacast));
        s->magic = DELTACAST_MAGIC;
        
        s->frame = vf_alloc(1);
        s->tile = vf_get_tile(s->frame, 0);
        s->frames = 0;
        
        gettimeofday(&s->tv, NULL);
        
        s->initialized = FALSE;
        if(flags & DISPLAY_FLAG_AUDIO_EMBEDDED) {
                s->play_audio = TRUE;
        } else {
                s->play_audio = FALSE;
        }
        
        s->BoardHandle = s->StreamHandle = s->SlotHandle = NULL;
        s->audio_configured = FALSE;

        if(fmt && strcmp(fmt, "help") == 0) {
                show_help();
                vf_free(s->frame);
                free(s);
                return &display_init_noerr;
        }
        
        if(fmt)
        {
                char *tmp = strdup(fmt);
                char *save_ptr = NULL;
                char *tok;
                
                tok = strtok_r(tmp, ":", &save_ptr);
                if(!tok)
                {
                        free(tmp);
                        show_help();
                        goto error;
                }
                if (strncasecmp(tok, "board=", strlen("board=")) == 0) {
                        BrdId = atoi(tok + strlen("board="));
                } else {
                        fprintf(stderr, "Unknown option: %s\n\n", tok);
                        free(tmp);
                        show_help();
                        goto error;
                }
                free(tmp);
        }

        /* Query VideoMasterHD information */
        Result = VHD_GetApiInfo(&DllVersion,&NbBoards);
        if (Result != VHDERR_NOERROR) {
                fprintf(stderr, "[DELTACAST] ERROR : Cannot query VideoMasterHD"
                                " information. Result = 0x%08X\n",
                                Result);
                goto error;
        }
        if (NbBoards == 0) {
                fprintf(stderr, "[DELTACAST] No DELTA board detected, exiting...\n");
                goto error;
        }
        
        if(BrdId >= NbBoards) {
                fprintf(stderr, "[DELTACAST] Wrong index %d. Found %d cards.\n", BrdId, NbBoards);
                goto error;
        }

        /* Open a handle on first DELTA-hd/sdi/codec board */
        Result = VHD_OpenBoardHandle(BrdId,&s->BoardHandle,NULL,0);
        if (Result != VHDERR_NOERROR)
        {
                fprintf(stderr, "[DELTACAST] ERROR : Cannot open DELTA board %u handle. Result = 0x%08X\n",BrdId,Result);
                goto error;
        }
        VHD_GetBoardProperty(s->BoardHandle, VHD_CORE_BP_TX0_TYPE, &ChnType);
        if((ChnType!=VHD_CHNTYPE_SDSDI)&&(ChnType!=VHD_CHNTYPE_HDSDI)&&(ChnType!=VHD_CHNTYPE_3GSDI)) {
                fprintf(stderr, "[DELTACAST] ERROR : The selected channel is not an SDI one\n");
                goto bad_channel;
        }
        
        /* Disable RX0-TX0 by-pass relay loopthrough */
        VHD_SetBoardProperty(s->BoardHandle,VHD_CORE_BP_BYPASS_RELAY_0,FALSE);
        
        /* Select a 1/1 clock system */
        VHD_SetBoardProperty(s->BoardHandle,VHD_SDI_BP_CLOCK_SYSTEM,VHD_CLOCKDIV_1);

        pthread_mutex_init(&s->lock, NULL);
                  
	return s;

bad_channel:
        VHD_CloseBoardHandle(s->BoardHandle);
error:
        vf_free(s->frame);
        free(s);
        return NULL;
}