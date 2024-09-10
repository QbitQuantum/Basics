static void
pidgin_sound_play_file_win32(const char *filename)
{
	wchar_t *wc_filename = g_utf8_to_utf16(filename,
			-1, NULL, NULL, NULL);
	if (!PlaySoundW(wc_filename, NULL, SND_ASYNC | SND_FILENAME))
		purple_debug(PURPLE_DEBUG_ERROR, "sound", "Error playing sound.\n");
	g_free(wc_filename);
}