void QuickTimeDecoder::init() {
	// Remove non-Video/Audio streams
	for (uint32 i = 0; i < _numStreams;) {
		if (_streams[i]->codec_type == CODEC_TYPE_MOV_OTHER) {
			delete _streams[i];
			for (uint32 j = i + 1; j < _numStreams; j++)
				_streams[j - 1] = _streams[j];
			_numStreams--;
		} else
			i++;
	}

	// Adjust time/duration
	for (uint32 i = 0; i < _numStreams; i++) {
		MOVStreamContext *sc = _streams[i];

		if (!sc->time_rate)
			sc->time_rate = 1;

		if (!sc->time_scale)
			sc->time_scale = _timeScale;

		sc->duration /= sc->time_rate;

		if (sc->codec_type == CODEC_TYPE_VIDEO && _videoStreamIndex < 0)
			_videoStreamIndex = i;
		else if (sc->codec_type == CODEC_TYPE_AUDIO && _audioStreamIndex < 0)
			_audioStreamIndex = i;
	}

	// Initialize audio, if present
	if (_audioStreamIndex >= 0) {
		STSDEntry *entry = &_streams[_audioStreamIndex]->stsdEntries[0];

		if (checkAudioCodecSupport(entry->codecTag)) {
			_audStream = Audio::makeQueuingAudioStream(entry->sampleRate, entry->channels == 2);
			_curAudioChunk = 0;

			// Make sure the bits per sample transfers to the sample size
			if (entry->codecTag == MKID_BE('raw ') || entry->codecTag == MKID_BE('twos'))
				_streams[_audioStreamIndex]->sample_size = (entry->bitsPerSample / 8) * entry->channels;

			startAudio();
		}

		_audioStartOffset = Audio::Timestamp(0);
	}

	// Initialize video, if present
	if (_videoStreamIndex >= 0) {
		for (uint32 i = 0; i < _streams[_videoStreamIndex]->stsdEntryCount; i++) {
			STSDEntry *entry = &_streams[_videoStreamIndex]->stsdEntries[i];
			entry->videoCodec = createCodec(entry->codecTag, entry->bitsPerSample & 0x1F);
		}

		if (getScaleFactorX() != 1 || getScaleFactorY() != 1) {
			// We have to initialize the scaled surface
			_scaledSurface = new Graphics::Surface();
			_scaledSurface->create(getWidth(), getHeight(), getPixelFormat().bytesPerPixel);
		}
	}
}