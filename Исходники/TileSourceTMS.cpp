STDMETHODIMP CTileSourceTMS::get_url( BSTR *pUrl )
{
	SysFreeStringHelper( *pUrl );
	std::string stdStr= getOrCreateInnerObject()->url().get().getString();
	*pUrl = SysAllocString( CString ( stdStr.data() ) );
	return S_OK;
}