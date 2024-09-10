static int CALLBACK EnumFontCallback(const ENUMLOGFONTEX *logfont, const NEWTEXTMETRICEX *metric, DWORD type, LPARAM lParam)
{
	EFCParam *info = (EFCParam *)lParam;

	/* Only use TrueType fonts */
	if (!(type & TRUETYPE_FONTTYPE)) return 1;
	/* Don't use SYMBOL fonts */
	if (logfont->elfLogFont.lfCharSet == SYMBOL_CHARSET) return 1;

	/* The font has to have at least one of the supported locales to be usable. */
	if ((metric->ntmFontSig.fsCsb[0] & info->locale.lsCsbSupported[0]) == 0 && (metric->ntmFontSig.fsCsb[1] & info->locale.lsCsbSupported[1]) == 0) {
		/* On win9x metric->ntmFontSig seems to contain garbage. */
		FONTSIGNATURE fs;
		memset(&fs, 0, sizeof(fs));
		HFONT font = CreateFontIndirect(&logfont->elfLogFont);
		if (font != NULL) {
			HDC dc = GetDC(NULL);
			HGDIOBJ oldfont = SelectObject(dc, font);
			GetTextCharsetInfo(dc, &fs, 0);
			SelectObject(dc, oldfont);
			ReleaseDC(NULL, dc);
			DeleteObject(font);
		}
		if ((fs.fsCsb[0] & info->locale.lsCsbSupported[0]) == 0 && (fs.fsCsb[1] & info->locale.lsCsbSupported[1]) == 0) return 1;
	}

	const char *english_name = GetEnglishFontName(logfont);
	const char *font_name = WIDE_TO_MB((const TCHAR*)logfont->elfFullName);
	DEBUG(freetype, 1, "Fallback font: %s (%s)", font_name, english_name);

	strecpy(info->settings->small_font,  font_name, lastof(info->settings->small_font));
	strecpy(info->settings->medium_font, font_name, lastof(info->settings->medium_font));
	strecpy(info->settings->large_font,  font_name, lastof(info->settings->large_font));

	/* Add english name after font name */
	strecpy(info->settings->small_font + strlen(info->settings->small_font) + 1, english_name, lastof(info->settings->small_font));
	strecpy(info->settings->medium_font + strlen(info->settings->medium_font) + 1, english_name, lastof(info->settings->medium_font));
	strecpy(info->settings->large_font + strlen(info->settings->large_font) + 1, english_name, lastof(info->settings->large_font));
	return 0; // stop enumerating
}