static void do_read(struct userdata *u) {
    uint32_t free_frags;
    pa_memchunk memchunk;
    WAVEHDR *hdr;
    MMRESULT res;
    void *p;

    if (!u->source)
        return;

    if (!PA_SOURCE_IS_LINKED(u->source->state))
        return;

    EnterCriticalSection(&u->crit);
    free_frags = u->free_ifrags;
    u->free_ifrags = 0;
    LeaveCriticalSection(&u->crit);

    if (free_frags == u->fragments)
        pa_log_debug("WaveIn overflow!");

    while (free_frags) {
        hdr = &u->ihdrs[u->cur_ihdr];
        if (hdr->dwFlags & WHDR_PREPARED)
            waveInUnprepareHeader(u->hwi, hdr, sizeof(WAVEHDR));

        if (hdr->dwBytesRecorded) {
            memchunk.memblock = pa_memblock_new(u->core->mempool, hdr->dwBytesRecorded);
            pa_assert(memchunk.memblock);

            p = pa_memblock_acquire(memchunk.memblock);
            memcpy((char*) p, hdr->lpData, hdr->dwBytesRecorded);
            pa_memblock_release(memchunk.memblock);

            memchunk.length = hdr->dwBytesRecorded;
            memchunk.index = 0;

            pa_source_post(u->source, &memchunk);
            pa_memblock_unref(memchunk.memblock);
        }

        res = waveInPrepareHeader(u->hwi, hdr, sizeof(WAVEHDR));
        if (res != MMSYSERR_NOERROR)
            pa_log_error("Unable to prepare waveIn block: %d", res);

        res = waveInAddBuffer(u->hwi, hdr, sizeof(WAVEHDR));
        if (res != MMSYSERR_NOERROR)
            pa_log_error("Unable to add waveIn block: %d", res);

        free_frags--;
        u->cur_ihdr++;
        u->cur_ihdr %= u->fragments;
    }
}