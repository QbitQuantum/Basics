bool vtUnzip::change_file_date(const char *filename, uLong dosdate, tm_unz tmu_date)
{
	bool bOK = false;
#ifdef _WIN32
#if SUPPORT_WSTRING
	wstring2 ws;
	ws.from_utf8(filename);
	HANDLE hFile = CreateFileW(ws.c_str(), GENERIC_READ | GENERIC_WRITE, 0,NULL,
		OPEN_EXISTING,0,NULL);
#else
	HANDLE hFile = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE, 0,NULL,
		OPEN_EXISTING,0,NULL);
#endif
	bOK = (hFile != INVALID_HANDLE_VALUE);
	if (bOK)
	{
		FILETIME ftm,ftLocal,ftLastAcc;
		BOOL bBOK = GetFileTime(hFile,NULL,&ftLastAcc,NULL);
		bOK = (bBOK == TRUE);
		DosDateTimeToFileTime((WORD)(dosdate>>16),(WORD)dosdate,&ftLocal);
		LocalFileTimeToFileTime(&ftLocal,&ftm);
		SetFileTime(hFile,&ftm,&ftLastAcc,&ftm);
		CloseHandle(hFile);
	}
#else
	// TODO: Unix implementation, if needed.  Do we care about file dates?
	bOK = true;
#endif
	return bOK;
}