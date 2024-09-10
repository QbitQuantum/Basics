	static HRESULT WINAPI CreateDXGIFactory2_hook(UINT Flags, REFIID riid,  void **ppFactory)
	{
		if(ppFactory) *ppFactory = NULL;
		HRESULT ret = dxgihooks.CreateDXGIFactory2()(Flags, riid, ppFactory);
		
		if(SUCCEEDED(ret) && dxgihooks.m_EnabledHooks)
			RefCountDXGIObject::HandleWrap(riid, ppFactory);

		return ret;
	}