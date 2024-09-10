voidpf ZCALLBACK win32_open64_file_funcW(voidpf opaque, const void *filename, int mode) {
	const char *mode_fopen = NULL;
	DWORD dwDesiredAccess, dwCreationDisposition, dwShareMode, dwFlagsAndAttributes ;
	HANDLE hFile = NULL;
	win32_translate_open_mode(mode, &dwDesiredAccess, &dwCreationDisposition, &dwShareMode, &dwFlagsAndAttributes);
#ifdef IOWIN32_USING_WINRT_API
	if ((filename != NULL) && (dwDesiredAccess != 0)) {
		hFile = CreateFile2((LPCWSTR)filename, dwDesiredAccess, dwShareMode, dwCreationDisposition, NULL);
	}
#else
	if ((filename != NULL) && (dwDesiredAccess != 0)) {
		hFile = CreateFileW((LPCWSTR)filename, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
	}
#endif
	return win32_build_iowin(hFile);
}