HRESULT SetupForIsXInputDevice()
{
	IWbemLocator *pIWbemLocator = NULL;
	IEnumWbemClassObject *pEnumDevices = NULL;
	IWbemClassObject *pDevices[20] = {0};
	IWbemServices *pIWbemServices = NULL;
	BSTR bstrNamespace = NULL;
	BSTR bstrDeviceID = NULL;
	BSTR bstrClassName = NULL;
	DWORD uReturned = 0;
	BOOL bIsXinputDevice = FALSE;
	UINT iDevice = 0;
	VARIANT var;
	HRESULT hr;

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	bCleanupCOM = SUCCEEDED(hr);
	
	// Create WMI
	hr = CoCreateInstance( &CLSID_WbemContext,
		NULL,
		CLSCTX_INPROC_SERVER,
		&IID_IWbemContext,
		(LPVOID*) &pIWbemLocator);
	if( FAILED(hr) || pIWbemLocator == NULL )
		goto bail;

	bstrNamespace = SysAllocString( L"\\\\.\\root\\cimv2" );if( bstrNamespace == NULL ) goto bail;
	bstrClassName = SysAllocString( L"Win32_PNPEntity" );   if( bstrClassName == NULL ) goto bail;
	bstrDeviceID  = SysAllocString( L"DeviceID" );          if( bstrDeviceID == NULL )  goto bail;

	// Connect to WMI 	
	hr = IWbemLocator_ConnectServer(pIWbemLocator, bstrNamespace, NULL, NULL, NULL, 
		0L, NULL, NULL, &pIWbemServices );

	if( FAILED(hr) || pIWbemServices == NULL )
		goto bail;

	// Switch security level to IMPERSONATE
	CoSetProxyBlanket( (IUnknown *)pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, 
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE );                    

	hr = IWbemServices_CreateInstanceEnum( pIWbemServices, bstrClassName, 0, NULL, &pEnumDevices ); 
	if( FAILED(hr) || pEnumDevices == NULL )
		goto bail;

	// Loop over all devices
	for(;;)
	{
		// Get 20 at a time		
		hr = IEnumWbemClassObject_Next( pEnumDevices, 10000, 20, pDevices, &uReturned );
		if( FAILED(hr) || 
			uReturned == 0 )
			break;

		for( iDevice=0; iDevice<uReturned; iDevice++ )
		{
			// For each device, get its device ID
			hr = IWbemClassObject_Get( pDevices[iDevice], bstrDeviceID, 0L, &var, NULL, NULL );
			if( SUCCEEDED( hr ) && var.vt == VT_BSTR && var.bstrVal != NULL )
			{
				// Check if the device ID contains "IG_".  If it does, then it's an XInput device
				// This information can not be found from DirectInput 
				if( wcsstr( var.bstrVal, L"IG_" ) )
				{
					// If it does, then get the VID/PID from var.bstrVal
					DWORD dwPid = 0, dwVid = 0;
					WCHAR* strVid;
					WCHAR* strPid;
					DWORD dwVidPid;
					XINPUT_DEVICE_NODE* pNewNode;

					strVid = wcsstr( var.bstrVal, L"VID_" );
					if( strVid && swscanf( strVid, L"VID_%4X", &dwVid ) != 1 )
						dwVid = 0;
					strPid = wcsstr( var.bstrVal, L"PID_" );
					if( strPid && swscanf( strPid, L"PID_%4X", &dwPid ) != 1 )
						dwPid = 0;

					dwVidPid = MAKELONG( dwVid, dwPid );

					// Add the VID/PID to a linked list
					pNewNode = malloc(sizeof(XINPUT_DEVICE_NODE));
					if( pNewNode )
					{
						pNewNode->dwVidPid = dwVidPid;
						pNewNode->pNext = (struct XINPUT_DEVICE_NODE *)g_pXInputDeviceList;
						g_pXInputDeviceList = pNewNode;
					}
				}
			}
			SAFE_RELEASE( pDevices[iDevice] );
		}
	}

bail:
	if(bstrNamespace)
		SysFreeString(bstrNamespace);
	if(bstrDeviceID)
		SysFreeString(bstrDeviceID);
	if(bstrClassName)
		SysFreeString(bstrClassName);
	for( iDevice=0; iDevice<20; iDevice++ )
		SAFE_RELEASE( pDevices[iDevice] );
	SAFE_RELEASE( pEnumDevices );
	SAFE_RELEASE( pIWbemLocator );
	SAFE_RELEASE( pIWbemServices );

	return hr;
}