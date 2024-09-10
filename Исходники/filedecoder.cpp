void FileDecoder::metadata_callback(const ::FLAC__StreamMetadata *metadata)
{
	// assert(FileSize != 0);

	if (metadata->type == FLAC__METADATA_TYPE_STREAMINFO)
	{
		TotalSamples = (unsigned)metadata->data.stream_info.total_samples & 0xfffffffful;
		MapPluginFileInfo.nBitsPerSample = metadata->data.stream_info.bits_per_sample;
		MapPluginFileInfo.nChannels = metadata->data.stream_info.channels;
		MapPluginFileInfo.nSampleRate = metadata->data.stream_info.sample_rate;
		MapPluginFileInfo.nAvgBitrate = (unsigned)(FileSize / (125. * TotalSamples / MapPluginFileInfo.nSampleRate));
		MapPluginFileInfo.nDuration = (unsigned)((double)TotalSamples / (double)MapPluginFileInfo.nSampleRate * 1000.0 + 0.5);
	}
	else if (metadata->type == FLAC__METADATA_TYPE_VORBIS_COMMENT)
	{
		hasFileTag=TRUE;

		for (unsigned i = 0; i < metadata->data.vorbis_comment.num_comments; ++i)
		{
			char buffer[MAX_PLUGIN_TAG_STR];
			wchar_t wbuffer[MAX_PLUGIN_TAG_STR]={0};
			memcpy(buffer, metadata->data.vorbis_comment.comments[i].entry, min(MAX_PLUGIN_TAG_STR, metadata->data.vorbis_comment.comments[i].length + 1));
			MultiByteToWideChar(CP_UTF8, 0, buffer, strlen(buffer), wbuffer, sizeof(wbuffer) / sizeof(wchar_t));

			wchar_t* wchr = wcschr(wbuffer, L'=');
			if (wchr == NULL)
				continue;

			*wchr = L'\0'; // NULL terminate the string
			wchr++; // Move to the value (it moves 1 wchar_t, aka 2 bytes)
			_wcslwr(wbuffer); // Make the field name lowercase for easy comparison

			if (wcscmp(wbuffer, L"title") == 0)
				wcscpy(FileTag.szTrack, wchr);
			else if (wcscmp(wbuffer, L"artist") == 0)
				wcscpy(FileTag.szArtist, wchr);
			else if (wcscmp(wbuffer, L"album") == 0)
				wcscpy(FileTag.szAlbum, wchr);
			else if (wcscmp(wbuffer, L"comment") == 0)
				wcscpy(FileTag.szComment, wchr);
			else if (wcscmp(wbuffer, L"genre") == 0)
				wcscpy(FileTag.szGenre, wchr);
			else if (wcscmp(wbuffer, L"tracknumber") == 0)
				FileTag.nTrackNum = _wtoi(wchr);
			else if (wcscmp(wbuffer, L"date") == 0)
			{
				*(wchr + 4) = L'\0';
				FileTag.nYear = _wtoi(wchr);
			}
		}
		int a = 5;
	}
}