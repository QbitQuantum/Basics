size_t os_get_abs_path(const char *path, char *abspath, size_t size)
{
	wchar_t wpath[512];
	wchar_t wabspath[512];
	size_t out_len = 0;
	size_t len;

	if (!abspath)
		return 0;

	len = os_utf8_to_wcs(path, 0, wpath, 512);
	if (!len)
		return 0;

	if (_wfullpath(wabspath, wpath, 512) != NULL)
		out_len = os_wcs_to_utf8(wabspath, 0, abspath, size);
	return out_len;
}