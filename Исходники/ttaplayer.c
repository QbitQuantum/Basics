/**
 * 得到TTA音乐文件相关信息
 *
 * @param pinfo 信息结构体指针
 *
 * @return
 */
static int tta_get_info(struct music_info *pinfo)
{
	generic_get_info(pinfo);

	if (pinfo->type & MD_GET_TITLE) {
		if (g_info.tag.title[0] == '\0') {
			pinfo->encode = conf_encode_gbk;
			STRCPY_S(pinfo->title, (const char *) ttainfo.ID3.title);
		}
	}
	if (pinfo->type & MD_GET_ARTIST) {
		if (g_info.tag.artist[0] == '\0') {
			pinfo->encode = conf_encode_gbk;
			STRCPY_S(pinfo->artist, (const char *) ttainfo.ID3.artist);
		}
	}
	if (pinfo->type & MD_GET_ALBUM) {
		if (g_info.tag.album[0] == '\0') {
			pinfo->encode = conf_encode_gbk;
			STRCPY_S(pinfo->album, (const char *) ttainfo.ID3.album);
		}
	}
	if (pinfo->type & MD_GET_CURTIME) {
		pinfo->cur_time = g_play_time;
	}
	if (pinfo->type & MD_GET_CPUFREQ) {
#ifdef _DEBUG
		pinfo->psp_freq[0] = 222;
#else
		pinfo->psp_freq[0] = 111;
#endif
		pinfo->psp_freq[1] = pinfo->psp_freq[0] / 2;
	}
	if (pinfo->type & MD_GET_FREQ) {
		pinfo->freq = ttainfo.SAMPLERATE;
	}
	if (pinfo->type & MD_GET_CHANNELS) {
		pinfo->channels = ttainfo.NCH;
	}
	if (pinfo->type & MD_GET_AVGKBPS) {
		pinfo->avg_kbps = ttainfo.BITRATE;
	}
	if (pinfo->type & MD_GET_DECODERNAME) {
		STRCPY_S(pinfo->decoder_name, "tta");
	}
	if (pinfo->type & MD_GET_ENCODEMSG) {
		if (config.show_encoder_msg && g_status != ST_UNKNOWN) {
			SPRINTF_S(pinfo->encode_msg, "%s: %.2f", _("压缩率"),
					  ttainfo.COMPRESS);
		} else {
			pinfo->encode_msg[0] = '\0';
		}
	}

	return 0;
}