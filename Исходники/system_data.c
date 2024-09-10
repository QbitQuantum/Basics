void sys_data_select_audio_language(UINT8 langid1, UINT8 langid2)
{
	UINT8 szLangGroup[AUDIO_CODE_CNT][4]; /*default is 2,for support multicode*/
	UINT8 i, multi_audio_cnt;
	UINT8 strm_lang_num, strm_multicode_num;
	UINT8 lang_code[4], lang_codem[4];

	if (langid1 >= STREAM_ISO_639_NUM)
		langid1 = 0;
	if (langid2 >= STREAM_ISO_639_NUM)
		langid2 = langid1;

	multi_audio_cnt = 2;
	strm_lang_num = get_stream_lang_cnt();
	strm_multicode_num = get_stream_langm_cnt();
	MEMSET(lang_code,0,4);	// add lang_code init
	MEMSET(lang_codem,0,4);
	MEMCPY(lang_code, stream_iso_639lang_abbr[langid1], 3);
	MEMCPY(lang_codem, lang_code, 3);
	for (i = 0; i < strm_multicode_num; i++)
	{
		if (MEMCMP(iso_639lang_multicode[i][0], lang_code, 3) == 0)
		{
			MEMCPY(lang_codem, iso_639lang_multicode[i][1], 3);
			multi_audio_cnt = 3;
			break;
		}
	}


	if (multi_audio_cnt == 2)
	{
		STRCPY(szLangGroup[0], lang_code); /*copy Country abrev.*/
		STRCPY(szLangGroup[1], stream_iso_639lang_abbr[langid2]);
	}
	else if (multi_audio_cnt == 3)
	{
		STRCPY(szLangGroup[0], lang_code);
		STRCPY(szLangGroup[1], lang_codem);
		STRCPY(szLangGroup[2], stream_iso_639lang_abbr[langid2]);
	}

	system_config.lang.Audio_lang_1 = langid1;
	system_config.lang.Audio_lang_2 = langid2;
	//UIChChgSetAudLanguage ( szLangGroup, multi_audio_cnt );
	api_set_audio_language( szLangGroup, multi_audio_cnt );
}