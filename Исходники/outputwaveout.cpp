VolumeSettings VolumeWaveOut::volume() const
{
    VolumeSettings vol;
    DWORD data;
    waveOutGetVolume(0, (PDWORD)&data);
    vol.left = (long)LOWORD(data) * 100 / 0xFFFF + 1;
    vol.right = (long)HIWORD(data) * 100 / 0xFFFF + 1;
    return vol;
}