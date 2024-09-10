JNIEXPORT jint JNICALL Java_JNISignalQuality_nativeSignalQuality(JNIEnv *env, jobject obj){

	HANDLE hClient = NULL;
	DWORD dwMaxClient = 2;
	DWORD dwCurVersion = 0;
	DWORD dwResult = 0;
	WCHAR GuidString[39] = { 0 };

	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;

	PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;
	DWORD connectInfoSize = sizeof(WLAN_CONNECTION_ATTRIBUTES);
	WLAN_OPCODE_VALUE_TYPE opCode = wlan_opcode_value_type_invalid;

	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);

	if (dwResult != ERROR_SUCCESS){
		printf("Error with WlanOpenHandle\n");
		return 101;
	}

	dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);

	if (dwResult != ERROR_SUCCESS){
		printf("Error with WlanEnumInterfaces\n");
		return 102;
	}

	pIfInfo = (WLAN_INTERFACE_INFO *)& pIfList->InterfaceInfo[0];
	const GUID * IG = &pIfInfo->InterfaceGuid;
	StringFromGUID2(IG, (LPOLESTR)& GuidString, sizeof(GuidString) / sizeof(*GuidString));

	dwResult = WlanQueryInterface(hClient, &pIfInfo->InterfaceGuid, wlan_intf_opcode_current_connection, NULL, &connectInfoSize, (PVOID *)&pConnectInfo, &opCode);

	if (dwResult != ERROR_SUCCESS){
		printf("Error with WlanQueryInterface\n");
		return 103;
	}

	unsigned long sQuality = pConnectInfo->wlanAssociationAttributes.wlanSignalQuality;

	return sQuality;
}