int pcmwav_open(TCHAR *fname, DWORD access, pcmwavfile *opwf) {

	RIFFhdr		rhdr;
	fmt_sub		fmt;
	DWORD		nread;
	char		have_fmt = 0;
	unsigned long	subchunk, subchunk_size;

	opwf->winfile = CreateFile(fname, access, 0, NULL,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (opwf->winfile == INVALID_HANDLE_VALUE) {
		swprintf(pcmwav_error, _T("Cannot open file %s.\n"), fname);
		return 0;
	}

	// Read RIFF header
	ReadFile(opwf->winfile, &rhdr, sizeof(rhdr), &nread, NULL);

	// Check it
	if ((rhdr.ChunkID != 0x46464952 /* 'RIFF' */) || (rhdr.Format != 0x45564157 /* 'WAVE' */)) {
		swprintf(pcmwav_error, _T("This is not a PCM WAV file.\n"));
		CloseHandle(opwf->winfile);
		return 0;
	}

	/* read subchunks until we encounter 'data' */
	do {
		// Read subchunk ID
		if (!ReadFile(opwf->winfile, &subchunk, sizeof(subchunk), &nread, NULL)) {
			swprintf(pcmwav_error, _T("Read error: this is not a correct PCM WAV file.\n"));
			CloseHandle(opwf->winfile);
			return 0;
		}

		if (subchunk == 0x20746D66 /* 'fmt ' */) {
			// Read subchunk 1
			ReadFile(opwf->winfile, &fmt, sizeof(fmt), &nread, NULL);

			// Check it
			if (fmt.AudioFormat != 1) {
				swprintf(pcmwav_error, _T("Error in format subchunk: this is not a PCM WAV file.\n"));
				CloseHandle(opwf->winfile);
				return 0;
			}

			opwf->bitspersample = fmt.BitsPerSample;

			if ((opwf->bitspersample != 8) && (opwf->bitspersample != 16)) {
				swprintf(pcmwav_error, _T("Can only deal with 8-bit or 16-bit samples.\n"));
				CloseHandle(opwf->winfile);
				return 0;
			}

			// Skip any extra header bytes
			if (fmt.Subchunk1Size - 16)
				SetFilePointer(opwf->winfile, fmt.Subchunk1Size - 16, NULL, FILE_CURRENT);
			
			have_fmt = 1;
		} else if (subchunk != 0x61746164 /* 'data' */) {
			// unknown subchunk - read size and skip
			ReadFile(opwf->winfile, &subchunk_size, sizeof(subchunk_size), &nread, NULL);
			SetFilePointer(opwf->winfile, subchunk_size, NULL, FILE_CURRENT);
		}

	} while (subchunk != 0x61746164 /* 'data' */);

	if (!have_fmt) {
		swprintf(pcmwav_error, _T("Encountered data subchunk, but no format subchunk found.\n"));
		CloseHandle(opwf->winfile);
		return 0;
	}

	/* read data chunk size */
	ReadFile(opwf->winfile, &opwf->ndatabytes, sizeof(opwf->ndatabytes), &nread, NULL);

	opwf->samplerate = fmt.SampleRate;
	opwf->nchannels = fmt.NumChannels;
	opwf->datapos = SetFilePointer(opwf->winfile, 0, NULL, FILE_CURRENT);
	
	return 1;
}