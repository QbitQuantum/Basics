static void
MME_CloseDevice(_THIS)
{
    if (this->hidden != NULL) {
        MMRESULT result;

        if (this->hidden->mixbuf) {
            result = mmeFreeBuffer(this->hidden->mixbuf);
            if (result != MMSYSERR_NOERROR)
                SetMMerror("mmeFreeBuffer", result);
            this->hidden->mixbuf = NULL;
        }

        if (this->hidden->shm) {
            if (this->hidden->shm->sound) {
                result = waveOutClose(this->hidden->shm->sound);
                if (result != MMSYSERR_NOERROR)
                    SetMMerror("waveOutClose()", result);
                mmeProcessCallbacks();
            }
            result = mmeFreeMem(this->hidden->shm);
            if (result != MMSYSERR_NOERROR)
                SetMMerror("mmeFreeMem()", result);
            this->hidden->shm = NULL;
        }

        SDL_free(this->hidden);
        this->hidden = NULL;
    }
}