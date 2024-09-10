void ComErrorInfo(HRESULT hres)
{
	if(FAILED(hres))      
	{
		HRESULT hresult;
		HRESULT hr;
		GUID guidErrSrc;
		CComBSTR ErrDesc,ErrSrc;
		CComPtr<IErrorInfo>	pIErrorInfo;
		hr = hres;			// backup orig HRESULT
		hresult = GetErrorInfo(0,&pIErrorInfo);
		if (hresult == S_OK) 
		{
			USES_CONVERSION;
			pIErrorInfo->GetGUID(&guidErrSrc);
			pIErrorInfo->GetSource(&ErrSrc);
			pIErrorInfo->GetDescription(&ErrDesc);

			acutPrintf(OLE2W(ErrSrc));
		}
	}
}