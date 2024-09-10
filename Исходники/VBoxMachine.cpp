CUniString vboxFormatError(HRESULT hr)
{
	// Get error info
	Simple::CAutoPtr<IErrorInfo, SRefCounted> spErrorInfo;
	GetErrorInfo(0, &spErrorInfo);

	CUniString str;
	if (spErrorInfo)
	{
		BSTR bstr=NULL;
		spErrorInfo->GetDescription(&bstr);
		str=bstr;
		SysFreeString(bstr);
	}
	else
	{
		str=FormatError(hr);
	}

	return str;
}