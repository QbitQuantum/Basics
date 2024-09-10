BOOL CMediaVisDlg::EnumerateWrapped(LPCTSTR pszName, REFCLSID pCLSID, LPCTSTR pszCLSID)
{
	IWrappedPluginControl* pPlugin = NULL;

	HINSTANCE hRes = AfxGetResourceHandle();

	HRESULT hr = CoCreateInstance( pCLSID, NULL, CLSCTX_ALL,
		IID_IWrappedPluginControl, (void**)&pPlugin );

	AfxSetResourceHandle( hRes );

	if ( FAILED(hr) || pPlugin == NULL ) return FALSE;

	LPSAFEARRAY pArray = NULL;
	hr = pPlugin->Enumerate( &pArray );

	pPlugin->Release();

	if ( FAILED(hr) || pArray == NULL ) return FALSE;

	LONG pIndex[2] = { 0, 0 };
	SafeArrayGetUBound( pArray, 2, &pIndex[1] );

	if ( pIndex[1] < 0 )
	{
		SafeArrayDestroy( pArray );
		return TRUE;
	}

	for ( ; pIndex[1] >= 0; pIndex[1]-- )
	{
		CString strName, strPath;
		BSTR bsValue = NULL;

		strName = pszName;
		strName += L": ";

		pIndex[0] = 0;
		SafeArrayGetElement( pArray, pIndex, &bsValue );
		strName += bsValue;
		SysFreeString( bsValue );
		bsValue = NULL;

		pIndex[0] = 1;
		SafeArrayGetElement( pArray, pIndex, &bsValue );
		strPath = bsValue;
		SysFreeString( bsValue );
		bsValue = NULL;

		AddPlugin( strName, pszCLSID, strPath );
	}

	SafeArrayDestroy( pArray );

	return TRUE;
}