void WaveIn::close()
{
	waveInReset(hWaveIn);
	
	while (!waveHeaders.IsEmpty()) {
		LPWAVEHDR pwh = (LPWAVEHDR) waveHeaders.RemoveHead();
		waveInUnprepareHeader(hWaveIn, pwh, sizeof(WAVEHDR));
		delete []pwh->lpData;
		delete pwh;
	}

	waveInClose(hWaveIn);
	hWaveIn = NULL;
}