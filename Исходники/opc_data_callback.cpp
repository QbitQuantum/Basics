	//*
	STDMETHODIMP data_callback::QueryInterface( REFIID iid, LPVOID* ppInterface)
	{
		if ( ppInterface == NULL)
		{
			return E_INVALIDARG;
		}

#if DEBUG_PRINT
		{
			cotask_holder str;
			if ( SUCCEEDED( StringFromIID( iid, str.addr() ) ) )
			{
				DWPRINT( L"data_callback::QueryInterface( %s )\n", str.get() );
			}
		}

#endif

		if ( iid == IID_IUnknown )
		{
			*ppInterface = (IUnknown*) this;
		} else if ( iid == IID_IOPCDataCallback)
		{
			*ppInterface = (IOPCDataCallback*) this;
		} else
		{
			*ppInterface = NULL;
			return E_NOINTERFACE;
		}

		AddRef();
		return S_OK;
	}