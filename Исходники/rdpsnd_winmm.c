static BOOL rdpsnd_winmm_set_volume(rdpsndDevicePlugin* device, UINT32 value)
{
	rdpsndWinmmPlugin* winmm = (rdpsndWinmmPlugin*) device;

	winmm->volume = value;

	if (!winmm->hWaveOut)
		return TRUE;

	return (waveOutSetVolume(winmm->hWaveOut, value) == MMSYSERR_NOERROR);
}