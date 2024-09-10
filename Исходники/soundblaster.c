static BOOL SB_Init(void)
{
    HRESULT result;

    if (!lpdsound) {
        result = DirectSoundCreate(NULL,&lpdsound,NULL);
        if (result != DS_OK) {
            ERR("Unable to initialize Sound Subsystem err = %x !\n",result);
            return FALSE;
        }

        /* FIXME: To uncomment when :
           - SetCooperative level is correctly implemented
           - an always valid and non changing handle to a windows  (vga_hwnd) is available
             (this surely needs some work in vga.c)
        result = IDirectSound_SetCooperativeLevel(lpdsound,vga_hwnd,DSSCL_EXCLUSIVE|DSSCL_PRIORITY);
        if (result != DS_OK) {
            ERR("Can't set cooperative level !\n");
            return FALSE;
        }
        */

        /* Default format */
        wav_fmt.wFormatTag = WAVE_FORMAT_PCM;
        wav_fmt.nChannels = 1;
        wav_fmt.nSamplesPerSec = 22050;
        wav_fmt.nAvgBytesPerSec = 22050;
        wav_fmt.nBlockAlign = 1;
        wav_fmt.wBitsPerSample = 8;
        wav_fmt.cbSize = 0;

        memset(&buf_desc,0,sizeof(DSBUFFERDESC));
        buf_desc.dwSize = sizeof(DSBUFFERDESC);
        buf_desc.dwBufferBytes = DSBUFLEN;
        buf_desc.lpwfxFormat = &wav_fmt;
        result = IDirectSound_CreateSoundBuffer(lpdsound,&buf_desc,&lpdsbuf,NULL);
        if (result != DS_OK) {
            ERR("Can't create sound buffer !\n");
            return FALSE;
        }

        result = IDirectSoundBuffer_Play(lpdsbuf,0, 0, DSBPLAY_LOOPING);
        if (result != DS_OK) {
            ERR("Can't start playing !\n");
            return FALSE;
        }

        buf_off = 0;
        end_sound_loop = 0;
        SB_Thread = CreateThread(NULL, 0, SB_Poll, NULL, 0, NULL);
        TRACE("thread\n");
        if (!SB_Thread) {
            ERR("Can't create thread !\n");
            return FALSE;
        }
    }
    return TRUE;
}