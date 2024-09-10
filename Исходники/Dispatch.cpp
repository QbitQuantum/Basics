template <class T> HRESULT SepaControlDispatch<T>::SetErrorInfo(const wchar_t *pMessage) const
{
	ICreateErrorInfo *pCreateErrorInfo;
	IErrorInfo *pErrorInfo;

	if (SUCCEEDED(CreateErrorInfo(&pCreateErrorInfo)))
	{
		pCreateErrorInfo->SetDescription(_bstr_t(pMessage).Detach());
		pCreateErrorInfo->SetGUID(__uuidof(this));
		pCreateErrorInfo->SetSource(_bstr_t(TEXT("Separatista")).Detach());

		if (SUCCEEDED(pCreateErrorInfo->QueryInterface(IID_IErrorInfo, (LPVOID*)&pErrorInfo)))
		{
			::SetErrorInfo(0, pErrorInfo);
			pErrorInfo->Release();
		}
		pCreateErrorInfo->Release();
	}
	return DISP_E_EXCEPTION;
}