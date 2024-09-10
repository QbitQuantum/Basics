HANDLE createfile(const TCHAR *filename, size_w length)
{
	TCHAR tmpfile[MAX_PATH];
	const TCHAR *newname = filename;
	HANDLE hFile;

	if(filename == 0)
	{
		GetTempPath(MAX_PATH, tmpfile);
		GetTempFileName(tmpfile, TEXT("~HX"), 0, tmpfile);

		newname = tmpfile;
	}

	hFile = CreateFile(newname, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER set;
		LARGE_INTEGER result;

		set.QuadPart = length;
	
		// allocate space for desired file size
		if(SetFilePointerEx(hFile, set, &result, FILE_BEGIN))
		{
			if(SetEndOfFile(hFile))
			{
				return hFile;
			}
		}

		CloseHandle(hFile);
	}

	if(filename == 0)
		DeleteFile(tmpfile);

	return 0;
}