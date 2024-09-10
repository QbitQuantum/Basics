int audio_close(snd_type snd)
{
    int i;
    MMRESULT er;
    buffer_state *bs = (buffer_state *) snd->u.audio.descriptor;
    if (snd->write_flag == SND_READ) {
        if (er = waveInReset(bs->u.h_in)) {
            mm_error_handler(snd, er, snd_fail);
            return !SND_SUCCESS;
        }
        if (er = waveInClose(bs->u.h_in)) {
            mm_error_handler(snd, er, snd_fail);
            return !SND_SUCCESS;
        }
    } else { // SND_WRITE
        if (er = waveOutReset(bs->u.h_out)) {
            mm_error_handler(snd, er, snd_fail);
            return !SND_SUCCESS;
        }
        if (er = waveOutClose(bs->u.h_out)) {
            mm_error_handler(snd, er, snd_fail);
            return !SND_SUCCESS;
        }
    }
    for (i = 0; i < bs->numofbuffers; i++) {
        snd_free(bs->whdr[i].lpData);
    }
    snd_free(bs->whdr);
    snd_free(bs);
    if (rt_devices_open) {
        timeEndPeriod(1);
        rt_devices_open--;
    }
    return SND_SUCCESS;
}