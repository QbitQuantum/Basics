int32
ad_stop_rec(ad_rec_t * r)
{
    int32 i, st;

    if ((!r->opened) || (!r->recording))
        return -1;

    if (waveInStop(r->h_wavein) != 0)
        return AD_ERR_WAVE;

    if ((st = waveInReset(r->h_wavein)) != 0) {
        wavein_error("waveInReset", st);
        return AD_ERR_WAVE;
    }

    /* Wait until all buffers marked done */
    for (i = 0; i < r->n_buf; i++)
        while (!(r->wi_buf[i].p_whdr->dwFlags & WHDR_DONE));

    if ((r->lastbuf = r->curbuf - 1) < 0)
        r->lastbuf = r->n_buf - 1;

    r->recording = 0;

    return 0;
}