void InternalPlayer::writeAudio(int16_t *samples, int sampleCount) {

		WAVEHDR &h = header[blockPosition];
		h.dwBufferLength = sampleCount * 2;
		memcpy(h.lpData, samples, sampleCount * 2);

		if(h.dwFlags & WHDR_PREPARED) 
			waveOutUnprepareHeader(hWaveOut, &h, sizeof(WAVEHDR));

		waveOutPrepareHeader(hWaveOut, &h, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &h, sizeof(WAVEHDR));

		lock.lock();
		blockCounter++;
		lock.unlock();

		blockPosition++;
		blockPosition = (blockPosition % bufCount);

		while(true) {
			lock.lock();
			int bc = blockCounter;
			lock.unlock();
			if(bc < bufCount)
				break;
			Sleep(100);
		}
	}