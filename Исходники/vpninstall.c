// Open the file
VI_FILE *ViOpenFile(char *path)
{
	VI_FILE *f;
	// Validate arguments
	if (path == NULL)
	{
		return NULL;
	}

	if (ViIsInternetFile(path))
	{
		HINTERNET hHttpFile;
		HINTERNET hInternet = InternetOpenA(DEFAULT_USER_AGENT,
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL, NULL, 0);
		UINT size;
		UINT sizesize;

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

		if (StartWith(path, "ftp://"))
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

		f = ZeroMalloc(sizeof(VI_FILE));
		f->InternetFile = true;
		f->hInternet = hInternet;
		f->hHttpFile = hHttpFile;
		f->FileSize = size;

		return f;
	}
	else
	{
		IO *io;
		char fullpath[MAX_PATH];
		char exedir[MAX_PATH];

		GetExeDir(exedir, sizeof(exedir));

		ConbinePath(fullpath, sizeof(fullpath), exedir, path);

		io = FileOpen(fullpath, false);
		if (io == NULL)
		{
			return NULL;
		}

		f = ZeroMalloc(sizeof(VI_FILE));
		f->InternetFile = false;
		f->FileSize = FileSize(io);
		f->io = io;

		return f;
	}
}