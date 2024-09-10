// Main program
int main(int argc, char** argv)
{
	// Parse arguments
	int task = 0;
	if (argc < 2) {
		usage(argv[0]);
		return 2;
	}
	// Interface number
	DWORD ifSelect = 0;

	// Task
	if (argc >= 2) {
		if (strncmp(argv[1], "if", 2) == 0) {
			task = TASK_LIST_INTERFACES;
		}
		else if (strncmp(argv[1], "scan", 4) == 0) {
			task = TASK_SCAN_NETWORKS;
		}
		else if (strncmp(argv[1], "list", 4) == 0) {
			task = TASK_LIST_NETWORKS;
		}
		else if (strncmp(argv[1], "query", 5) == 0) {
			task = TASK_SCAN_NETWORKS | TASK_LIST_NETWORKS;
		}
	}

	// Interface
	if (argc >= 3) {
		sscanf(argv[2], "%d", &ifSelect);
	}

	// Setup
	HANDLE whandle = getWlanHandle();
	std::string input;

	if (whandle == NULL) {
		printf("Error: Failed to open wlan handle.\n");
		return 1;
	}

	// Print usage and exit
	if (task == TASK_USAGE) {
		usage(argv[0]);
		return 2;
	}

	// Get interfaces
	PWLAN_INTERFACE_INFO_LIST ifList = NULL;
	ifList = getWlanInterfaces(whandle);

	if (ifList == NULL) {
		printf("Error: Failed to find wlan interfaces.\n");
		return 1;
	}

	// Print interfaces and exit
	if (bitCheck(task, TASK_LIST_INTERFACES)) {
		for (DWORD i = 0; i < ifList->dwNumberOfItems; i++) {
			PWLAN_INTERFACE_INFO info = (WLAN_INTERFACE_INFO *)&ifList->InterfaceInfo[i];
            printf("% 2d  ", i);
            for (int j = 0; j < 256 && info->strInterfaceDescription[j] != 0; j++) {
                printf("%c", (unsigned char) info->strInterfaceDescription[j]);
            }
            printf("\n");
		}
		WlanFreeMemory(ifList);
		return 0;
	}

	// Select the wlan interface
	GUID ifGuid;
	if (ifList->dwNumberOfItems == 0) {
		printf("Error: No wlan interfaces exist.\n");
		return 1;
	}
	else {
		if (ifSelect >= ifList->dwNumberOfItems) {
			//printf("Warning: Interface %d does not exist. Defaulting to interface 0.\n", ifSelect);
			ifSelect = 0;
		}
		ifGuid = ((WLAN_INTERFACE_INFO *)&ifList->InterfaceInfo[ifSelect])->InterfaceGuid;
	}
	WlanFreeMemory(ifList);

	if (bitCheck(task, TASK_LIST_NETWORKS)) {
		// List available networks
		std::vector<NetworkInfo> networks = getWifiNetworks(whandle, ifGuid);
		
		for (auto itr = networks.begin(); itr != networks.end(); itr++) {
			// Rssi
			printf("% 4d  ", (*itr).rssi);
			// Quality
			printf("% 4d  ", (*itr).quality);
			// Bssid
			for (int i = 0; i < 6; i++) printf("%02x", (*itr).bssid[i]) && (i<5) && printf(":");
			printf("  ");
			// Ssid
			for (int i = 0; i < 32; i++) printf("%c", (*itr).ssid[i]);
			printf("\n");
		}
	}

	if (bitCheck(task, TASK_SCAN_NETWORKS)) {
		// Scan for network
		scanWifiNetworks(whandle, ifGuid);
	}

	return 0;
}