int wiiuse_find(struct wiimote_t** wm, int max_wiimotes, int timeout) {
	GUID device_id;
	HANDLE dev;
	HDEVINFO device_info;
	int i, index;
	DWORD len;
	SP_DEVICE_INTERFACE_DATA device_data;
	PSP_DEVICE_INTERFACE_DETAIL_DATA detail_data = NULL;
	HIDD_ATTRIBUTES	attr;
	int found = 0;

	(void) timeout; /* unused */

	device_data.cbSize = sizeof(device_data);
	index = 0;

	/* get the device id */
	HidD_GetHidGuid(&device_id);

	/* get all hid devices connected */
	device_info = SetupDiGetClassDevs(&device_id, NULL, NULL, (DIGCF_DEVICEINTERFACE | DIGCF_PRESENT));

	for (;; ++index) {

		if (detail_data) {
			free(detail_data);
			detail_data = NULL;
		}

		/* query the next hid device info */
		if (!SetupDiEnumDeviceInterfaces(device_info, NULL, &device_id, index, &device_data))
			break;

		/* get the size of the data block required */
		i = SetupDiGetDeviceInterfaceDetail(device_info, &device_data, NULL, 0, &len, NULL);
		detail_data = (SP_DEVICE_INTERFACE_DETAIL_DATA_A*)malloc(len);
		detail_data->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		/* query the data for this device */
		if (!SetupDiGetDeviceInterfaceDetail(device_info, &device_data, detail_data, len, NULL, NULL))
			continue;

		/* open the device */
		dev = CreateFile(detail_data->DevicePath,
						(GENERIC_READ | GENERIC_WRITE),
						(FILE_SHARE_READ | FILE_SHARE_WRITE),
						NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
		if (dev == INVALID_HANDLE_VALUE)
			continue;

		/* get device attributes */
		attr.Size = sizeof(attr);
		i = HidD_GetAttributes(dev, &attr);

		if ((attr.VendorID == WM_VENDOR_ID) && (attr.ProductID == WM_PRODUCT_ID)) {
			/* this is a wiimote */
			wm[found]->dev_handle = dev;

			wm[found]->hid_overlap.hEvent = CreateEvent(NULL, 1, 1, "");
			wm[found]->hid_overlap.Offset = 0;
			wm[found]->hid_overlap.OffsetHigh = 0;

			WIIMOTE_ENABLE_STATE(wm[found], WIIMOTE_STATE_DEV_FOUND);
			WIIMOTE_ENABLE_STATE(wm[found], WIIMOTE_STATE_CONNECTED);

			/* try to set the output report to see if the device is actually connected */
			if (!wiiuse_set_report_type(wm[found])) {
				WIIMOTE_DISABLE_STATE(wm[found], WIIMOTE_STATE_CONNECTED);
				continue;
			}

			/* do the handshake */
			wiiuse_handshake(wm[found], NULL, 0);

			WIIUSE_INFO("Connected to wiimote [id %i].", wm[found]->unid);

			++found;
			if (found >= max_wiimotes)
				break;
		} else {
			/* not a wiimote */
			CloseHandle(dev);
		}
	}

	if (detail_data)
		free(detail_data);

	SetupDiDestroyDeviceInfoList(device_info);

	return found;
}