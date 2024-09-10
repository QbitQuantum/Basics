void LongSound_concatenate (SoundAndLongSoundList me, MelderFile file, int audioFileType, int numberOfBitsPerSamplePoint) {
	try {
		long sampleRate, n;   /* Integer sampling frequencies only, because of possible rounding errors. */
		int numberOfChannels;
		if (my size < 1) Melder_throw (U"No Sound or LongSound objects to concatenate.");
		/*
		 * The sampling frequencies and numbers of channels must be equal for all (long)sounds.
		 */
		Sampled data = my at [1];
		if (data -> classInfo == classSound) {
			Sound sound = (Sound) data;
			sampleRate = lround (1.0 / sound -> dx);
			numberOfChannels = sound -> ny;
			n = sound -> nx;
		} else {
			LongSound longSound = (LongSound) data;
			sampleRate = longSound -> sampleRate;
			numberOfChannels = longSound -> numberOfChannels;
			n = longSound -> nx;
		}
		/*
		 * Check whether all the sampling frequencies and channels match.
		 */
		for (long i = 2; i <= my size; i ++) {
			int sampleRatesMatch, numbersOfChannelsMatch;
			data = my at [i];
			if (data -> classInfo == classSound) {
				Sound sound = (Sound) data;
				sampleRatesMatch = round (1.0 / sound -> dx) == sampleRate;
				numbersOfChannelsMatch = sound -> ny == numberOfChannels;
				n += sound -> nx;
			} else {
				LongSound longSound = (LongSound) data;
				sampleRatesMatch = longSound -> sampleRate == sampleRate;
				numbersOfChannelsMatch = longSound -> numberOfChannels == numberOfChannels;
				n += longSound -> nx;
			}
			if (! sampleRatesMatch)
				Melder_throw (U"Sampling frequencies are not equal.");
			if (! numbersOfChannelsMatch)
				Melder_throw (U"Cannot mix stereo and mono.");
		}
		/*
		 * Create output file and write header.
		 */
		autoMelderFile mfile = MelderFile_create (file);
		if (file -> filePointer) {
			MelderFile_writeAudioFileHeader (file, audioFileType, sampleRate, n, numberOfChannels, numberOfBitsPerSamplePoint);
		}
		for (long i = 1; i <= my size; i ++) {
			data = my at [i];
			if (data -> classInfo == classSound) {
				Sound sound = (Sound) data;
				if (file -> filePointer) {
					MelderFile_writeFloatToAudio (file, sound -> ny, Melder_defaultAudioFileEncoding (audioFileType, numberOfBitsPerSamplePoint),
						sound -> z, sound -> nx, true);
				}
			} else {
				LongSound longSound = (LongSound) data;
				writePartToOpenFile (longSound, audioFileType, 1, longSound -> nx, file, 0, numberOfBitsPerSamplePoint);
			}
		}
		MelderFile_writeAudioFileTrailer (file, audioFileType, sampleRate, n, numberOfChannels, numberOfBitsPerSamplePoint);
		mfile.close ();
	} catch (MelderError) {
		Melder_throw (U"Sounds not concatenated and not saved to ", file, U".");
	}
}