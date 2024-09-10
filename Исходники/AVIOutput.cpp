int AVIBegin(const char* filename, struct AVIFile* _avi_out)
{
	AVIFile& avi = *_avi_out;
	int result = 0;

	do
	{
		if(!avi.video_added)
			break;

		if(!truncate_existing(filename))
			break;

		// open the file
		if(FAILED(AVIFileOpen(&avi.avi_file, filename, OF_CREATE | OF_WRITE, NULL)))
			break;

		// create the video stream
		memset(&avi.avi_video_header, 0, sizeof(AVISTREAMINFO));
		avi.avi_video_header.fccType = streamtypeVIDEO;
		avi.avi_video_header.dwScale = ONE_DOT_CYCLE*SNES_HCOUNTER_MAX*SNES_MAX_NTSC_VCOUNTER;
		avi.avi_video_header.dwRate = (int)NTSC_MASTER_CLOCK;
		avi.avi_video_header.dwSuggestedBufferSize = avi.bitmap_format.biSizeImage;
		if(FAILED(AVIFileCreateStream(avi.avi_file, &avi.streams[VIDEO_STREAM], &avi.avi_video_header)))
			break;

		if(use_prev_options)
		{
			avi.compress_options[VIDEO_STREAM] = saved_avi_info.compress_options[VIDEO_STREAM];
			avi.compress_options_ptr[VIDEO_STREAM] = &avi.compress_options[0];
		}
		else
		{
			// get compression options
			memset(&avi.compress_options[VIDEO_STREAM], 0, sizeof(AVICOMPRESSOPTIONS));
			avi.compress_options_ptr[VIDEO_STREAM] = &avi.compress_options[0];
			if(!AVISaveOptions(GUI.hWnd, 0, 1, &avi.streams[VIDEO_STREAM], &avi.compress_options_ptr[VIDEO_STREAM]))
				break;
		}

		// create compressed stream
		if(FAILED(AVIMakeCompressedStream(&avi.compressed_streams[VIDEO_STREAM], avi.streams[VIDEO_STREAM], &avi.compress_options[VIDEO_STREAM], NULL)))
			break;

		// set the stream format
		if(FAILED(AVIStreamSetFormat(avi.compressed_streams[VIDEO_STREAM], 0, (void*)&avi.bitmap_format, avi.bitmap_format.biSize)))
			break;

		// add sound (if requested)
		if(avi.sound_added)
		{
			// create the audio stream
			memset(&avi.avi_sound_header, 0, sizeof(AVISTREAMINFO));
			avi.avi_sound_header.fccType = streamtypeAUDIO;
			avi.avi_sound_header.dwQuality = (DWORD)-1;
			avi.avi_sound_header.dwScale = avi.wave_format.nBlockAlign;
			avi.avi_sound_header.dwRate = avi.wave_format.nAvgBytesPerSec;
			avi.avi_sound_header.dwSampleSize = avi.wave_format.nBlockAlign;
			avi.avi_sound_header.dwInitialFrames = 1;
			if(FAILED(AVIFileCreateStream(avi.avi_file, &avi.streams[AUDIO_STREAM], &avi.avi_sound_header)))
				break;

			// AVISaveOptions doesn't seem to work for audio streams
			// so here we just copy the pointer for the compressed stream
			avi.compressed_streams[AUDIO_STREAM] = avi.streams[AUDIO_STREAM];

			// set the stream format
			if(FAILED(AVIStreamSetFormat(avi.compressed_streams[AUDIO_STREAM], 0, (void*)&avi.wave_format, sizeof(WAVEFORMATEX))))
				break;
		}

		// initialize counters
		avi.video_frames = 0;
		avi.sound_samples = 0;
		avi.tBytes = 0;
		avi.ByteBuffer = 0;
		avi.audio_buffer_pos = 0;

		strncpy(saved_cur_avi_fnameandext,filename,MAX_PATH);
		strncpy(saved_avi_fname,filename,MAX_PATH);
		char* dot = strrchr(saved_avi_fname, '.');
		if(dot && dot > strrchr(saved_avi_fname, '/') && dot > strrchr(saved_avi_fname, '\\'))
		{
			strcpy(saved_avi_ext,dot);
			dot[0]='\0';
		}

		// success
		result = 1;
		avi.valid = true;

	} while(false);

	if(!result)
	{
		clean_up(&avi);
		avi.valid = false;
	}

	return result;
}