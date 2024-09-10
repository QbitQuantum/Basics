int get_ap_rssi_data(RADIOMAP &result_map)
{
	HANDLE hClient = NULL;
	DWORD dwMaxClient = 2;
	DWORD dwCurVersion = 0;
	DWORD dwResult = 0;
	DWORD dwRetVal = 0;
	WCHAR GuidString[39] = { 0 };
	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;
	PWLAN_BSS_ENTRY pBssEntry = NULL;
	PWLAN_BSS_LIST pBssList = NULL;
	LocalizationNode *pLocalizationNode = NULL;
	std::string mac_id;
	std::string ret_ssid;
	int iRet = 0;
	int ret;
	uint i;

	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
	if (dwResult != ERROR_SUCCESS)
	{
		wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
		return 1;
	}
	dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
	if (dwResult != ERROR_SUCCESS)
	{
		wprintf(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
		return 1;
	}
	else
	{
		wprintf(L"Nunber Entries: %lu\n", pIfList->dwNumberOfItems);
		wprintf(L"Current Index: %lu\n", pIfList->dwIndex);
		for (i = 0; i < (int)pIfList->dwNumberOfItems; i++)
		{
			pIfInfo = (WLAN_INTERFACE_INFO *)&pIfList->InterfaceInfo[i];
			wprintf(L" Interface Index[%u]:\t %lu\n", i, i);
			iRet = StringFromGUID2(pIfInfo->InterfaceGuid, (LPOLESTR)&GuidString,
				sizeof(GuidString) / sizeof(*GuidString));

			if (iRet == 0)
				wprintf(L"StringFromGUID2 Failed\n");
			else
				wprintf(L"  InterfaceGUID[%d]: %ws\n", i, GuidString);

			wprintf(L"  Interface Description[%d]: %ws", i,
				pIfInfo->strInterfaceDescription);
			wprintf(L"\n");
			wprintf(L"  Interface State[%d]:\t ", i);
			switch (pIfInfo->isState) {
			case wlan_interface_state_not_ready:
				wprintf(L"Not ready\n");
				break;
			case wlan_interface_state_connected:
				wprintf(L"Connected\n");
				break;
			case wlan_interface_state_ad_hoc_network_formed:
				wprintf(L"First node in a ad hoc network\n");
				break;
			case wlan_interface_state_disconnecting:
				wprintf(L"Disconnecting\n");
				break;
			case wlan_interface_state_disconnected:
				wprintf(L"Not connected\n");
				break;
			case wlan_interface_state_associating:
				wprintf(L"Attempting to associate with a network\n");
				break;
			case wlan_interface_state_discovering:
				wprintf(L"Auto configuration is discovering settings for the network\n");
				break;
			case wlan_interface_state_authenticating:
				wprintf(L"In process of authenticating\n");
				break;
			default:
				wprintf(L"Unknown state %ld\n", pIfInfo->isState);
				break;
			}
			wprintf(L"\n");

			const GUID * pGUID = &pIfInfo->InterfaceGuid;
			dwResult = WlanGetNetworkBssList(hClient, pGUID, NULL, dot11_BSS_type_any, 0, NULL, &pBssList);
			if (dwResult != ERROR_SUCCESS)
			{
				wprintf(L"Wlan get network bss list error: %lu\n", dwResult);
				return 1;
			}
			else
			{
				for (uint i = 0; i < pBssList->dwNumberOfItems; i++)
				{
					pBssEntry = &pBssList->wlanBssEntries[i];
					get_mac_id(pBssEntry->dot11Bssid, mac_id);
					if (find_at_radiomap(mac_id, result_map, pLocalizationNode) == 0)
					{
						pLocalizationNode->add_recoder(pBssEntry->lRssi);
					}
					else if (get_ssid(pBssEntry->dot11Ssid, ret_ssid) == 0)
					{
						LocalizationNode new_ap(mac_id, ret_ssid, pBssEntry->lRssi);
						ret = add_to_radiomap(new_ap, result_map);
						if (ret != 0)
						{
							printf("ERROR: add_to_radiomap error");
							exit(1);
						}
					}
				}
			}
		}
	}
	if (pBssList != NULL)
	{
		WlanFreeMemory(pBssList);
		pBssList = NULL;
	}
	if (pIfList != NULL)
	{
		WlanFreeMemory(pIfList);
		pIfList = NULL;
	}
	WlanCloseHandle(hClient, 0);
	return 0;
}