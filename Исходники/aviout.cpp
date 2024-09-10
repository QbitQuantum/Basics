static int avi_open(const char* filename, const BITMAPINFOHEADER* pbmih, const WAVEFORMATEX* pwfex)
{
	int error = 1;
	int result = 0;

	do
	{
		// close existing first
		DRV_AviEnd();

		if(!truncate_existing(filename))
			break;

		if(!pbmih)
			break;

		// create the object
		avi_create(&avi_file);

		// set video size and framerate
		/*avi_file->start_scanline = vsi->start_scanline;
		avi_file->end_scanline = vsi->end_scanline;
		avi_file->fps = vsi->fps;
		avi_file->fps_scale = 16777216-1;
		avi_file->convert_buffer = new u8[256*384*3];*/

		// open the file
		if(FAILED(AVIFileOpen(&avi_file->avi_file, filename, OF_CREATE | OF_WRITE, NULL)))
			break;

		// create the video stream
		set_video_format(pbmih, avi_file);

		memset(&avi_file->avi_video_header, 0, sizeof(AVISTREAMINFO));
		avi_file->avi_video_header.fccType = streamtypeVIDEO;
		avi_file->avi_video_header.dwScale = 6*355*263;
		avi_file->avi_video_header.dwRate = 33513982;
		avi_file->avi_video_header.dwSuggestedBufferSize = avi_file->bitmap_format.biSizeImage;
		if(FAILED(AVIFileCreateStream(avi_file->avi_file, &avi_file->streams[VIDEO_STREAM], &avi_file->avi_video_header)))
			break;

		if(use_prev_options)
		{
			avi_file->compress_options[VIDEO_STREAM] = saved_avi_info.compress_options[VIDEO_STREAM];
			avi_file->compress_options_ptr[VIDEO_STREAM] = &avi_file->compress_options[0];
		}
		else
		{
			// get compression options
			memset(&avi_file->compress_options[VIDEO_STREAM], 0, sizeof(AVICOMPRESSOPTIONS));
			avi_file->compress_options_ptr[VIDEO_STREAM] = &avi_file->compress_options[0];
//retryAviSaveOptions: //mbg merge 7/17/06 removed
			error = 0;
			if(!AVISaveOptions(MainWindow->getHWnd(), 0, 1, &avi_file->streams[VIDEO_STREAM], &avi_file->compress_options_ptr[VIDEO_STREAM]))
				break;
			error = 1;
		}

		// create compressed stream
		if(FAILED(AVIMakeCompressedStream(&avi_file->compressed_streams[VIDEO_STREAM], avi_file->streams[VIDEO_STREAM], &avi_file->compress_options[VIDEO_STREAM], NULL)))
			break;

		// set the stream format
		if(FAILED(AVIStreamSetFormat(avi_file->compressed_streams[VIDEO_STREAM], 0, (void*)&avi_file->bitmap_format, avi_file->bitmap_format.biSize)))
			break;

		// add sound (if requested)
		if(pwfex)
		{
			// add audio format
			set_sound_format(pwfex, avi_file);

			// create the audio stream
			memset(&avi_file->avi_sound_header, 0, sizeof(AVISTREAMINFO));
			avi_file->avi_sound_header.fccType = streamtypeAUDIO;
			avi_file->avi_sound_header.dwQuality = (DWORD)-1;
			avi_file->avi_sound_header.dwScale = avi_file->wave_format.nBlockAlign;
			avi_file->avi_sound_header.dwRate = avi_file->wave_format.nAvgBytesPerSec;
			avi_file->avi_sound_header.dwSampleSize = avi_file->wave_format.nBlockAlign;
			avi_file->avi_sound_header.dwInitialFrames = 1;
			if(FAILED(AVIFileCreateStream(avi_file->avi_file, &avi_file->streams[AUDIO_STREAM], &avi_file->avi_sound_header)))
				break;

			// AVISaveOptions doesn't seem to work for audio streams
			// so here we just copy the pointer for the compressed stream
			avi_file->compressed_streams[AUDIO_STREAM] = avi_file->streams[AUDIO_STREAM];

			// set the stream format
			if(FAILED(AVIStreamSetFormat(avi_file->compressed_streams[AUDIO_STREAM], 0, (void*)&avi_file->wave_format, sizeof(WAVEFORMATEX))))
				break;
		}

		// initialize counters
		avi_file->video_frames = 0;
		avi_file->sound_samples = 0;
		avi_file->tBytes = 0;
		avi_file->ByteBuffer = 0;
		avi_file->audio_buffer_pos = 0;

		// success
		error = 0;
		result = 1;
		avi_file->valid = 1;

	} while(0);

	if(!result)
	{
		avi_destroy(&avi_file);
		if(error)
			EMU_PrintError("Error writing AVI file");
	}

	return result;
}