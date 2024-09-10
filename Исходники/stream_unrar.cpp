bool getPathInfo(const char * name, fileInfo & info)
{
	// we don't handle symbolic links as destinations
	if (name == NULL)
		return false;

	int result;
#ifdef WINDOWS
	struct __stat64 buf;
	result = _stat64(name, &buf);
#else
	struct stat64 buf;
	result = stat64(name, &buf);
#endif

	info.isDir = (buf.st_mode & S_IFDIR) != 0;
	info.isFile = (buf.st_mode & S_IFREG) != 0;

	return result == 0 ? true : false;
}