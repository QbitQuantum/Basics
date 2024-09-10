	//*
	void local_host::get_clsid( const CATID& cat_id, LPCOLESTR server_name, CLSID& server_id )
	{
#if defined _DEBUG && defined _CONSOLE
		wprintf( L"get_clsid( %s )\n", server_name );
#endif

		CATID Implist[1] = { cat_id };
		ATL::CComPtr<IEnumCLSID> iEnum;
		HRESULT result = root_->EnumClassesOfCategories(1, Implist,0, NULL, &iEnum);
		if (FAILED(result))
		{
			throw opc_exception( result, OLESTR("Failed to get enum for categeories") );
		}

		GUID glist;
		ULONG actual;
		while((result = iEnum->Next(1, &glist, &actual)) == S_OK)
		{
			cotask_holder<OLECHAR> progID;

			HRESULT res = ProgIDFromCLSID(glist, progID.addr());			
			if(FAILED(res))
			{
				throw opc_exception( res, OLESTR("Failed to get ProgId from ClassId") );
			}
			else 
			{
#if defined _DEBUG && defined _CONSOLE
				wprintf( L"progId = %s\n", progID );
#endif
				if ( lstrcmpW( progID.get(), server_name ) == 0 )
				{
					server_id = glist;

					return;					
				}																
			}
		}
	}