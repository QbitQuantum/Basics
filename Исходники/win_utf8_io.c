int _stat64_utf8(const char *path, struct __stat64 *buffer)
{
	wchar_t *wpath;
	int ret;

	if (!(wpath = wchar_from_utf8(path))) return -1;
	ret = _wstat64(wpath, buffer);
	free(wpath);

	return ret;
}