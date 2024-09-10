static int mp3_load(const char *spath, const char *lpath)
{
	int ret;

	__init();

	dbg_printf(d, "%s: loading %s", __func__, spath);
	g_status = ST_UNKNOWN;

	mp3_data.use_buffer = true;

	mp3_data.fd = xrIoOpen(spath, PSP_O_RDONLY, 0777);

	if (mp3_data.fd < 0)
		return -1;

	g_info.filesize = xrIoLseek(mp3_data.fd, 0, PSP_SEEK_END);
	xrIoLseek(mp3_data.fd, 0, PSP_SEEK_SET);
	mp3_data.size = g_info.filesize;

	if (g_info.filesize < 0)
		return g_info.filesize;

	xrIoLseek(mp3_data.fd, 0, PSP_SEEK_SET);

	mad_stream_init(&stream);
	mad_frame_init(&frame);
	mad_synth_init(&synth);

	if (use_me) {
		if ((ret = me_init()) < 0) {
			dbg_printf(d, "me_init failed: %d", ret);
			use_me = false;
		}
	}

	mp3info.check_crc = check_crc;
	mp3info.have_crc = false;

	if (use_brute_method) {
		if (read_mp3_info_brute(&mp3info, &mp3_data) < 0) {
			__end();
			return -1;
		}
	} else {
		if (read_mp3_info(&mp3info, &mp3_data) < 0) {
			__end();
			return -1;
		}
	}

	g_info.channels = mp3info.channels;
	g_info.sample_freq = mp3info.sample_freq;
	g_info.avg_bps = mp3info.average_bitrate;
	g_info.samples = mp3info.frames;
	g_info.duration = mp3info.duration;

	generic_readtag(&g_info, spath);

	if (mp3_data.use_buffer) {
		SceOff cur = xrIoLseek(mp3_data.fd, 0, PSP_SEEK_CUR);

		xrIoClose(mp3_data.fd);
		mp3_data.fd = -1;
		mp3_data.r = buffered_reader_open(spath, g_io_buffer_size, 1);

		if (mp3_data.r == NULL) {
			__end();
			return -1;
		}

		buffered_reader_seek(mp3_data.r, cur);
	}

	dbg_printf(d, "[%d channel(s), %d Hz, %.2f kbps, %02d:%02d%sframes %d%s]",
			   g_info.channels, g_info.sample_freq,
			   g_info.avg_bps / 1000,
			   (int) (g_info.duration / 60), (int) g_info.duration % 60,
			   mp3info.frameoff != NULL ? ", frame table, " : ", ",
			   g_info.samples, mp3info.have_crc ? ", crc passed" : "");

#ifdef _DEBUG
	if (mp3info.lame_encoded) {
		char lame_method[80];
		char encode_msg[80];

		switch (mp3info.lame_mode) {
			case ABR:
				STRCPY_S(lame_method, "ABR");
				break;
			case CBR:
				STRCPY_S(lame_method, "CBR");
				break;
			case VBR:
				SPRINTF_S(lame_method, "VBR V%1d", mp3info.lame_vbr_quality);
				break;
			default:
				break;
		}

		if (mp3info.lame_str[strlen(mp3info.lame_str) - 1] == ' ')
			SPRINTF_S(encode_msg, "%s%s", mp3info.lame_str, lame_method);
		else
			SPRINTF_S(encode_msg, "%s %s", mp3info.lame_str, lame_method);
		dbg_printf(d, "[ %s ]", encode_msg);
	}
#endif

	ret = xAudioInit();

	if (ret < 0) {
		__end();
		return -1;
	}

	ret = xAudioSetFrequency(g_info.sample_freq);
	if (ret < 0) {
		__end();
		return -1;
	}

	g_buff = xAudioAlloc(0, BUFF_SIZE);

	if (g_buff == NULL) {
		__end();
		return -1;
	}

	if (use_me)
		xAudioSetChannelCallback(0, memp3_audiocallback, NULL);
	else
		xAudioSetChannelCallback(0, mp3_audiocallback, NULL);

	generic_lock();
	g_status = ST_LOADED;
	generic_unlock();

	return 0;
}