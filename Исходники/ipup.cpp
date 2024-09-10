static void HttpGet(const wxString& url, std::shared_ptr<wxString>& str)
{
	wxString host(url), req;

	// Usuń z adresu http[s]://
	if (host.substr(0, 4) == "http") {
		host = host.substr(7);
	}

	// Wyciągnij wszystko po pierwszym '/'
	const size_t idx = host.find("/");
	if (idx != wxString::npos) {
		req = host.substr(idx);
		host = host.substr(0, idx);
	}

	HINTERNET hInternet = InternetOpenW(ua.wc_str(), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (hInternet) {
		HINTERNET hConnect = InternetConnectW(hInternet, host.wc_str(), 80, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

		if (hConnect) {
			const wchar_t* parrAcceptTypes[] = { L"text/*", NULL };
			HINTERNET hRequest = HttpOpenRequestW(hConnect, L"GET", req.wc_str(), NULL, NULL, parrAcceptTypes, 0, 0);

			if (hRequest) {
				BOOL bRequestSent = HttpSendRequestW(hRequest, NULL, 0, NULL, 0);

				if (bRequestSent) {
					const int nBuffSize = 10240; // 10 kB
					char buff[nBuffSize];

					BOOL bKeepReading = true;
					DWORD dwBytesRead = -1;

					while (bKeepReading && dwBytesRead != 0) {
						bKeepReading = InternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);
						str->append(buff, dwBytesRead);
					}
				}

				InternetCloseHandle(hRequest);
			}

			InternetCloseHandle(hConnect);
		}

		InternetCloseHandle(hInternet);
	}
}