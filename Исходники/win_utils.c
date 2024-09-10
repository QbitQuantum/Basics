/**
 * Check if given file can be opened with exclusive write access.
 *
 * @param path path to the file
 * @return 1 if file can be opened, 0 otherwise
 */
int can_open_exclusive(const char* path)
{
	int i, res = 0;
	for(i = 0; i < 2 && res == 0; i++) {
		int fd;
		wchar_t* wpath = c2w(path, i);
		if(wpath == NULL) continue;
		fd = _wsopen(wpath, _O_RDONLY | _O_BINARY, _SH_DENYWR, 0);
		if(fd >= 0) {
			res = 1;
			_close(fd);
		}
		free(wpath);
	}
	return res;
}