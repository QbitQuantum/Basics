int audio_write_wince(cst_audiodev *ad, void *samples, int num_bytes)
{
    au_wince_pdata *pd = ad->platform_data;
    WAVEHDR *hdr;
    MMRESULT err;

    if (num_bytes == 0)
        return 0;

    hdr = cst_alloc(WAVEHDR,1);
    hdr->lpData = cst_alloc(char,num_bytes);
    memcpy(hdr->lpData,samples,num_bytes);
    hdr->dwBufferLength = num_bytes;

    err = waveOutPrepareHeader(pd->wo, hdr, sizeof(*hdr));
    if (err != MMSYSERR_NOERROR)
    {
        cst_errmsg("Failed to prepare header %p: %x\n", hdr, err);
        cst_error();
    }

    if (InterlockedIncrement(&pd->bcnt) == 8)
        WaitForSingleObject(pd->wevt, INFINITE);
    err = waveOutWrite(pd->wo, hdr, sizeof(*hdr));
    if (err != MMSYSERR_NOERROR)
    {
        cst_errmsg("Failed to write header %p: %x\n", hdr, err);
        cst_error();
    }
    return num_bytes;
}