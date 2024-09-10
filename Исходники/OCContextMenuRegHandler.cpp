HRESULT OCContextMenuRegHandler::RegisterInprocServer(PCWSTR pszModule, const CLSID& clsid, PCWSTR pszFriendlyName, PCWSTR pszThreadModel)
{
	if (pszModule == NULL || pszThreadModel == NULL)
	{
		return E_INVALIDARG;
	}

	HRESULT hr;

	wchar_t szCLSID[MAX_PATH];
	StringFromGUID2(clsid, szCLSID, ARRAYSIZE(szCLSID));

	wchar_t szSubkey[MAX_PATH];

	// Create the HKCR\CLSID\{<CLSID>} key.
	hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), L"CLSID\\%s", szCLSID);
	if (SUCCEEDED(hr))
	{
		hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszFriendlyName);

		// Create the HKCR\CLSID\{<CLSID>}\InprocServer32 key.
		if (SUCCEEDED(hr))
		{
			hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey),
				L"CLSID\\%s\\InprocServer32", szCLSID);
			if (SUCCEEDED(hr))
			{
				// Set the default value of the InprocServer32 key to the 
				// path of the COM module.
				hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszModule);
				if (SUCCEEDED(hr))
				{
					// Set the threading model of the component.
					hr = SetHKCRRegistryKeyAndValue(szSubkey,
						L"ThreadingModel", pszThreadModel);
				}
			}
		}
	}

	return hr;
}