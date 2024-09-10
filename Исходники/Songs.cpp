int Songs::LoadHistory(const char *userId) {
	//ここでサーバに接続して前回と前々回の点数を受信
	HINTERNET      hSession, hConnect, hRequest;
	URL_COMPONENTS urlComponents;
	WCHAR          szHostName[256], szUrlPath[2048];
	//URL
	WCHAR          szUrl[256] = L"http://globalstudios.jp/mai-archive/api_history.php?user="******"Sample Application/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		0);
	if (hSession == NULL)
		return -1;

	ZeroMemory(&urlComponents, sizeof(URL_COMPONENTS));
	urlComponents.dwStructSize = sizeof(URL_COMPONENTS);
	urlComponents.lpszHostName = szHostName;
	urlComponents.dwHostNameLength = sizeof(szHostName) / sizeof(WCHAR);
	urlComponents.lpszUrlPath = szUrlPath;
	urlComponents.dwUrlPathLength = sizeof(szUrlPath) / sizeof(WCHAR);


	if (!WinHttpCrackUrl(szUrl, lstrlenW(szUrl), 0, &urlComponents)) {
		WinHttpCloseHandle(hSession);
		return -1;
	}

	//接続
	hConnect = WinHttpConnect(hSession, szHostName, INTERNET_DEFAULT_PORT, 0);
	if (hConnect == NULL) {
		WinHttpCloseHandle(hSession);
		return -1;
	}

	hRequest = WinHttpOpenRequest(hConnect,
		L"GET",
		szUrlPath,
		NULL,
		WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES,
		0);
	if (hRequest == NULL) {
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return -1;
	}

	if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, WINHTTP_IGNORE_REQUEST_TOTAL_LENGTH, 0)) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return 0;
	}

	WinHttpReceiveResponse(hRequest, NULL);

	//ボディ取得
	lpData = ReadData(hRequest, &dwSize);
	for (int i = 0; i < NUMSONGS; i++) {
		char* temp = NULL;
		char* ctx;//内部的に使用するので深く考えない

		if (i == 0) {
			temp = strtok_s((char*)lpData, "\n", &ctx);

		} else {
			temp = strtok_s(0, "\n", &ctx);
		}
		if (temp == NULL)break;
		int history[2] = {};
		int hoge;
		sscanf_s(temp, "%d||%d||%d", &hoge, &history[0], &history[1]);
		//以下の式を実行することによってデータを保存
		//song[Search(<曲ID>)]->songHistory->Set(＜前回と前々回の点数（配列ポインタ）＞);
		song[Search(hoge)]->songHistory->Set(history);
	}
	HeapFree(GetProcessHeap(), 0, lpData);

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);

	return 0;
}