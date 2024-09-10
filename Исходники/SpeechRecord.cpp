// Stop recording speech
int StopRecord(HWAVEIN* hWaveIn, MMTIME* mmTime)
{
	int res;

	res = waveInGetPosition(*hWaveIn, mmTime, sizeof(MMTIME));
	if(res != MMSYSERR_NOERROR)
	{
		_debug_print("Get Position of wave in FAILED!",1);
		return -1;
	}
	else
	{
		_debug_print("Get Position of wave in SUCCEED!");
	}

	res = waveInStop(*hWaveIn);
	if(res != MMSYSERR_NOERROR)
	{
		_debug_print("Stop recording FAILED!",1);
		return -1;
	}
	else
	{
		_debug_print("Stop recording SUCCEED!");
	}

	res = waveInReset(*hWaveIn);
	if(res != MMSYSERR_NOERROR)
	{
		_debug_print("Reset wave in memory FAILED!",1);
		return -1;
	}
	else
	{
		_debug_print("Reset wave in memory SUCCEED!");
	}

	return 0;
}