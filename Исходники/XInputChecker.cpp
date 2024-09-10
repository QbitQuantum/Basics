/*
================
XInputChecker::XInputChecker
================
*/
XInputChecker::XInputChecker() {
	// CoInit if needed
	HRESULT hr = CoInitialize( OG_NULL );
	bool bCleanupCOM = SUCCEEDED( hr );

	// Create WMI
	IWbemLocator* pIWbemLocator = OG_NULL;
	hr = CoCreateInstance( __uuidof( WbemLocator ), OG_NULL, CLSCTX_INPROC_SERVER, __uuidof( IWbemLocator ), ( LPVOID* )&pIWbemLocator );
	if( FAILED( hr ) || pIWbemLocator == OG_NULL ) {
		if( bCleanupCOM )
			CoUninitialize();
		return;
	}

	IEnumWbemClassObject* pEnumDevices = OG_NULL;
	IWbemServices* pIWbemServices = OG_NULL;
	IWbemClassObject* pDevices[20] = {0};

	BSTR bstrDeviceID = OG_NULL;
	BSTR bstrClassName = OG_NULL;
	BSTR bstrNamespace = OG_NULL;

	// Do just once
	do {
		bstrNamespace = SysAllocString( L"\\\\.\\root\\cimv2" );	if( bstrNamespace == OG_NULL )	break;
		bstrDeviceID = SysAllocString( L"DeviceID" );				if( bstrDeviceID == OG_NULL )	break;
		bstrClassName = SysAllocString( L"Win32_PNPEntity" );		if( bstrClassName == OG_NULL )	break;

		// Connect to WMI
		hr = pIWbemLocator->ConnectServer( bstrNamespace, OG_NULL, OG_NULL, 0L, 0L, OG_NULL, OG_NULL, &pIWbemServices );
		if( FAILED( hr ) || pIWbemServices == OG_NULL )
			break;

		// Switch security level to IMPERSONATE
		CoSetProxyBlanket( pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, OG_NULL,
						   RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, OG_NULL, 0 );

		// Get list of Win32_PNPEntity devices
		hr = pIWbemServices->CreateInstanceEnum( bstrClassName, 0, OG_NULL, &pEnumDevices );
		if( FAILED( hr ) || pEnumDevices == OG_NULL )
			break;

		// Loop over all devices
		DWORD uReturned = 0;
		VARIANT var;
		for( ; ; ) {
			// Get 20 at a time
			hr = pEnumDevices->Next( 10000, 20, pDevices, &uReturned );
			if( FAILED( hr ) || uReturned == 0 )
				break;

			for( int i = 0; i < uReturned; i++ ) {
				// For each device, get its device ID
				hr = pDevices[i]->Get( bstrDeviceID, 0L, &var, OG_NULL, OG_NULL );
				if( SUCCEEDED( hr ) && var.vt == VT_BSTR && var.bstrVal != OG_NULL ) {
					// Check if the device ID contains "IG_".  If it does, then it’s an XInput device
					// Unfortunately this information can not be found by just using DirectInput
					if( wcsstr( var.bstrVal, L"IG_" ) ) {
						// If it does, then get the VID/PID from var.bstrVal
						DWORD dwPid = 0, dwVid = 0;
						WCHAR* strVid = wcsstr( var.bstrVal, L"VID_" );
						if( strVid && swscanf( strVid, L"VID_%4X", &dwVid ) != 1 )
							dwVid = 0;
						WCHAR* strPid = wcsstr( var.bstrVal, L"PID_" );
						if( strPid && swscanf( strPid, L"PID_%4X", &dwPid ) != 1 )
							dwPid = 0;

						listIds.Alloc() = MAKELONG( dwVid, dwPid );
					}
				}
				SAFE_RELEASE( pDevices[i] );
			}
		}
	}
	while( 0 ); // Do just once

	if( bstrNamespace )
		SysFreeString( bstrNamespace );
	if( bstrDeviceID )
		SysFreeString( bstrDeviceID );
	if( bstrClassName )
		SysFreeString( bstrClassName );

	for( int i=0; i<20; i++ )
		SAFE_RELEASE( pDevices[i] );
	SAFE_RELEASE( pEnumDevices );
	SAFE_RELEASE( pIWbemLocator );
	SAFE_RELEASE( pIWbemServices );

	if( bCleanupCOM )
		CoUninitialize();
}