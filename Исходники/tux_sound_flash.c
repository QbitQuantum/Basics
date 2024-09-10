static bool
get_default_playback_idx(int *idx)
{
    int err;
    DWORD po = -1;
    DWORD pf = 0;

    err = waveOutMessage((HWAVEOUT)WAVE_MAPPER, DRVM_MAPPER_PREFERRED_GET,
            (DWORD)&po, (DWORD)&pf);
    if (err == 0)
    {
        *idx = po;
        return true;
    }

    return true;
}