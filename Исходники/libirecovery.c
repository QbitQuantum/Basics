irecv_error_t mobiledevice_connect(irecv_client_t* client) {
	irecv_error_t ret;

	SP_DEVICE_INTERFACE_DATA currentInterface;
	HDEVINFO usbDevices;
	DWORD i;
	LPSTR path;
	irecv_client_t _client = (irecv_client_t) malloc(sizeof(struct irecv_client));
	memset(_client, 0, sizeof(struct irecv_client));

	// Get DFU paths
	usbDevices = SetupDiGetClassDevs(&GUID_DEVINTERFACE_DFU, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if(!usbDevices) {
		return IRECV_E_UNABLE_TO_CONNECT;
	}
	currentInterface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	for(i = 0; SetupDiEnumDeviceInterfaces(usbDevices, NULL, &GUID_DEVINTERFACE_DFU, i, &currentInterface); i++) {
		DWORD requiredSize = 0;
		PSP_DEVICE_INTERFACE_DETAIL_DATA details;
		SetupDiGetDeviceInterfaceDetail(usbDevices, &currentInterface, NULL, 0, &requiredSize, NULL);
		details = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc(requiredSize);
		details->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		if(!SetupDiGetDeviceInterfaceDetail(usbDevices, &currentInterface, details, requiredSize, NULL, NULL)) {
			irecv_close(_client);
			free(details);
			SetupDiDestroyDeviceInfoList(usbDevices);
			return IRECV_E_UNABLE_TO_CONNECT;
		} else {
			LPSTR result = (LPSTR) malloc(requiredSize - sizeof(DWORD));
			memcpy((void*) result, details->DevicePath, requiredSize - sizeof(DWORD));
			free(details);
			path = (LPSTR) malloc(requiredSize - sizeof(DWORD));
			memcpy((void*) path, (void*) result, requiredSize - sizeof(DWORD));
			TCHAR* pathEnd = strstr(path, "#{");
			*pathEnd = '\0';
			_client->DfuPath = result;
			break;
		}
	}
	SetupDiDestroyDeviceInfoList(usbDevices);
	// Get iBoot path
	usbDevices = SetupDiGetClassDevs(&GUID_DEVINTERFACE_IBOOT, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if(!usbDevices) {
		irecv_close(_client);
		return IRECV_E_UNABLE_TO_CONNECT;
	}
	currentInterface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	for(i = 0; SetupDiEnumDeviceInterfaces(usbDevices, NULL, &GUID_DEVINTERFACE_IBOOT, i, &currentInterface); i++) {
		DWORD requiredSize = 0;
		PSP_DEVICE_INTERFACE_DETAIL_DATA details;
		SetupDiGetDeviceInterfaceDetail(usbDevices, &currentInterface, NULL, 0, &requiredSize, NULL);
		details = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc(requiredSize);
		details->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		if(!SetupDiGetDeviceInterfaceDetail(usbDevices, &currentInterface, details, requiredSize, NULL, NULL)) {
			irecv_close(_client);
			free(details);
			SetupDiDestroyDeviceInfoList(usbDevices);
			return IRECV_E_UNABLE_TO_CONNECT;
		} else {
			LPSTR result = (LPSTR) malloc(requiredSize - sizeof(DWORD));
			memcpy((void*) result, details->DevicePath, requiredSize - sizeof(DWORD));
			free(details);

			if(strstr(result, path) == NULL) {
				free(result);
				continue;
			}
			
			_client->iBootPath = result;
			break;
		}
	}
	SetupDiDestroyDeviceInfoList(usbDevices);
	free(path);
	
	ret = mobiledevice_openpipes(_client);
	if (ret != IRECV_E_SUCCESS) return ret;
	
	*client = _client;
	return IRECV_E_SUCCESS;
}