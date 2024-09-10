/*
 * os_stat -- stat abstraction layer
 */
int
os_stat(const char *pathname, os_stat_t *buf)
{
	wchar_t *path = util_toUTF16(pathname);
	if (path == NULL)
		return -1;

	int ret = _wstat64(path, buf);

	util_free_UTF16(path);
	return ret;
}