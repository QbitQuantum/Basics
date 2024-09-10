void get_full_path(wchar_t *file_name, wchar_t *file_name2)
{
	// current directory 를 구한다.
	wchar_t *buf = NULL;
	uint32_t buflen = 0;
	buflen = GetCurrentDirectoryW(buflen, buf);
	if (0 == buflen)
	{
		fprintf(stderr, "err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		return;
	}

	buf = (PWSTR)malloc(sizeof(WCHAR)* buflen);
	if (0 == GetCurrentDirectoryW(buflen, buf))
	{
		fprintf(stderr, "err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		free(buf);
		return;
	}

	// current dir \\ bob.txt, bob2.txt 파일명 생성
	if (!SUCCEEDED(StringCbPrintfW(
		file_name,
		sizeof(wchar_t) * FILE_NAME_SIZE,
		L"%ws\\bob.txt",
		buf)))
	{
		fprintf(stderr, "err, can not create file name");
		free(buf);
		return;
	}

	if (!SUCCEEDED(StringCbPrintfW(
		file_name2,
		sizeof(wchar_t) * FILE_NAME_SIZE,
		L"%ws\\bob2.txt",
		buf)))
	{
		fprintf(stderr, "err, can not create file name");
		free(buf);
		return;
	}
	free(buf); buf = NULL;
}