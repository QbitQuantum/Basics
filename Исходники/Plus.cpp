STDMETHODIMP CPlus::GetOpName(BSTR *pOpName)
{
	*pOpName = A2BSTR(_T("Plus"));
	return S_OK;
}