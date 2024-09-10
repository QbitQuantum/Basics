uint8_t win32AudioDevice::stop(void) 
{
	if (!_inUse)
		return 0;

	printf("[Win32] Closing audio\n");

	waveOutReset(myDevice);		

	for (uint32_t i = 0; i < NB_BUCKET; i++)
		waveOutUnprepareHeader(myDevice, &waveHdr[i], sizeof(WAVEHDR));

	myError = waveOutClose(myDevice);

	if (myError != MMSYSERR_NOERROR)
	{
		printf("[Win32] Close failed %d\n", myError);
		handleMM(myError);
		return 0;
	}

	for (uint32_t i = 0; i < NB_BUCKET; i++)
		delete[] waveHdr[i].lpData;

	_inUse=0;
	myDevice = NULL;

	return 1;
}