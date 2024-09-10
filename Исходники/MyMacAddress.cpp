int MyMacAddress::WMI_GetMacAddress(int iQueryType, int iSize)
{
	ZeroMemory(PermanentAddress, sizeof(PermanentAddress));
	ZeroMemory(MACAddress, sizeof(MACAddress));
	HRESULT hres;  	int	iTotal = 0;
	if( (iQueryType  < 0) || (iQueryType >= sizeof(szWQLQuery)/sizeof(T_WQL_QUERY)) ) 
	{  		
		return -1;
	}    	
	hres = CoInitializeEx( NULL, COINIT_MULTITHREADED); 
	if( FAILED(hres) )      
	{          
		return -2; 
	}        
	hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if( FAILED(hres))
	{          
		CoUninitialize();
		return -2;      
	}        	
	IWbemLocator *pLoc = NULL;
	hres = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast <LPVOID*>(&pLoc));
	if( FAILED(hres))
	{  		
		CoUninitialize();
		return -2;      
	}
	IWbemServices *pSvc = NULL;
	hres = pLoc->ConnectServer(_bstr_t( L"ROOT\\CIMV2" ), NULL, NULL, NULL, 0, NULL, NULL, &pSvc);
	if( FAILED(hres))      
	{  		
		pLoc->Release();           
		CoUninitialize();          
		return -2;      
	}    	
	// 设置请求代理的安全级别
	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if(FAILED(hres))
	{          
		pSvc->Release();
		pLoc->Release(); 
		CoUninitialize();  
		return -2;      
	}       
	IEnumWbemClassObject *pEnumerator = NULL;
	hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t( szWQLQuery[iQueryType].szSelect), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);  	
	if(FAILED(hres)) 
	{          
		pSvc->Release();
		pLoc->Release();  
		CoUninitialize();         
		return -3;      
	}        
	while(pEnumerator)
	{  		
		IWbemClassObject *pclsObj = NULL;
		ULONG uReturn = 0;    	
		if(iTotal >= iSize)  
		{  			
			break;  	
		}           
		pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);            
		if( uReturn == 0 )         
		{              
			break;
		}    		
		VARIANT	vtProperty;  	
		TCHAR szProperty[128]; 
		// 获取网卡范例ID		
		VariantInit( &vtProperty);	  	
		pclsObj->Get( szWQLQuery[iQueryType].szProperty, 0, &vtProperty, NULL, NULL );  
		StringCchCopy( szProperty, sizeof(szProperty)/sizeof(TCHAR), W2T(vtProperty.bstrVal) );  
		VariantClear( &vtProperty );    			
		if( GetPNPDeviceID( szProperty))  	
		{  			
			iTotal++;  		
		}  		  		
		pclsObj->Release();  
	}
	// 释放资源  
	pEnumerator->Release(); 
	pSvc->Release();     
	pLoc->Release();   
	CoUninitialize();     
	return iTotal;  
}