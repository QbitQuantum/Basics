BOOL COleDispatchDriver::CreateDispatch(REFCLSID clsid, COleException* pError)
{
	ASSERT(m_lpDispatch == NULL);

	m_bAutoRelease = TRUE;  // good default is to auto-release

	// create an instance of the object
	LPUNKNOWN lpUnknown = NULL;
	SCODE sc = CoCreateInstance(clsid, NULL, CLSCTX_ALL | CLSCTX_REMOTE_SERVER,
		IID_IUnknown, (LPLP)&lpUnknown);
	if (sc == E_INVALIDARG)
	{
		// may not support CLSCTX_REMOTE_SERVER, so try without
		sc = CoCreateInstance(clsid, NULL, CLSCTX_ALL & ~CLSCTX_REMOTE_SERVER,
			IID_IUnknown, (LPLP)&lpUnknown);
	}
	if (FAILED(sc))
		goto Failed;

	// make sure it is running
	sc = OleRun(lpUnknown);
	if (FAILED(sc))
		goto Failed;

	// query for IDispatch interface
	m_lpDispatch = QUERYINTERFACE(lpUnknown, IDispatch);
	if (m_lpDispatch == NULL)
		goto Failed;

	lpUnknown->Release();
	ASSERT(m_lpDispatch != NULL);
	return TRUE;

Failed:
	RELEASE(lpUnknown);
	if (pError != NULL)
		pError->m_sc = sc;
	TRACE1("Warning: CreateDispatch returning scode = %s.\n",
		AfxGetFullScodeString(sc));
	return FALSE;
}