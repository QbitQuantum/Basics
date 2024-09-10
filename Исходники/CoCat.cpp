STDMETHODIMP CoCat::SetName(BSTR name)
{
	SysReAllocString(&name_, name);
	return S_OK;
}