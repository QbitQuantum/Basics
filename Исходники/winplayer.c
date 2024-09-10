// nativeStoreSamples - stores Java samples into a wave buffer for playback
JNIEXPORT void 
JNICALL Java_craigl_winplayer_WinPlayer_nativeStoreSamples(
	JNIEnv *env, jclass jc, jshortArray buffer, jint length) {
	
	static AudioSample *pSamples = NULL;
	WAVEHDR *pWaveHdr;

	// No more data to process ?
	if (length == -1) {
		// Release the array
		(*env)->ReleaseShortArrayElements(env, buffer, pSamples, 0);
		pSamples = NULL;
		return;
	}
	
	// pSamples points at the Java samples
	pSamples = (AudioSample *)(*env)->GetShortArrayElements(env, buffer, 0);
		
	// pWaveHdr points at the buffer to use
	pWaveHdr = &waveHdr[currentBufferIndex];

	// Set amount of data to process
	pWaveHdr->dwBufferLength = length * 2;

	// Copy the samples from array into wave buffer
	memcpy((byte *) pWaveHdr->lpData, (byte *) pSamples, length * 2);

	// Write the wave data to the output device
	waveOutWrite(hDevice, pWaveHdr, sizeof(WAVEHDR));

	// Update buffer index
	currentBufferIndex = (currentBufferIndex + 1) % NUMBEROFBUFFERS;
}