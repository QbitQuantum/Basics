static bool_t getbuffer(WAVEHDR *pwh) {
	GDataBuffer *paud;

	// Get the next data block to send
	gfxSystemLock();
	paud = gaudioRecordGetFreeBlockI();
	if (!paud && !nQueuedBuffers)
		gaudioRecordDoneI();
	gfxSystemUnlock();
	if (!paud)
		return FALSE;

	// Prepare the wave header for Windows
	pwh->dwUser = (DWORD_PTR)paud;
	pwh->lpData = (LPSTR)(paud+1);			// The data is on the end of the structure
	pwh->dwBufferLength = paud->size;
	pwh->dwFlags = 0;
	if (waveInPrepareHeader(ah, pwh, sizeof(WAVEHDR))) {
		fprintf(stderr, "GAUDIO: Failed to prepare a record buffer");
		exit(-1);
	}

	// Send it to windows
	if (waveInAddBuffer(ah, pwh, sizeof(WAVEHDR))) {
		fprintf(stderr, "GAUDIO: Failed to add the record buffer");
		exit(-1);
	}

	nQueuedBuffers++;
	return TRUE;
}