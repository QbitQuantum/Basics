int InternetDownloadFile (char *szUrl, char *cookie, char *userAgent, TCHAR **szData) 
{
	if (userAgent == NULL || userAgent[0] == 0)
		userAgent = "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)";
	
	NETLIBHTTPHEADER headers[5];
	headers[0].szName = "User-Agent";
	headers[0].szValue = userAgent;
	headers[1].szName = "Cache-Control";
	headers[1].szValue = "no-cache";
	headers[2].szName = "Pragma";
	headers[2].szValue = "no-cache";
	headers[3].szName = "Connection";
	headers[3].szValue = "close";
	headers[4].szName = "Cookie";
	headers[4].szValue = cookie;

	// initialize the netlib request
	NETLIBHTTPREQUEST nlhr = { sizeof(nlhr) };
	nlhr.requestType = REQUEST_GET;
	nlhr.flags = NLHRF_DUMPASTEXT | NLHRF_HTTP11 | NLHRF_PERSISTENT | NLHRF_REDIRECT;
	nlhr.szUrl = szUrl;
	nlhr.nlc = hNetlibHttp;
	nlhr.headers = headers;
	nlhr.headersCount = SIZEOF(headers);

	if (cookie == NULL || cookie[0] == 0)
		--nlhr.headersCount;

	// download the page
	NETLIBHTTPREQUEST *nlhrReply = (NETLIBHTTPREQUEST*)CallService(MS_NETLIB_HTTPTRANSACTION, (WPARAM)hNetlibUser, (LPARAM)&nlhr);
	if (nlhrReply == 0) {
	// if the data does not downloaded successfully (ie. disconnected), then return 1000 as error code
		*szData = (TCHAR*)mir_alloc(512);
		// store the error code in szData
		_tcscpy(*szData, _T("NetLib error occurred!!"));
		hNetlibHttp = NULL;
		return NLHRF_REDIRECT;
	}

	// if the recieved code is 200 OK
	int result;
	if (nlhrReply->resultCode == 200) {
		if (nlhrReply->dataLength) {
			bool bIsUtf = false;
			result = 0;

			// allocate memory and save the retrieved data
			int i = findHeader(nlhrReply, "Content-Type");
			if (i != -1 && strstr(_strlwr((char*)nlhrReply->headers[i].szValue), "utf-8"))
				bIsUtf = true;
			else {
				char* end = nlhrReply->pData;
				for (;;) {
					char* beg = strstr(end, "<meta");
					if (beg == NULL) break;
					else {
						char* method, tmp;
						end = strchr(beg, '>');
						tmp = *end; *end = 0;

						method = strstr(beg, "http-equiv=\"");
						if (method && _strnicmp(method+12, "Content-Type", 12) == 0 && strstr(method, "utf-8")) {
							bIsUtf = true;
							break;
						}
						else *end = tmp;
					}
				}
			}

			TCHAR *retVal = NULL;
			if (bIsUtf)
				retVal = mir_utf8decodeT( nlhrReply->pData );
			if (retVal == NULL)
				retVal = mir_a2t(nlhrReply->pData);
			*szData = retVal;
		}
		else result = DATA_EMPTY;
	}
	// return error code if the recieved code is neither 200 OK nor 302 Moved
	else {
		*szData = (TCHAR*)mir_alloc(512);
		// store the error code in szData
		mir_sntprintf(*szData, 512, _T("Error occured! HTTP Error: %i\n"), nlhrReply->resultCode);
		result = (int)nlhrReply->resultCode;
	}

	hNetlibHttp = nlhrReply->nlc;
	// make a copy of the retrieved data, then free the memory of the http reply
	CallService(MS_NETLIB_FREEHTTPREQUESTSTRUCT,0, (LPARAM)nlhrReply);
	return result;
}