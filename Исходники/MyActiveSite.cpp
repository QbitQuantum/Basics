void MyActiveSite::Throw(TCHAR* errmsg, REFGUID refguid){
	LocRef<ICreateErrorInfo> pcerrinfo;
	LocRef<IErrorInfo> perrinfo;

	SysStr errMsg(errmsg);

	HRESULT hr = CreateErrorInfo(&pcerrinfo);
	if (FAILED(hr))
		return;
	
	pcerrinfo->SetDescription(errMsg);
	pcerrinfo->SetGUID(refguid);

	hr = pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID FAR*) &perrinfo);
	if (FAILED(hr))
		return;
	
	SetErrorInfo(0, perrinfo);
}