// Determine if this computer has a sound card capable of recording
JNIEXPORT jboolean 
JNICALL Java_craigl_winrecorder_WinRecorder_nativeHasSoundCard(
		JNIEnv *env, jobject o) {

	WAVEINCAPS waveInCaps;
	BOOL success;

	if (waveInGetNumDevs() == 0)
		return FALSE;

	// We have a recording device, grab its specs
	success = (waveInGetDevCaps(0, &waveInCaps, sizeof(WAVEINCAPS)) == MMSYSERR_NOERROR);

	if (success) {
#ifdef DEBUG
		// Display info
		printf("Manufacturer ID: %d\n", waveInCaps.wMid);
		printf("Product ID: %d\n", waveInCaps.wPid);
		printf("Maj Version: %d\n", waveInCaps.vDriverVersion >> 8);
		printf("Min Version: %d\n", waveInCaps.vDriverVersion & 255);
		printf("Product Name: %s\n", waveInCaps.szPname);
		printf("Formats: %x\n", waveInCaps.dwFormats);
		printf("Channels: %d\n", waveInCaps.wChannels);
#endif
		return TRUE;
	}	else
		return FALSE;