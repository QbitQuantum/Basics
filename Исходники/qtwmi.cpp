void QtWMI::OnQueryWMI()
{		
	CString strQuery;
	strQuery.Format(L"select * from Win32_%s", ui.cboWMIClasses->currentText().toStdWString().c_str() );	
	IWbemLocator *pLoc = NULL;	
	IWbemServices *pSvc = NULL;
	IEnumWbemClassObject* pEnumerator = NULL;
	IWbemClassObject *pclsObj=NULL;
	HRESULT hr=E_FAIL;

	do 
	{
		hr=CoCreateInstance(CLSID_WbemLocator,0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &pLoc);
		if (FAILED(hr) )		break;

		hr=pLoc->ConnectServer(	_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
		if (FAILED(hr) )		break;

		hr=CoSetProxyBlanket( pSvc,  RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, 
			RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE );
		if (FAILED(hr) )		break;

		hr=pSvc->ExecQuery( _bstr_t(L"WQL"),  bstr_t(strQuery), 
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,  NULL, &pEnumerator);
		if (FAILED(hr) )		break;

		ULONG		uReturn=0;
		variant_t		vtProp;	
		vtProp.Clear();						
		SAFEARRAY* psaNames=NULL;
		LONG nLower=0, nUpper=0;		
		_bstr_t		PropName;
		CString s;

		while (pEnumerator)
		{
			pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if(!uReturn)     break;   

			hr=pclsObj->GetNames(NULL, WBEM_FLAG_ALWAYS | WBEM_FLAG_NONSYSTEM_ONLY, NULL, &psaNames);
			if (hr==WBEM_S_NO_ERROR )
			{
				nLower=nUpper=0;

				SafeArrayGetLBound(psaNames, 1, &nLower);
				SafeArrayGetUBound(psaNames, 1, &nUpper);
				ui.lbDebug->clear();

				for (long i = nLower; i <= nUpper; i++) 
				{					
					SafeArrayGetElement(psaNames, &i, &PropName);	
					s.Format(L"%s", PropName);							
					hr = pclsObj->Get(s, 0, &vtProp, 0, 0);					
					if (hr==WBEM_S_NO_ERROR)																
						DisplayVariantValues(s, vtProp);	
					vtProp.Clear();						
				}					
			}
			if (psaNames)
				::SafeArrayDestroy(psaNames);	
			SAFE_RELEASE(pclsObj);	
		}		

	} while (0);

	SAFE_RELEASE(pEnumerator);
	SAFE_RELEASE(pclsObj);	
	SAFE_RELEASE(pSvc);
	SAFE_RELEASE(pLoc);
}