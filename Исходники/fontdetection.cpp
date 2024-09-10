/**
 * Get the short DOS 8.3 format for paths.
 * FreeType doesn't support Unicode filenames and Windows' fopen (as used
 * by FreeType) doesn't support UTF-8 filenames. So we have to convert the
 * filename into something that isn't UTF-8 but represents the Unicode file
 * name. This is the short DOS 8.3 format. This does not contain any
 * characters that fopen doesn't support.
 * @param long_path the path in UTF-8.
 * @return the short path in ANSI (ASCII).
 */
char *GetShortPath(const char *long_path)
{
	static char short_path[MAX_PATH];
#ifdef UNICODE
	/* The non-unicode GetShortPath doesn't support UTF-8...,
	 * so convert the path to wide chars, then get the short
	 * path and convert it back again. */
	wchar_t long_path_w[MAX_PATH];
	MultiByteToWideChar(CP_UTF8, 0, long_path, -1, long_path_w, MAX_PATH);

	wchar_t short_path_w[MAX_PATH];
	GetShortPathNameW(long_path_w, short_path_w, MAX_PATH);

	WideCharToMultiByte(CP_ACP, 0, short_path_w, -1, short_path, MAX_PATH, NULL, NULL);
#else
	/* Technically not needed, but do it for consistency. */
	GetShortPathNameA(long_path, short_path, MAX_PATH);
#endif
	return short_path;
}