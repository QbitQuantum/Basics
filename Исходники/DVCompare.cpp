STDMETHODIMP CDVCompare::InterfaceSupportsErrorInfo(REFIID riid)
{
	CResourceSwapper rs( _Module.m_hInstResource );

	static const IID* arr[] = 
	{
		&IID_ICommand
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}