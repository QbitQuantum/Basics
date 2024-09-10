	BOOL __cdecl GetInfo(char *filename, int audioDataOffset, TrackInfo *trackInfo)
	{
		BYTE module[ASAPInfo_MAX_MODULE_LENGTH];
		int module_len;
		if (!loadModule(filename, module, &module_len))
			return FALSE;
		ASAPInfo *info = ASAPInfo_New();
		if (info == NULL)
			return FALSE;
		if (!ASAPInfo_Load(info, filename, module, module_len)) {
			ASAPInfo_Delete(info);
			return FALSE;
		}
		strcpy(trackInfo->suggestedTitle, ASAPInfo_GetTitle(info));
		trackInfo->fileSize = module_len;
		trackInfo->seekable = TRUE;
		trackInfo->hasEqualizer = FALSE;
		int duration = getSongDuration(info, ASAPInfo_GetDefaultSong(info));
		trackInfo->playingTime = duration >= 0 ? duration : -1;
		trackInfo->bitRate = 0;
		trackInfo->sampleRate = ASAP_SAMPLE_RATE;
		trackInfo->numChannels = ASAPInfo_GetChannels(info);
		trackInfo->bitResolution = BITS_PER_SAMPLE;
		strcpy(trackInfo->fileTypeDescription, "8-bit Atari music");
		ASAPInfo_Delete(info);
		return TRUE;
	}