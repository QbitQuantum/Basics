static bool get_thumb_dir(char *dir, ThumbSize size)
{
	char *s = dir;
	const char *subdir;
#ifdef WIN32
	wchar_t dir_16[MAX_PATH];
	/* yes, applications shouldn't store data there, but so does GIMP :)*/
	SHGetSpecialFolderPathW(0, dir_16, CSIDL_PROFILE, 0);
	conv_utf_16_to_8(dir_16, dir, FILE_MAX);
	s += strlen(dir);
#else
#if defined(USE_FREEDESKTOP)
	const char *home_cache = getenv("XDG_CACHE_HOME");
	const char *home = home_cache ? home_cache : getenv("HOME");
#else
	const char *home = getenv("HOME");
#endif
	if (!home) return 0;
	s += BLI_strncpy_rlen(s, home, FILE_MAX);

#ifdef USE_FREEDESKTOP
	if (!home_cache) {
		s += BLI_strncpy_rlen(s, "/.cache", FILE_MAX - (s - dir));
	}
#endif
#endif
	switch (size) {
		case THB_NORMAL:
			subdir = "/" THUMBNAILS "/normal/";
			break;
		case THB_LARGE:
			subdir = "/" THUMBNAILS "/large/";
			break;
		case THB_FAIL:
			subdir = "/" THUMBNAILS "/fail/blender/";
			break;
		default:
			return 0; /* unknown size */
	}

	s += BLI_strncpy_rlen(s, subdir, FILE_MAX - (s - dir));
	(void)s;

	return 1;
}