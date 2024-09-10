void KPR_system_getWifiInfo(xsMachine* the)
{
    DWORD dwResult = 0;
    HANDLE hClient = NULL;
    DWORD dwMaxClient = 2; 
    DWORD dwCurVersion = 0;
    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
    int i;
    PWLAN_INTERFACE_INFO pIfInfo = NULL;
    DWORD connectInfoSize = sizeof(WLAN_CONNECTION_ATTRIBUTES);
    PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;
    WLAN_OPCODE_VALUE_TYPE opCode = wlan_opcode_value_type_invalid;
    ULONG length;
	xsVars(1);
    dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient); 
    if (dwResult != ERROR_SUCCESS) 
    	goto bail;
	dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList); 
    if (dwResult != ERROR_SUCCESS)
    	goto bail;
    for (i = 0; i < (int) pIfList->dwNumberOfItems; i++) {
		pIfInfo = (WLAN_INTERFACE_INFO *) &pIfList->InterfaceInfo[i];
   		if (pIfInfo->isState == wlan_interface_state_connected) {
			dwResult = WlanQueryInterface(hClient, &pIfInfo->InterfaceGuid,
										  wlan_intf_opcode_current_connection,
										  NULL,
										  &connectInfoSize,
										  (PVOID *) &pConnectInfo, 
										  &opCode);
			if (dwResult != ERROR_SUCCESS)
				goto bail;
			length = pConnectInfo->wlanAssociationAttributes.dot11Ssid.uSSIDLength;
			if (length > 0) {
				xsResult = xsNewInstanceOf(xsObjectPrototype);
				xsVar(0) = xsStringBuffer(NULL, length + 1);
				FskMemCopy(xsToString(xsVar(0)), pConnectInfo->wlanAssociationAttributes.dot11Ssid.ucSSID, length);
				xsSet(xsResult, xsID("SSID"), xsVar(0));
			}
   			break;
   		}
   	}
bail:
    if (pConnectInfo != NULL) {
        WlanFreeMemory(pConnectInfo);
        pConnectInfo = NULL;
    }
    if (pIfList != NULL) {
        WlanFreeMemory(pIfList);
        pIfList = NULL;
    }
    if (hClient != NULL) {
        WlanCloseHandle(hClient, NULL);
        hClient = NULL;
    }
}