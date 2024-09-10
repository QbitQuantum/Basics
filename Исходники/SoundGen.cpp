void SoundGen_SetSpeed(WORD speedpercent)
{
    DWORD dwRate = 0x00010000;
    if (speedpercent > 0 && speedpercent < 1000)
        dwRate = (((DWORD)speedpercent / 100) << 16) | ((speedpercent % 100) * 0x00010000 / 100);

    waveOutSetPlaybackRate(hWaveOut, dwRate);
}