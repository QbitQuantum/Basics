void closeWaveDevice()
{
    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
}