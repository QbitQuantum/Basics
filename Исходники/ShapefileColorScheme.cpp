STDMETHODIMP CShapefileColorScheme::get_Key(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	USES_CONVERSION;
	*pVal = OLE2BSTR(_key);

	return S_OK;
}