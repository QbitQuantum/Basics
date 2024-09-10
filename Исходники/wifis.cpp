int foo() {

  WindowsNdisApi* w = WindowsNdisApi::Create();
  std::vector<AccessPoint> apData;
  w->GetAccessPointData(apData);


  ///////////////////////////////////////////////////////////
	HANDLE hClient;
	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfConnInfo = NULL;
	PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;

	PWLAN_BSS_LIST pBssList=NULL;
	PWLAN_BSS_ENTRY  pBssEntry=NULL;
	WLAN_OPCODE_VALUE_TYPE opCode = wlan_opcode_value_type_invalid;

	DWORD dwResult = 0;
	DWORD dwMaxClient = 2;         
	DWORD dwCurVersion = 0;
	DWORD connectInfoSize = sizeof(WLAN_CONNECTION_ATTRIBUTES);

	int i;

	// Initialise the Handle
	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
	if (dwResult != ERROR_SUCCESS) 
	{    
		return 0;
	}

	// Get the Interface List
	dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
	if (dwResult != ERROR_SUCCESS) 
	{    
		return 0;
	}

	//Loop through the List to find the connected Interface
	PWLAN_INTERFACE_INFO pIfInfo = NULL;
	for (i = 0; i < (int) pIfList->dwNumberOfItems; i++) 
	{
		pIfInfo = (WLAN_INTERFACE_INFO *) & pIfList->InterfaceInfo[i];    
		if (pIfInfo->isState == wlan_interface_state_connected) 
		{
			pIfConnInfo = pIfInfo;
			break;
		}
	}

	if ( pIfConnInfo == NULL )
		return 0;

	// Query the Interface
	dwResult = WlanQueryInterface(hClient,&pIfConnInfo->InterfaceGuid,wlan_intf_opcode_current_connection,NULL,&connectInfoSize,(PVOID *) &pConnectInfo,&opCode);
	if (dwResult != ERROR_SUCCESS) 
	{    
		return 0;
	}

	// Scan the connected SSID
	dwResult = WlanScan(hClient, &pIfConnInfo->InterfaceGuid,
		                NULL/*&pConnectInfo->wlanAssociationAttributes.dot11Ssid*/,
						NULL, NULL);
	if (dwResult != ERROR_SUCCESS) 
	{    
		return 0;
	}

	// Get the BSS Entry
	dwResult = WlanGetNetworkBssList(hClient, &pIfConnInfo->InterfaceGuid,
		NULL /*&pConnectInfo->wlanAssociationAttributes.dot11Ssid */,
		dot11_BSS_type_any,
		TRUE, NULL, &pBssList);

	if (dwResult != ERROR_SUCCESS) 
	{    
		return 0;
	}

	// Get the RSSI value
	pBssEntry=&pBssList->wlanBssEntries[0];
	return pBssEntry->lRssi;
}