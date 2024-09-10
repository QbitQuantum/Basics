static bool_t get_lyrics_step_3(void *buf, int64_t len, void *requri)
{
	if (strcmp(state.uri, requri))
	{
		free(buf);
		str_unref(requri);
		return FALSE;
	}
	str_unref(requri);

	if(!len)
	{
		SPRINTF(error, _("Unable to fetch %s"), state.uri);
		update_lyrics_window(_("Error"), NULL, error);
		free(buf);
		return FALSE;
	}

	char *lyrics = scrape_lyrics_from_lyricwiki_edit_page(buf, len);

	if(!lyrics)
	{
		SPRINTF(error, _("Unable to parse %s"), state.uri);
		update_lyrics_window(_("Error"), NULL, error);
		free(buf);
		return FALSE;
	}

	update_lyrics_window(state.title, state.artist, lyrics);

	free(lyrics);
	return TRUE;
}