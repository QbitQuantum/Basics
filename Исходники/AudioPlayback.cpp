DWORD AudioPlayback::QueryPosition(DWORD scope)
{
    DWORD pos = 0;
    if (hWaveOut && _sound)
    {
        MMTIME mmTime = {};
        mmTime.wType = TIME_BYTES;
        if (MMSYSERR_NOERROR == waveOutGetPosition(hWaveOut, &mmTime, sizeof(mmTime)))
        {
            pos = (scope * mmTime.u.cb / _sound->DigitalSamplePCM.size());
        }
    }
    return pos;
}