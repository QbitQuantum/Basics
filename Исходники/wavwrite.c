wav_file *wav_open(const char *filename, int sample_rate, int channels)
{
	wav_file *wav;
	UINT32 bps, temp32;
	UINT16 align, temp16;

	/* allocate memory for the wav struct */
	wav = (wav_file *) malloc(sizeof(struct _wav_file));
	if (!wav)
		return NULL;

	/* create the file */
	wav->file = fopen(filename, "wb");
	if (!wav->file)
	{
		free(wav);
		return NULL;
	}

	/* write the 'RIFF' header */
	fwrite("RIFF", 1, 4, wav->file);

	/* write the total size */
	temp32 = 0;
	wav->total_offs = ftell(wav->file);
	fwrite(&temp32, 1, 4, wav->file);

	/* write the 'WAVE' type */
	fwrite("WAVE", 1, 4, wav->file);

	/* write the 'fmt ' tag */
	fwrite("fmt ", 1, 4, wav->file);

	/* write the format length */
	temp32 = intel_long(16);
	fwrite(&temp32, 1, 4, wav->file);

	/* write the format (PCM) */
	temp16 = intel_short(1);
	fwrite(&temp16, 1, 2, wav->file);

	/* write the channels */
	temp16 = intel_short(channels);
	fwrite(&temp16, 1, 2, wav->file);

	/* write the sample rate */
	temp32 = intel_long(sample_rate);
	fwrite(&temp32, 1, 4, wav->file);

	/* write the bytes/second */
	bps = sample_rate * 2 * channels;
	temp32 = intel_long(bps);
	fwrite(&temp32, 1, 4, wav->file);

	/* write the block align */
	align = 2 * channels;
	temp16 = intel_short(align);
	fwrite(&temp16, 1, 2, wav->file);

	/* write the bits/sample */
	temp16 = intel_short(16);
	fwrite(&temp16, 1, 2, wav->file);

	/* write the 'data' tag */
	fwrite("data", 1, 4, wav->file);

	/* write the data length */
	temp32 = 0;
	wav->data_offs = ftell(wav->file);
	fwrite(&temp32, 1, 4, wav->file);

	return wav;
}