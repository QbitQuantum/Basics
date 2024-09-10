BOOL HttpRequest(HTTPREQ* req, const wchar_t* url, const wchar_t* header, DWORD header_length, const char* body, DWORD body_length)
{
	BOOL ret = FALSE;
	req->internet = WinHttpOpen(NULL, NULL, NULL, NULL, NULL);
	if (req->internet != NULL)
	{
		URL_COMPONENTS urlinfo = {0};
		urlinfo.dwStructSize = sizeof(URL_COMPONENTS);
		urlinfo.dwSchemeLength    = (DWORD)-1;
		urlinfo.dwUserNameLength  = (DWORD)-1;
		urlinfo.dwHostNameLength  = (DWORD)-1;
		urlinfo.dwUrlPathLength   = (DWORD)-1;
		urlinfo.dwExtraInfoLength = (DWORD)-1;
		urlinfo.dwPasswordLength  = (DWORD)-1;
		if (WinHttpCrackUrl(url, wcslen(url), 0, &urlinfo))
		{
			if (WinHttpSetTimeouts(req->internet, req->resolveTimeout, req->connectTimeout, req->sendTimeout, req->receiveTimeout))
			{
				TCHAR* host = new TCHAR[urlinfo.dwHostNameLength + 1];
				wmemset(host, 0, urlinfo.dwHostNameLength + 1);
				StrCpyN(host, urlinfo.lpszHostName, urlinfo.dwHostNameLength + 1);
				req->connect = WinHttpConnect(req->internet, host, urlinfo.nPort, 0);
				if (req->connect != NULL)
				{
					if (body == NULL || body_length == 0)
						req->request = WinHttpOpenRequest(req->connect, L"GET", urlinfo.lpszUrlPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
					else
						req->request = WinHttpOpenRequest(req->connect, L"POST", urlinfo.lpszUrlPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

					if (req->request != NULL)
					{						
						if (WinHttpSendRequest(req->request, header, header_length, (void*)body, body_length, body_length, 0) && WinHttpReceiveResponse(req->request, 0))
						{
							TCHAR status[16] = {0};
							DWORD size = sizeof(status);
							if (WinHttpQueryHeaders(req->request, WINHTTP_QUERY_STATUS_CODE, NULL, status, &size, 0))
							{
								if (StrCmp(status, L"200") == 0)
								{
									char buffer[4096] = {0};
									DWORD length = 0;
									
									while (TRUE)
									{
										if (WinHttpReadData(req->request, buffer, sizeof(buffer), &length) && length > 0)
										{
											AppendBuffer(&req->buffer, req->dataLength, req->bufferLength, buffer, length);
											length = 0;
										}
										else
											break;
									}				

									ret = TRUE;
								}
							}
						}
					}
				}

				SAFE_DELETE_ARRAY(host);
			}
		}
	}
	
	return ret;
}