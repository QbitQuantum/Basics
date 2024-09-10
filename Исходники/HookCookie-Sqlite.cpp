VOID  CALLBACK HCInternetStatusCallback(
									  __in HINTERNET hInternet,
									  __in_opt DWORD_PTR dwContext,
									  __in DWORD dwInternetStatus,
									  __in_opt LPVOID lpvStatusInformation,
									  __in DWORD dwStatusInformationLength
									  )
{



	if ( INTERNET_STATUS_REDIRECT == dwInternetStatus )
	{
		LPCSTR pszRedirectUrl = (LPCSTR)lpvStatusInformation;
		CStringA strRedirectUrl;
		strRedirectUrl = pszRedirectUrl;
		CStringA strOrgUrl;
		UrlRecorder.GetRecordData(hInternet,&strOrgUrl);
		UrlRecorder.SetRecordData(hInternet,strRedirectUrl);


		CHAR chCookieData[2000]={0};
		CommonGetCookie(strRedirectUrl,chCookieData,1999,FALSE);

		CStringA strCookieHeader;
		strCookieHeader = "Cookie: ";
		strCookieHeader += chCookieData;

		BOOL bRes = HttpAddRequestHeadersA(hInternet,strCookieHeader.GetBuffer(),strCookieHeader.GetLength(),HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
		
		int a=0;

	}

	if ( INTERNET_STATUS_REQUEST_COMPLETE == dwInternetStatus  )
	{
		CStringA strInternetUrl;
		UrlRecorder.GetRecordData(hInternet,&strInternetUrl);

		char chRecvCookie[2000];
		DWORD dwRecvCookieLen = 2000;
		DWORD dwCookieIndex = 0;
		while(HttpQueryInfoA(hInternet,HTTP_QUERY_SET_COOKIE,chRecvCookie,&dwRecvCookieLen,&dwCookieIndex))
		{

			CommonSetCookie(strInternetUrl,chRecvCookie);

			if ( ERROR_HTTP_HEADER_NOT_FOUND ==  dwCookieIndex)
			{
				break;
			}
			dwRecvCookieLen = 2000;
		}
	}

	INTERNET_STATUS_CALLBACK pOrgCallback = NULL;
	CallbackRecorder.GetRecordData(hInternet,&pOrgCallback);

	if (pOrgCallback)
	{
		pOrgCallback(hInternet,
			dwContext,
			dwInternetStatus,
			lpvStatusInformation,
			dwStatusInformationLength
			);
	}


}