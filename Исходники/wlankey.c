/*
 * Removes existing profiles on all interfaces
 */
DWORD RemoveWlanProfiles (const WLANKEY *profiles,
                          const WLANKEY *keep){
	DWORD apiver;
	DWORD status;
	HANDLE h;
	WLAN_INTERFACE_INFO_LIST *iflist;
	GUID *iface;
	int i;

	status = WlanOpenHandle (1, NULL, &apiver, &h);
	if (status != ERROR_SUCCESS){
		return status;
	}
	status = WlanEnumInterfaces (h, NULL, &iflist);
	for (i=0; status == ERROR_SUCCESS && i < iflist->dwNumberOfItems; i++){
		iface = &(iflist->InterfaceInfo[i].InterfaceGuid);
		status = RemoveIfaceProfiles (h, iface, profiles, keep);
	}

	WlanFreeMemory (iflist);
	WlanCloseHandle (h, NULL);
	return status;
}