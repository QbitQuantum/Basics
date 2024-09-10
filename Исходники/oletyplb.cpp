HRESULT CCmdTarget::GetTypeInfoOfGuid(LCID lcid, REFGUID guid,
	LPTYPEINFO* ppTypeInfo)
{
	USES_CONVERSION;

	AfxLockGlobals(CRIT_TYPELIBCACHE);

	HRESULT hr = TYPE_E_CANTLOADLIBRARY;
	CTypeLibCache* pTypeLibCache = GetTypeLibCache();
	LPTYPELIB pTypeLib = NULL;

	// If type info is already cached, just return it.
	if (pTypeLibCache->LookupTypeInfo(lcid, guid, ppTypeInfo))
	{
		hr = S_OK;
	}
	else
	{
		// If type library isn't already cached, try to locate it.
		if (!pTypeLibCache->Lookup(lcid, &pTypeLib))
		{
			// First, try getting the subclass to load the type library
			// (normally this goes through LoadRegTypeLib).

			if (FAILED(GetTypeLib(lcid, &pTypeLib)))
			{
				AFX_MANAGE_STATE(m_pModuleState);

				// If that failed, try loading the type library from our own
				// resources.

				TCHAR szPath[_MAX_PATH];
				GetModuleFileName(AfxGetInstanceHandle(), szPath, _MAX_PATH);

				if (FAILED(LoadTypeLib(T2COLE(szPath), &pTypeLib)))
					pTypeLib = NULL;
			}

			pTypeLibCache->Cache(lcid, pTypeLib);
		}

		// If we got a type library, extract the requested type info.
		if (pTypeLib != NULL)
		{
			hr = pTypeLib->GetTypeInfoOfGuid(guid, ppTypeInfo);
			pTypeLib->Release();
			pTypeLibCache->CacheTypeInfo(lcid, guid, *ppTypeInfo);
		}
	}

	AfxUnlockGlobals(CRIT_TYPELIBCACHE);

	return hr;
}