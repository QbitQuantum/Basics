uint64_t fsize(const char *filename)
{
#if __MINGW32__
	struct __stat64 st;
	if (_stat64(filename, &st) == 0) return st.st_size;
#else
	struct stat st;
	if (stat(filename, &st) == 0) return st.st_size;
#endif
	return 0;
}