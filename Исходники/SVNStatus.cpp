STDMETHODIMP
CSVNStatus::get_name(BSTR *pVal)
{
	*pVal = A2BSTR(pszName);
	return S_OK;
}