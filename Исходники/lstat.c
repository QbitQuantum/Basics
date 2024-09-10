static dev_t stat_dev_for(const wchar_t *wpathname)
{
	DWORD len;
	wchar_t *fullpath;

	len = GetFullPathNameW(wpathname, 0, NULL, NULL);
	fullpath = __builtin_alloca((len + 1) * sizeof(wchar_t));
	if(!GetFullPathNameW(wpathname, len, fullpath, NULL)) {
		fprintf(stderr, "tup error: GetFullPathNameW(\"%ls\") failed: 0x%08lx\n", wpathname, GetLastError());
		return 0;
	}
	if(fullpath[1] != L':') {
		return 0;
	}
	return fullpath[0] - L'A';
}