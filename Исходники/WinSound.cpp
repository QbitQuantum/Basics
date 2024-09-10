void WinSound::fillNextBuffer(void) {
	if (isStarted) {
		isFilling = TRUE;
		// check if the buffer is already prepared (should not !)
		if (waveHeader[currentBuffer].dwFlags & WHDR_PREPARED)
			waveOutUnprepareHeader(waveOut, &waveHeader[currentBuffer],
					sizeof(WAVEHDR));
		// Call the user function to fill the buffer
		if (userCallback) {
			userCallback(soundBuffer[currentBuffer], bufferSize);
		}
		// Prepare the buffer to be sent to the WaveOut API
		waveHeader[currentBuffer].lpData = (char*) soundBuffer[currentBuffer];
		waveHeader[currentBuffer].dwBufferLength = bufferSize;
		waveOutPrepareHeader(waveOut, &waveHeader[currentBuffer], sizeof(WAVEHDR));
		// Send the buffer the the WaveOut queue
		waveOutWrite(waveOut, &waveHeader[currentBuffer], sizeof(WAVEHDR));
		currentBuffer++;
		if (currentBuffer >= WINSOUND_BUFFERCOUNT) {
			currentBuffer = 0;
		}
		isFilling = FALSE;
	}
}