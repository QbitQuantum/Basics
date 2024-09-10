int WAVBegin(const char* _filename, struct WAVFile* _wav_out)
{
	WAVFile& wav = *_wav_out;
	LPSTR filename = NULL;
	int result = 0;

	do
	{
		filename = new char[strlen(_filename)+1];
		strcpy(filename, _filename);

		// open the file
		if(!(wav.wav_file = mmioOpen(filename, NULL, MMIO_CREATE|MMIO_WRITE)))
			break;

		delete filename;

		// create WAVE chunk
		wav.waveChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioCreateChunk(wav.wav_file, &wav.waveChunk, MMIO_CREATERIFF);

		// create Format chunk
		wav.fmtChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioCreateChunk(wav.wav_file, &wav.fmtChunk, 0);
		// then write header
		memcpy(&wav.wav_format, &wav.wav_format_master, sizeof(WAVEFORMATEX));
		wav.wav_format.cbSize = 0;
		mmioWrite(wav.wav_file, (HPSTR) &wav.wav_format, sizeof(WAVEFORMATEX));
		mmioAscend(wav.wav_file, &wav.fmtChunk, 0);

		// create Data chunk
		wav.dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioCreateChunk(wav.wav_file, &wav.dataChunk, 0);

		// success
		result = 1;
		wav.valid = true;

	} while(false);

	if(!result)
	{
		clean_up(&wav);
		wav.valid = false;
	}

	return result;
}