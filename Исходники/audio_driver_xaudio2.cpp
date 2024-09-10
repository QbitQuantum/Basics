Error AudioDriverXAudio2::init() {

	active = false;
	thread_exited = false;
	exit_thread = false;
	pcm_open = false;
	samples_in = NULL;

	mix_rate = 48000;
	// FIXME: speaker_mode seems unused in the Xaudio2 driver so far
	speaker_mode = SPEAKER_MODE_STEREO;
	channels = 2;

	int latency = GLOBAL_DEF("audio/output_latency", 25);
	buffer_size = closest_power_of_2(latency * mix_rate / 1000);

	samples_in = memnew_arr(int32_t, buffer_size * channels);
	for (int i = 0; i < AUDIO_BUFFERS; i++) {
		samples_out[i] = memnew_arr(int16_t, buffer_size * channels);
		xaudio_buffer[i].AudioBytes = buffer_size * channels * sizeof(int16_t);
		xaudio_buffer[i].pAudioData = (const BYTE *)(samples_out[i]);
		xaudio_buffer[i].Flags = 0;
	}

	HRESULT hr;
	hr = XAudio2Create(&xaudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (hr != S_OK) {
		ERR_EXPLAIN("Error creating XAudio2 engine.");
		ERR_FAIL_V(ERR_UNAVAILABLE);
	}
	hr = xaudio->CreateMasteringVoice(&mastering_voice);
	if (hr != S_OK) {
		ERR_EXPLAIN("Error creating XAudio2 mastering voice.");
		ERR_FAIL_V(ERR_UNAVAILABLE);
	}

	wave_format.nChannels = channels;
	wave_format.cbSize = 0;
	wave_format.nSamplesPerSec = mix_rate;
	wave_format.wFormatTag = WAVE_FORMAT_PCM;
	wave_format.wBitsPerSample = 16;
	wave_format.nBlockAlign = channels * wave_format.wBitsPerSample >> 3;
	wave_format.nAvgBytesPerSec = mix_rate * wave_format.nBlockAlign;

	hr = xaudio->CreateSourceVoice(&source_voice, &wave_format, 0, XAUDIO2_MAX_FREQ_RATIO, &voice_callback);
	if (hr != S_OK) {
		ERR_EXPLAIN("Error creating XAudio2 source voice. " + itos(hr));
		ERR_FAIL_V(ERR_UNAVAILABLE);
	}

	mutex = Mutex::create();
	thread = Thread::create(AudioDriverXAudio2::thread_func, this);

	return OK;
};