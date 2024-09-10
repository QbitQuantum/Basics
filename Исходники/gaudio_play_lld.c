static DWORD WINAPI waveProc(LPVOID arg) {
	MSG			msg;
	WAVEHDR		*pwh;
	(void)		arg;

	while (GetMessage(&msg, 0, 0, 0)) {
		switch (msg.message) {
			case MM_WOM_DONE:
				pwh = (WAVEHDR *)msg.lParam;

				// Windows - Let go!
				waveOutUnprepareHeader(ah, pwh, sizeof(WAVEHDR));

				// Give the buffer back to the Audio Free List
				gfxSystemLock();
				gaudioPlayReleaseDataBlockI((GDataBuffer *)pwh->dwUser);
				gfxSystemUnlock();
				pwh->lpData = 0;
				nQueuedBuffers--;

				// Are we stopping?
				if (!isRunning) {
					// Have we finished yet?
					if (!nQueuedBuffers) {
						gfxSystemLock();
						gaudioPlayDoneI();
						gfxSystemUnlock();
					}
	                break;
				}

				// Try and get a new block
				senddata(pwh);
				break;
		}
	}
	return 0;
}