bool SendFile(HANDLE hFile, const TCHAR* sUrl, const char* sVariableName, const char* sFileName) {
	if(!hFile) return false;
	bool result = false;
	LARGE_INTEGER lnSize;
	if(!GetFileSizeEx(hFile, &lnSize)){
		CloseHandle(hFile);
		return false;
	}
	DWORD nDataSize = lnSize.LowPart;
	if(!(nDataSize>0)) {
		CloseHandle(hFile);
		return false;
	}
	std::vector<char> pData(nDataSize);
	DWORD nReadSize = 0; 
	if(!ReadFile(hFile, (void*)&pData[0], nDataSize, &nReadSize, NULL) || !(nReadSize >0) || (nReadSize != nDataSize)) {
		CloseHandle(hFile);
		return false;
	}
	CloseHandle(hFile);

	TCHAR extraInfo[URL_PART_SIZE];
	TCHAR hostName[URL_PART_SIZE];
	TCHAR passwordSet[URL_PART_SIZE];
	TCHAR schemeUrl[URL_PART_SIZE];
	TCHAR fileUrlPath[URL_PART_SIZE];
	TCHAR userName[URL_PART_SIZE];

	URL_COMPONENTS aUrl;
	aUrl.dwStructSize=sizeof(URL_COMPONENTS);
	aUrl.dwHostNameLength=URL_PART_SIZE;
	aUrl.dwPasswordLength=URL_PART_SIZE;
	aUrl.dwSchemeLength=URL_PART_SIZE;
	aUrl.dwUrlPathLength=URL_PART_SIZE;
	aUrl.dwUserNameLength=URL_PART_SIZE;
	aUrl.dwExtraInfoLength=URL_PART_SIZE;
	aUrl.lpszExtraInfo=extraInfo;
	aUrl.lpszHostName=hostName;
	aUrl.lpszPassword=passwordSet;
	aUrl.lpszScheme=schemeUrl;
	aUrl.lpszUrlPath=fileUrlPath;
	aUrl.lpszUserName=userName;

	PCTSTR rgpszAcceptTypes[] = {_T("text/*"), NULL};

	if(!InternetCrackUrl(sUrl, 0, 0, &aUrl)) return false;
	HINTERNET hInternet = InternetOpen(TEXT("swas"),INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(hInternet) {
		HINTERNET hConnect = InternetConnect(hInternet,aUrl.lpszHostName, aUrl.nPort, aUrl.lpszUserName, aUrl.lpszHostName, INTERNET_SERVICE_HTTP, 0, 0);
		if(hConnect){
			HINTERNET hReq = HttpOpenRequest(hConnect, TEXT("POST"), aUrl.lpszUrlPath, NULL, NULL, rgpszAcceptTypes, 
				INTERNET_FLAG_NO_UI | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0);
			if(hReq) {
				

				//see http://stackoverflow.com/questions/6407755/how-to-send-a-zip-file-using-wininet-in-my-vc-application
				char sBoundary[HEADERS_MAX_SIZE];
				if(GenerateBoundary(sBoundary, HEADERS_MAX_SIZE, sFileName)) {
					std::stringstream osHeaders;
					std::stringstream osHeadPart;
					std::stringstream osTailPart;
					const char const endl[] = "\r\n"; 

					osHeaders<<"Content-Type: multipart/form-data; boundary="<<sBoundary;

					osHeadPart<<"--"<<sBoundary<<endl;
					osHeadPart<<"Content-Disposition: form-data; ";
					osHeadPart<<"name=\""<<((NULL != sVariableName)?sVariableName:"filearg")<<"\"; ";
					osHeadPart<<"filename=\""<<((NULL != sFileName)?sFileName:"Chrome Tabs")<<"\""<<endl;
					osHeadPart<<"Content-Type: application/octet-stream"<<endl;
					osHeadPart<<endl;

					osTailPart<<endl<<"--"<<sBoundary<<"--"<<endl;

					std::string sHeaders = osHeaders.str();
					std::string sHeadPart = osHeadPart.str();
					std::string sTailPart = osTailPart.str();

					HttpAddRequestHeadersA(hReq, sHeaders.c_str(), -1, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD); 
				
					INTERNET_BUFFERS bufferIn;

					memset(&bufferIn, 0, sizeof(INTERNET_BUFFERS));

					bufferIn.dwStructSize  = sizeof(INTERNET_BUFFERS);
					bufferIn.dwBufferTotal = sHeadPart.length() + nDataSize + sTailPart.length();
					DWORD bytesWritten;
					if(HttpSendRequestEx(hReq, &bufferIn, NULL, HSR_INITIATE, 0)) {
						InternetWriteFile(hReq, (const void*)sHeadPart.c_str(), sHeadPart.length(), &bytesWritten);

						InternetWriteFile(hReq, (const void*)&pData[0], nDataSize, &bytesWritten);
						// or a while loop for call InternetWriteFile every 1024 bytes...

						InternetWriteFile(hReq, (const void*)sTailPart.c_str(), sTailPart.length(), &bytesWritten);
						result = true;
					}else{
						ShowAnError(GetLastError(), TEXT("Network error"), TEXT("Wininet"));
					}
				}
				HttpEndRequest(hReq, NULL, HSR_INITIATE, 0);

			}else{
				ShowAnError(GetLastError(), TEXT("Network error"), TEXT("Wininet"));
			}
		}else{
			ShowAnError(GetLastError(), TEXT("Network error"), TEXT("Wininet"));
		}
		InternetCloseHandle(hInternet);
	}
	return result;
}