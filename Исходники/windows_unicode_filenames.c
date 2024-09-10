int flac_internal_stat64_utf8(const char *path, struct __stat64 *buffer)
{
	if (!utf8_filenames) {
		return _stat64(path, buffer);
	} else {
		wchar_t *wpath;
		int ret;

		if (!(wpath = wchar_from_utf8(path))) return -1;
		ret = _wstat64(wpath, buffer);
		free(wpath);

		return ret;
	}
}