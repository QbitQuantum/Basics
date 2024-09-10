static char *
getWmiInfo (int mode)
{
	/* for more details about this wonderful API, see 
	http://msdn.microsoft.com/en-us/site/aa394138
	http://msdn.microsoft.com/en-us/site/aa390423
	http://msdn.microsoft.com/en-us/library/windows/desktop/aa394138%28v=vs.85%29.aspx
	http://social.msdn.microsoft.com/forums/en-US/vcgeneral/thread/d6420012-e432-4964-8506-6f6b65e5a451
	*/

	char *buffer = (char *) malloc (128);
	HRESULT hres;
	HRESULT hr;
	IWbemLocator *pLoc = NULL;
	IWbemServices *pSvc = NULL;
	IEnumWbemClassObject *pEnumerator = NULL;
	IWbemClassObject *pclsObj;
	ULONG uReturn = 0;

	hres =  CoInitializeEx (0, COINIT_APARTMENTTHREADED | COINIT_SPEED_OVER_MEMORY);

	if (FAILED (hres))
	{
		strcpy (buffer, "Error Code 0");
		return buffer;
	}

	hres =  CoInitializeSecurity (NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

	/* mysteriously failing after the first execution, but only when used as a plugin, skip it */
	/*if (FAILED (hres))
	{
		CoUninitialize ();
		strcpy (buffer, "Error Code 1");
		return buffer;
	}*/

	hres = CoCreateInstance (CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &pLoc);

	if (FAILED (hres))
	{
		CoUninitialize ();
		strcpy (buffer, "Error Code 2");
		return buffer;
	}

	hres = pLoc->ConnectServer (_bstr_t (L"root\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);

	if (FAILED (hres))
	{
		pLoc->Release ();
		CoUninitialize ();
		strcpy (buffer, "Error Code 3");
		return buffer;
	}

	hres = CoSetProxyBlanket (pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	if (FAILED (hres))
	{
		pSvc->Release ();
		pLoc->Release ();
		CoUninitialize ();
		strcpy (buffer, "Error Code 4");
		return buffer;
	}

	switch (mode)
	{
		case 0:
			hres = pSvc->ExecQuery (_bstr_t ("WQL"), _bstr_t ("SELECT * FROM Win32_OperatingSystem"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
			break;
		case 1:
			hres = pSvc->ExecQuery (_bstr_t ("WQL"), _bstr_t ("SELECT * FROM Win32_Processor"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
			break;
		case 2:
			hres = pSvc->ExecQuery (_bstr_t ("WQL"), _bstr_t ("SELECT * FROM Win32_VideoController"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
			break;

	}

	if (FAILED (hres))
	{
		pSvc->Release ();
		pLoc->Release ();
		CoUninitialize ();
		strcpy (buffer, "Error Code 5");
		return buffer;
	}

	while (pEnumerator)
	{
		hr = pEnumerator->Next (WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;
		switch (mode)
		{
			case 0:
				hr = pclsObj->Get (L"Caption", 0, &vtProp, 0, 0);
				break;
			case 1:
				hr = pclsObj->Get (L"Name", 0, &vtProp, 0, 0);
				break;
			case 2:
				hr = pclsObj->Get (L"Name", 0, &vtProp, 0, 0);
				break;
		}
		WideCharToMultiByte (CP_ACP, 0, vtProp.bstrVal, -1, buffer, SysStringLen (vtProp.bstrVal)+1, NULL, NULL);
		VariantClear (&vtProp);
    }

	pSvc->Release ();
	pLoc->Release ();
	pEnumerator->Release ();
	pclsObj->Release ();
	CoUninitialize ();
	return buffer;
}