BOOL AFXAPI AfxOleRegisterTypeLib(HINSTANCE hInstance, REFGUID tlid,
	LPCTSTR pszFileName, LPCTSTR pszHelpDir)
{
	USES_CONVERSION;

	BOOL bSuccess = FALSE;
	CString strPathName;
	TCHAR *szPathName = strPathName.GetBuffer(_MAX_PATH);
	::GetModuleFileName(hInstance, szPathName, _MAX_PATH);
	strPathName.ReleaseBuffer();
	LPTYPELIB ptlib = NULL;

	// If a filename was specified, replace final component of path with it.
	if (pszFileName != NULL)
	{
		int iBackslash = strPathName.ReverseFind('\\');
		if (iBackslash != -1)
			strPathName = strPathName.Left(iBackslash+1);
		strPathName += pszFileName;
	}

	if (SUCCEEDED(LoadTypeLib(T2COLE(strPathName), &ptlib)))
	{
		ASSERT_POINTER(ptlib, ITypeLib);

		LPTLIBATTR pAttr;
		GUID tlidActual = GUID_NULL;

		if (SUCCEEDED(ptlib->GetLibAttr(&pAttr)))
		{
			ASSERT_POINTER(pAttr, TLIBATTR);
			tlidActual = pAttr->guid;
			ptlib->ReleaseTLibAttr(pAttr);
		}

		// Check that the guid of the loaded type library matches
		// the tlid parameter.
		ASSERT(IsEqualGUID(tlid, tlidActual));

		if (IsEqualGUID(tlid, tlidActual))
		{
			// Register the type library.
			if (SUCCEEDED(RegisterTypeLib(ptlib,
					T2OLE((LPTSTR)(LPCTSTR)strPathName), T2OLE((LPTSTR)pszHelpDir))))
				bSuccess = TRUE;
		}

		RELEASE(ptlib);
	}
	else
	{
		TRACE1("Warning: Could not load type library from %s\n", (LPCTSTR)strPathName);
	}

	return bSuccess;
}