/*
 * Download a file from an URL
 * Mostly taken from http://support.microsoft.com/kb/234913
 * If hProgressDialog is not NULL, this function will send INIT and EXIT messages
 * to the dialog in question, with WPARAM being set to nonzero for EXIT on success
 * and also attempt to indicate progress using an IDC_PROGRESS control
 */
DWORD DownloadFile(const char* url, const char* file, HWND hProgressDialog)
{
	HWND hProgressBar = NULL;
	BOOL r = FALSE;
	LONG progress_style;
	DWORD dwFlags, dwSize, dwWritten, dwDownloaded, dwTotalSize;
	DWORD DownloadStatus;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	const char* accept_types[] = {"*/*\0", NULL};
	unsigned char buf[DOWNLOAD_BUFFER_SIZE];
	char agent[64], hostname[64], urlpath[128], msg[MAX_PATH];
	HINTERNET hSession = NULL, hConnection = NULL, hRequest = NULL;
	URL_COMPONENTSA UrlParts = {sizeof(URL_COMPONENTSA), NULL, 1, (INTERNET_SCHEME)0,
		hostname, sizeof(hostname), 0, NULL, 1, urlpath, sizeof(urlpath), NULL, 1};
	size_t last_slash;
	int i;

	DownloadStatus = 404;
	if (hProgressDialog != NULL) {
		// Use the progress control provided, if any
		hProgressBar = GetDlgItem(hProgressDialog, IDC_PROGRESS);
		if (hProgressBar != NULL) {
			progress_style = GetWindowLong(hProgressBar, GWL_STYLE);
			SetWindowLong(hProgressBar, GWL_STYLE, progress_style & (~PBS_MARQUEE));
			SendMessage(hProgressBar, PBM_SETPOS, 0, 0);
		}
		SendMessage(hProgressDialog, UM_DOWNLOAD_INIT, 0, 0);
	}

	if (file == NULL)
		goto out;

	for (last_slash = safe_strlen(file); last_slash != 0; last_slash--) {
		if ((file[last_slash] == '/') || (file[last_slash] == '\\')) {
			last_slash++;
			break;
		}
	}

	static_sprintf(msg, "Downloading %s: Connecting...", file);
	print_status(0, FALSE, msg);
	dprintf("Downloading %s from %s\n", file, url);

	if ( (!InternetCrackUrlA(url, (DWORD)safe_strlen(url), 0, &UrlParts))
	  || (UrlParts.lpszHostName == NULL) || (UrlParts.lpszUrlPath == NULL)) {
		dprintf("Unable to decode URL: %s\n", WinInetErrorString());
		goto out;
	}
	hostname[sizeof(hostname)-1] = 0;

	// Open an Internet session
	for (i=5; (i>0) && (!InternetGetConnectedState(&dwFlags, 0)); i--) {
		Sleep(1000);
	}
	if (i <= 0) {
		// http://msdn.microsoft.com/en-us/library/windows/desktop/aa384702.aspx is wrong...
		SetLastError(ERROR_INTERNET_NOT_INITIALIZED);
		dprintf("Network is unavailable: %s\n", WinInetErrorString());
		goto out;
	}
	static_sprintf(agent, APPLICATION_NAME "/%d.%d.%d (Windows NT %d.%d%s)",
		application_version[0], application_version[1], application_version[2],
		nWindowsVersion>>4, nWindowsVersion&0x0F, is_x64()?"; WOW64":"");
	hSession = InternetOpenA(agent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession == NULL) {
		dprintf("Could not open Internet session: %s\n", WinInetErrorString());
		goto out;
	}

	hConnection = InternetConnectA(hSession, UrlParts.lpszHostName, UrlParts.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, (DWORD_PTR)NULL);
	if (hConnection == NULL) {
		dprintf("Could not connect to server %s:%d: %s\n", UrlParts.lpszHostName, UrlParts.nPort, WinInetErrorString());
		goto out;
	}

	hRequest = HttpOpenRequestA(hConnection, "GET", UrlParts.lpszUrlPath, NULL, NULL, accept_types,
		INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP|INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS|
		INTERNET_FLAG_NO_COOKIES|INTERNET_FLAG_NO_UI|INTERNET_FLAG_NO_CACHE_WRITE|INTERNET_FLAG_HYPERLINK|
		((UrlParts.nScheme==INTERNET_SCHEME_HTTPS)?INTERNET_FLAG_SECURE:0), (DWORD_PTR)NULL);
	if (hRequest == NULL) {
		dprintf("Could not open URL %s: %s\n", url, WinInetErrorString());
		goto out;
	}

	if (!HttpSendRequestA(hRequest, NULL, 0, NULL, 0)) {
		dprintf("Unable to send request: %s\n", WinInetErrorString());
		goto out;
	}

	// Get the file size
	dwSize = sizeof(DownloadStatus);
	HttpQueryInfoA(hRequest, HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, (LPVOID)&DownloadStatus, &dwSize, NULL);
	if (DownloadStatus != 200) {
		error_code = ERROR_SEVERITY_ERROR|ERROR_INTERNET_ITEM_NOT_FOUND;
		dprintf("Unable to access file: %d\n", DownloadStatus);
		goto out;
	}
	dwSize = sizeof(dwTotalSize);
	if (!HttpQueryInfoA(hRequest, HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER, (LPVOID)&dwTotalSize, &dwSize, NULL)) {
		dprintf("Unable to retrieve file length: %s\n", WinInetErrorString());
		goto out;
	}
	dprintf("File length: %d bytes\n", dwTotalSize);

	hFile = CreateFileU(file, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		dprintf("Unable to create file '%s': %s\n", &file[last_slash], WinInetErrorString());
		goto out;
	}

	// Keep checking for data until there is nothing left.
	dwSize = 0;
	while (1) {
		if (IS_ERROR(error_code))
			goto out;

		if (!InternetReadFile(hRequest, buf, sizeof(buf), &dwDownloaded) || (dwDownloaded == 0))
			break;
		dwSize += dwDownloaded;
		SendMessage(hProgressBar, PBM_SETPOS, (WPARAM)(MAX_PROGRESS*((1.0f*dwSize)/(1.0f*dwTotalSize))), 0);
		static_sprintf(msg, "Downloading: %0.1f%%", (100.0f*dwSize)/(1.0f*dwTotalSize));
		print_status(0, FALSE, msg);
		if (!WriteFile(hFile, buf, dwDownloaded, &dwWritten, NULL)) {
			dprintf("Error writing file '%s': %s\n", &file[last_slash], WinInetErrorString());
			goto out;
		} else if (dwDownloaded != dwWritten) {
			dprintf("Error writing file '%s': Only %d/%d bytes written\n", dwWritten, dwDownloaded);
			goto out;
		}
	}

	if (dwSize != dwTotalSize) {
		dprintf("Could not download complete file - read: %d bytes, expected: %d bytes\n", dwSize, dwTotalSize);
		error_code = ERROR_SEVERITY_ERROR|ERROR_WRITE_FAULT;
		goto out;
	} else {
		r = TRUE;
		dprintf("Successfully downloaded '%s'\n", &file[last_slash]);
	}

out:
	if (hProgressDialog != NULL)
		SendMessage(hProgressDialog, UM_DOWNLOAD_EXIT, (WPARAM)r, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		// Force a flush - May help with the PKI API trying to process downloaded updates too early...
		FlushFileBuffers(hFile);
		CloseHandle(hFile);
	}
	if (!r) {
		if (file != NULL)
			_unlinkU(file);
		print_status(0, FALSE, "Failed to download file.");
		SetLastError(error_code);
		MessageBoxU(hMainDialog, WinInetErrorString(), "File download", MB_OK|MB_ICONERROR);
	}
	if (hRequest)
		InternetCloseHandle(hRequest);
	if (hConnection)
		InternetCloseHandle(hConnection);
	if (hSession)
		InternetCloseHandle(hSession);

	return r?dwSize:0;
}