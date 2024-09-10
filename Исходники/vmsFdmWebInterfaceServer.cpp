BOOL vmsFdmWebInterfaceServer::ProcessRequest(vmsHttpRequest &request, vmsHttpResponse &response)
{
	
	if (lstrcmpiA (request.get_RequestType (), "GET"))
		return FALSE;

	CString strU = AfxGetApp ()->GetProfileString (_T("Network"), _T("Login")), 
		strP = AfxGetApp ()->GetProfileString (_T("Network"), _T("Password"));
	
	CString strAuth = strU + ":" + strP;
#ifdef UNICODE
	_bstr_t bstrAuth((LPCWSTR)strAuth);
#else
	_bstr_t bstrAuth((LPCSTR)strAuth);
#endif

	if (strU.IsEmpty () == FALSE && 
			lstrcmpA (request.get_Auth (), (LPCSTR)bstrAuth))
	{
		response.set_ResponseCode ("401 Authorization Required");
		return FALSE;
	}

	LPCSTR pszRes = request.get_ResourcePath ();

	if (lstrcmpA (pszRes, "/") == 0)
		return RequestRootPage (response);

	if (strncmp (pszRes, "/adddownload.req?", lstrlenA ("/adddownload.req?")) == 0)
		return RequestCreateNewDownload (pszRes, response);

	if (strncmp (pszRes, "/compdlds.req", lstrlenA ("/compdlds.req")) == 0)
		return RequestListOfCompletedDownloads (pszRes, response);

	response.set_ResponseCode ("404 Not Found");
	return FALSE;
}