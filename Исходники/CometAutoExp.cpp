//extern "C" {
HRESULT WINAPI DateTime_Evaluate( DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t maxlen, DWORD reserved )
{
	DATE Time;
	DWORDLONG address = GetAddress( pHelper, dwAddress);

	if( !ReadMem( pHelper, address, &Time) )
		return E_FAIL;

	if(Time == 0.)
	{
		strcpy(pResult, "zero");
		return S_OK;
	}
	if(Time == ( 65535. * 2147483647. ) || Time == (2147483647.))
	{
		strcpy(pResult, "invalid");
		return S_OK;
	}
	if(Time == ( 65535. * 2147483648. ) || Time == (2147483648.))
	{
		strcpy(pResult, "null");
		return S_OK;
	}

	CComBSTR strDate ;
	HRESULT hr = VarBstrFromDate(Time, LOCALE_USER_DEFAULT, 0, &strDate);
	if (FAILED(hr)) return hr;
	
	if(strDate != 0)
		WideCharToMultiByte(CP_ACP, 0, strDate, strDate.Length(), pResult, maxlen , NULL, NULL);

	return S_OK;
	
}