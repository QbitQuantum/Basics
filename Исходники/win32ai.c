/**
 * win32ai_close()
 * Terminate recording.
 * This function discards all data that has been sampled but not read.
 * Return 0 if happy, -1 if error.
 */
int win32ai_close(void) {
	MMRESULT res;
	int i;

	// stop device
	res = waveInReset(wavein);
	if (checkWaveInResult(wavein, res, "waveInReset"))
		return -1;

	// wait for buffers to finish and unprepare them all
	for (i = 0; i < WaveBuf_N; ++i) {
		while ((whin[i]->dwFlags & WHDR_DONE) == 0) {
			// buffer not ready, wait, try again
			WaitForSingleObject(whinEvent, INFINITE);
		}
		// unprepare the buffer
		res = waveInUnprepareHeader(wavein, whin[i], sizeof(WAVEHDR));
		if (checkWaveInResult(wavein, res, "waveInUnprepareHeader"))
			return -1;
		// free memory
		free(whin[i]->lpData);
		free(whin[i]);
	}

	// close device
	res = waveInClose(wavein);
	if (checkWaveInResult(wavein, res, "waveInClose"))
		return -1;
			
	return 0;
}