char *iposix_path_abspath_w(const char *srcpath, char *path, int maxsize)
{
	char *fname;
	DWORD hr = GetFullPathNameA(srcpath, maxsize, path, &fname);
	if (hr == 0) return NULL;
	return path;
}