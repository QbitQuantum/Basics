STDMETHODIMP BallEx::get_Name(BSTR *pVal)
{
	*pVal = SysAllocString(L"Ball");
	return S_OK;
}