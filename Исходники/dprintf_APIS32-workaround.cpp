void initDebugEngine(void)
{
	if ( NULL != gDebugControl )
	{
		gDebugControl->Release();
		gDebugControl = NULL;
	}
	if ( NULL != gDebugClient )
	{
		gDebugClient->Release();
		gDebugClient = NULL;
	}

	{
		HRESULT hResult = S_FALSE;
		hResult = DebugCreate( __uuidof(IDebugClient), (PVOID *)&gDebugClient );
		if ( FAILED(hResult) )
		{
			dprintf( "get IDebugClient fail\n" );
			return;
		}

		if ( NULL != gDebugClient )
		{
			hResult = gDebugClient->QueryInterface( __uuidof(IDebugControl), (PVOID *)&gDebugControl );
			if ( FAILED(hResult) )
			{
				dprintf( "get IDebugControl fail\n" );
			}
		}
	}
}