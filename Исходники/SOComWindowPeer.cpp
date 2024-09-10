STDMETHODIMP SOComWindowPeer::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISOComWindowPeer,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
#if defined(_MSC_VER) && (_MSC_VER >= 1300)
		if (InlineIsEqualGUID(*arr[i],riid))
#else
		if (::ATL::InlineIsEqualGUID(*arr[i],riid))
#endif
			return S_OK;
	}
	return S_FALSE;
}