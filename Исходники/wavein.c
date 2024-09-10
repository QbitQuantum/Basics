void WaveInStart(WaveIn *waveIn, BOOL prep)
{
    MMRESULT res;

    res = waveInReset(waveIn->handler);
    if(res) {
        return;
    }

    // prepare header an add the buffer
    waveIn->header.lpData = (char *) waveIn->data;
    waveIn->header.dwBufferLength = waveIn->n * 2;
    waveIn->header.dwBytesRecorded = 0;
    waveIn->header.dwFlags = 0L;
    waveIn->header.dwLoops = 0L;
    waveIn->header.dwUser = 0L;
    waveInPrepareHeader(waveIn->handler, &waveIn->header, sizeof(WAVEHDR));

    res = waveInAddBuffer(waveIn->handler, &waveIn->header, sizeof(WAVEHDR));
    if(res) {
        return;
    }

    res = waveInStart(waveIn->handler);
    if(res) {
        return;
    }
}