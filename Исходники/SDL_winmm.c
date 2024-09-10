static void
WINMM_CloseDevice(_THIS)
{
    /* Close up audio */
    if (this->hidden != NULL) {
        int i;

        if (this->hidden->audio_sem) {
            CloseHandle(this->hidden->audio_sem);
            this->hidden->audio_sem = 0;
        }

        /* Clean up mixing buffers */
        for (i = 0; i < NUM_BUFFERS; ++i) {
            if (this->hidden->wavebuf[i].dwUser != 0xFFFF) {
                waveOutUnprepareHeader(this->hidden->hout,
                                       &this->hidden->wavebuf[i],
                                       sizeof(this->hidden->wavebuf[i]));
                this->hidden->wavebuf[i].dwUser = 0xFFFF;
            }
        }

        /* Free raw mixing buffer */
        SDL_free(this->hidden->mixbuf);
        this->hidden->mixbuf = NULL;

        if (this->hidden->hin) {
            waveInClose(this->hidden->hin);
            this->hidden->hin = 0;
        }

        if (this->hidden->hout) {
            waveOutClose(this->hidden->hout);
            this->hidden->hout = 0;
        }

        SDL_free(this->hidden);
        this->hidden = NULL;
    }
}