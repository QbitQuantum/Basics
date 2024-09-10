static int listDevices(ClientElem_t *pClient) {
	int res = 0;
	int size = 8192;
	TCHAR *pszDevices = 0;
	long dwChars = 0;
	TCHAR *ptr;

	while (res == 0 && dwChars == 0) {
		pszDevices = malloc(size);
		if (pszDevices != 0) {
			dwChars = QueryDosDevice(NULL, pszDevices, size/sizeof(TCHAR));
			if (dwChars == 0) {
				DWORD err = GetLastError();
				if (err == ERROR_INSUFFICIENT_BUFFER) {
					size *= 2;
					if (size > 1024*1024) {
						SEND("ERROR cannot list com ports, QueryDosDevice too hungry");
						res = -1;
					} else {
						free(pszDevices);
					}
				} else {
					SEND("ERROR cannot list com ports, %i", err);
					res = -1;
				}
			}
		} else {
			SEND("ERROR cannot list com ports, out of memory");
			res = -1;
		}
	}
	ptr = pszDevices;
	while (res >= 0 && dwChars > 0) {
		int port;
		TCHAR *pTmp;
		if (swscanf(ptr, TEXT("COM%i"), &port) == 1) {
			SEND("COM%i", port);
		}
		pTmp = wcschr(ptr, 0);
		dwChars -= (DWORD)((pTmp - ptr) / sizeof(TCHAR) + 1);
		ptr = pTmp + 1;
	}
	free(pszDevices);
	return res;
}