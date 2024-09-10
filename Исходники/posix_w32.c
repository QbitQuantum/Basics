int p_creat(const char *path, mode_t mode)
{
	int fd;
	wchar_t* buf = gitwin_to_utf16(path);
	fd = _wopen(buf, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, mode);

	git__free(buf);
	return fd;
}