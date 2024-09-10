// Open the Internet file
VW_FILE *VwOpenFile(char *path)
{
	VW_FILE *f;
	HINTERNET hHttpFile;
	HINTERNET hInternet = InternetOpenA(
		"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL, NULL, 0);
	UINT size;
	UINT sizesize;
	char tmp[8];
	// Validate arguments
	if (path == NULL)
	{
		return NULL;
	}

	if (hInternet == NULL)
	{
		return NULL;
	}

	hHttpFile = InternetOpenUrlA(hInternet, path, NULL, 0,
		INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_RELOAD, 0);

	if (hHttpFile == NULL)
	{
		InternetCloseHandle(hInternet);
		return NULL;
	}

	size = 0;
	sizesize = sizeof(size);

	ZeroMemory(tmp, sizeof(tmp));

	if (strlen(path) >= 6)
	{
		CopyMemory(tmp, path, 6);
	}

	if (lstrcmpi(tmp, "ftp://") == 0)
	{
		// ftp
		DWORD high = 0;

		size = FtpGetFileSize(hHttpFile, &high);
	}
	else
	{
		UINT errorcode = 0;
		UINT errorcode_size = sizeof(errorcode);

		// http
		if (HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,
			&size, &sizesize, NULL) == false)
		{
			size = 0;
		}

		if (HttpQueryInfo(hHttpFile, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
			&errorcode, &errorcode_size, NULL) == false ||
			(errorcode / 100) != 2)
		{
			// HTTP getting error
			InternetCloseHandle(hInternet);
			InternetCloseHandle(hHttpFile);
			return NULL;
		}
	}

	f = ZeroMalloc(sizeof(VW_FILE));
	f->hInternet = hInternet;
	f->hHttpFile = hHttpFile;
	f->FileSize = size;

	return f;
}