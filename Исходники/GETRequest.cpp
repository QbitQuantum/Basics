HRESULT GETRequest::perform() {
	wstring rangeProperty;
	wostringstream ss;
	BOOL  bResults = FALSE;

	if (! this->hRequest)
		return E_INVALIDARG;

	if (this->offset > 0 && this->length > 0) {
		ss<<L"Range: bytes="<<(int)this->offset<<L"-"<<(int)(this->offset+this->length);
		rangeProperty = ss.str();
		WinHttpAddRequestHeaders(this->hRequest, rangeProperty.c_str(), (DWORD)-1, WINHTTP_ADDREQ_FLAG_REPLACE|WINHTTP_ADDREQ_FLAG_ADD);
	}

	bResults = WinHttpSendRequest(this->hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

	if (! bResults)
		return E_FAIL;

	bResults = WinHttpReceiveResponse(this->hRequest, NULL);
	this->updateStatus();

	return S_OK;
}