bool CSMBiosTable::FetchSMBiosDataByCom( unsigned char ** p )
{
	BOOL bRet = FALSE;   
	HRESULT hres;   

	// Initialize COM.    
	hres =  CoInitializeEx( 0, COINIT_MULTITHREADED );    
	if( FAILED(hres) )   
	{   
		return FALSE;              // Program has failed.    
	}   

	// Obtain the initial locator to Windows Management    
	// on a particular host computer.    
	IWbemLocator *pLoc = 0;   
	hres = CoCreateInstance( CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &pLoc );   
	if( FAILED(hres) )   
	{   
		CoUninitialize();   
		return FALSE;       // Program has failed.    
	}   

	IWbemServices *pSvc = 0;   

	// Connect to the root\cimv2 namespace with the    z
	// current user and obtain pointer pSvc    
	// to make IWbemServices calls.    
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\WMI"), // WMI namespace    
		NULL,                    // User name    
		NULL,                    // User password    
		0,                       // Locale    
		NULL,                    // Security flags                     
		0,                       // Authority           
		0,                       // Context object    
		&pSvc                    // IWbemServices proxy    
		);                                 

	if( FAILED(hres) )   
	{   
		pLoc->Release();        
		CoUninitialize();   
		return FALSE;                // Program has failed.    
	}   

	// Set the IWbemServices proxy so that impersonation    
	// of the user (client) occurs.    
	hres = CoSetProxyBlanket(   
		pSvc,                         // the proxy to set    
		RPC_C_AUTHN_WINNT,            // authentication service    
		RPC_C_AUTHZ_NONE,             // authorization service    
		NULL,                         // Server principal name    
		RPC_C_AUTHN_LEVEL_CALL,       // authentication level    
		RPC_C_IMP_LEVEL_IMPERSONATE,  // impersonation level    
		NULL,                         // client identity     
		EOAC_NONE                     // proxy capabilities         
		);   

	if( FAILED(hres) )   
	{   
		pSvc->Release();   
		pLoc->Release();        
		CoUninitialize();   
		return FALSE;               // Program has failed.    
	}   

	IEnumWbemClassObject* pEnumerator = NULL;   
	hres = pSvc->CreateInstanceEnum( L"MSSMBios_RawSMBiosTables", 0, NULL, &pEnumerator);
	if( FAILED(hres) )   
	{   
		pSvc->Release();   
		pLoc->Release();        
		CoUninitialize();   
		return FALSE;               // Program has failed.    
	}   
	else   
	{    
		do   
		{   
			IWbemClassObject* pInstance = NULL;   
			ULONG dwCount = NULL;   

			hres = pEnumerator->Next( WBEM_INFINITE, 1, &pInstance, &dwCount);         
			if( SUCCEEDED(hres) )   
			{   
				VARIANT varBIOSData;   
				VariantInit(&varBIOSData);   
				CIMTYPE  type;   

				hres = pInstance->Get(bstr_t("SmbiosMajorVersion"),0,&varBIOSData,&type,NULL);   
				if( FAILED(hres) )   
				{   
					VariantClear(&varBIOSData);   
				}   
				else   
				{   
					m_smbiosbuffer.nSMBIOSMajorVersion = varBIOSData.iVal;   
					VariantInit(&varBIOSData);   
					hres = pInstance->Get( bstr_t("SmbiosMinorVersion"), 0, &varBIOSData, &type, NULL );   
					if( FAILED(hres) )   
					{   
						VariantClear( &varBIOSData );   
					}   
					else   
					{   
						m_smbiosbuffer.nSMBIOSMinorVersion = varBIOSData.iVal;   
						VariantInit(&varBIOSData);   
						hres = pInstance->Get( bstr_t("SMBiosData"), 0, &varBIOSData, &type, NULL );   
						if( SUCCEEDED(hres) )   
						{   
							if( ( VT_UI1 | VT_ARRAY  ) != varBIOSData.vt )   
							{   
							}   
							else   
							{   
								SAFEARRAY           *parray = NULL;   
								parray = V_ARRAY(&varBIOSData);   
								BYTE* pbData = (BYTE*)parray->pvData;   

								m_smbiosbuffer.nLength = parray->rgsabound[0].cElements;   
								(*p) = new unsigned char[m_smbiosbuffer.nLength];   
								memcpy_s( (*p), m_smbiosbuffer.nLength, pbData, m_smbiosbuffer.nLength );
								bRet = TRUE;   
							}   
						}   
						VariantClear( &varBIOSData );   
					}   
				}   
				break;   
			}   

		}while( hres == WBEM_S_NO_ERROR );   
	}   

	// Cleanup    
	// ========    
	pSvc->Release();   
	pLoc->Release();        
	CoUninitialize();   

	return bRet;  
}