HRESULT PROPFINDRequest::perform() {
	wstring depthProperty;
	wostringstream ss;
	BOOL  bResults = FALSE;
	int bodyLength = 0;

	if (! this->hRequest)
		return E_INVALIDARG;

	ss<<L"Depth: "<<depth;
	depthProperty = ss.str();
	
	//set Depth
	bodyLength = lstrlen(DEFAULT_PROPFIND)*sizeof(WCHAR);

	WinHttpAddRequestHeaders(this->hRequest, depthProperty.c_str(), (DWORD)-1, WINHTTP_ADDREQ_FLAG_REPLACE|WINHTTP_ADDREQ_FLAG_ADD);
	bResults = WinHttpSendRequest(this->hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, DEFAULT_PROPFIND, bodyLength, bodyLength, 0);

	if (! bResults)
		return E_FAIL;

	bResults = WinHttpReceiveResponse(this->hRequest, NULL);
	this->updateStatus();

	return S_OK;
}