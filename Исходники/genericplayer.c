int generic_get_info(struct music_info *info)
{
	if (info->type & MD_GET_TITLE) {
		info->encode = g_info.tag.encode;

		if (info->encode != conf_encode_ucs)
			STRCPY_S(info->title, g_info.tag.title);
		else
			memcpy(info->title, g_info.tag.title, sizeof(info->title));
	}
	if (info->type & MD_GET_ALBUM) {
		info->encode = g_info.tag.encode;

		if (info->encode != conf_encode_ucs)
			STRCPY_S(info->album, g_info.tag.album);
		else
			memcpy(info->album, g_info.tag.album, sizeof(info->album));
	}
	if (info->type & MD_GET_ARTIST) {
		info->encode = g_info.tag.encode;

		if (info->encode != conf_encode_ucs)
			STRCPY_S(info->artist, g_info.tag.artist);
		else
			memcpy(info->artist, g_info.tag.artist, sizeof(info->artist));
	}
	if (info->type & MD_GET_COMMENT) {
		info->encode = g_info.tag.encode;

		if (info->encode != conf_encode_ucs)
			STRCPY_S(info->comment, g_info.tag.comment);
		else
			memcpy(info->comment, g_info.tag.comment, sizeof(info->comment));
	}
	if (info->type & MD_GET_DURATION) {
		info->duration = g_info.duration;
	}
	if (info->type & MD_GET_FREQ) {
		info->freq = g_info.sample_freq;
	}
	if (info->type & MD_GET_CHANNELS) {
		info->channels = g_info.channels;
	}
	if (info->type & MD_GET_AVGKBPS) {
		info->avg_kbps = g_info.avg_bps / 1000;
	}

	return 0;
}