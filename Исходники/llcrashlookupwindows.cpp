LLCrashLookupWindows::LLCrashLookupWindows()
	: LLCrashLookup()
	, m_pDbgClient(NULL)
	, m_pDbgControl(NULL)
	, m_pDbgSymbols(NULL)
	, m_pDbgClient4(0)
{
	CoInitialize(NULL);

	// Create the base IDebugClient object and then query it for the class instances we're interested in
	HRESULT hRes = DebugCreate(__uuidof(IDebugClient), (void**)&m_pDbgClient);
	if (SUCCEEDED(hRes))
	{
		hRes = m_pDbgClient->QueryInterface(__uuidof(IDebugControl4), (void**)&m_pDbgControl);
		if (FAILED(hRes))
			return;
		hRes = m_pDbgClient->QueryInterface(__uuidof(IDebugSymbols2), (void**)&m_pDbgSymbols);
		if (FAILED(hRes))
			return;

		m_pDbgClient->QueryInterface( __uuidof(IDebugClient4), (void**)&m_pDbgClient4 );
	}
}