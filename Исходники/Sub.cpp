STDMETHODIMP CSub::GetOpName(BSTR *pOpName)
{
	*pOpName = A2BSTR(_T("Sub"));
	return S_OK;
}