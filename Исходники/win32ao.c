/**
 * win32ao_open(int sample_rate)
 * Setup audio for output at specified rate.
 * returns -1 on error, 0 on happy.
 */
int win32ao_open(int sample_rate, float jitterBufSecs) {
	WAVEFORMATEX waveFormat;
	MMRESULT res;
	int i;

	// create an event by which audio driver will notify us
	whoutEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	// populate whoutFormat struct
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nChannels = 1;
	waveFormat.nSamplesPerSec = sample_rate;
	waveFormat.nAvgBytesPerSec = sample_rate * SAMPLE_BITS / 8;
	waveFormat.nBlockAlign = SAMPLE_BITS / 8;
	waveFormat.wBitsPerSample = SAMPLE_BITS;
	waveFormat.cbSize = 0;

	whoutBufNo = 0;
	whoutBufIndex = 0;

	// open audio device
	res = waveOutOpen(&waveout, WAVE_MAPPER, &waveFormat,
			  (DWORD) whoutEvent, (DWORD) 0, CALLBACK_EVENT);
	if (checkWaveOutResult(waveout, res, "waveOutOpen"))
		return -1;

	// pause playback (unpause when lo water mark reached)
	res = waveOutPause(waveout);
	if (checkWaveOutResult(waveout, res, "waveOutPause"))
		return -1;

	// compute whoutBufCnt
	whoutBufCnt = (int) ceil(jitterBufSecs * (float) waveFormat.nAvgBytesPerSec
					         / (float) WaveBuf_SIZE);
	if (whoutBufCnt < WaveBuf_N_MIN)
		whoutBufCnt = WaveBuf_N_MIN;

	// create buffers
	whout = (WAVEHDR**) malloc(whoutBufCnt * sizeof(WAVEHDR**));
	for (i = 0; i < whoutBufCnt; ++i) {
		// allocate buffer header
		whout[i] = (WAVEHDR*) calloc(1, sizeof(WAVEHDR));
		if (whout[i] == NULL) {
			perror("calloc WAVEHDR");
			return -1;
		}
		// allocate buffer
		whout[i]->lpData = malloc(WaveBuf_SIZE);
		if (whout[i]->lpData == NULL) {
			perror("malloc lpData");
			return -1;
		}
	}

	return 0;
}