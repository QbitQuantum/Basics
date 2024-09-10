struct hid_device_info HID_API_EXPORT * HID_API_CALL hid_enumerate(unsigned short vendor_id, unsigned short product_id)
{
	BOOL res;
	struct hid_device_info *root = NULL; // return object
	struct hid_device_info *cur_dev = NULL;

#ifndef HIDAPI_USE_DDK
	if (!initialized)
		lookup_functions();
#endif

	// Windows objects for interacting with the driver.
	GUID InterfaceClassGuid = {0x4d1e55b2, 0xf16f, 0x11cf, {0x88, 0xcb, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30} };
	SP_DEVINFO_DATA devinfo_data;
	SP_DEVICE_INTERFACE_DATA device_interface_data;
	SP_DEVICE_INTERFACE_DETAIL_DATA_A *device_interface_detail_data = NULL;
	HDEVINFO device_info_set = INVALID_HANDLE_VALUE;

	// Initialize the Windows objects.
	devinfo_data.cbSize = sizeof(SP_DEVINFO_DATA);
	device_interface_data.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);


	// Get information for all the devices belonging to the HID class.
	device_info_set = SetupDiGetClassDevsA(&InterfaceClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	
	// Iterate over each device in the HID class, looking for the right one.
	int device_index = 0;
	for (;;) {
		HANDLE write_handle = INVALID_HANDLE_VALUE;
		DWORD required_size = 0;

		res = SetupDiEnumDeviceInterfaces(device_info_set,
			NULL,
			&InterfaceClassGuid,
			device_index,
			&device_interface_data);
		
		if (!res) {
			// A return of FALSE from this function means that
			// there are no more devices.
			break;
		}

		// Call with 0-sized detail size, and let the function
		// tell us how long the detail struct needs to be. The
		// size is put in &required_size.
		res = SetupDiGetDeviceInterfaceDetailA(device_info_set,
			&device_interface_data,
			NULL,
			0,
			&required_size,
			NULL);

		// Allocate a long enough structure for device_interface_detail_data.
		device_interface_detail_data = (SP_DEVICE_INTERFACE_DETAIL_DATA_A*) malloc(required_size);
		device_interface_detail_data->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);

		// Get the detailed data for this device. The detail data gives us
		// the device path for this device, which is then passed into
		// CreateFile() to get a handle to the device.
		res = SetupDiGetDeviceInterfaceDetailA(device_info_set,
			&device_interface_data,
			device_interface_detail_data,
			required_size,
			NULL,
			NULL);

		if (!res) {
			//register_error(dev, "Unable to call SetupDiGetDeviceInterfaceDetail");
			// Continue to the next device.
			goto cont;
		}

		//wprintf(L"HandleName: %s\n", device_interface_detail_data->DevicePath);

		// Open a handle to the device
		write_handle = CreateFileA(device_interface_detail_data->DevicePath,
			GENERIC_WRITE |GENERIC_READ,
			0x0, /*share mode*/
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,//FILE_ATTRIBUTE_NORMAL,
			0);

		// Check validity of write_handle.
		if (write_handle == INVALID_HANDLE_VALUE) {
			// Unable to open the device.
			//register_error(dev, "CreateFile");
			goto cont_close;
		}		


		// Get the Vendor ID and Product ID for this device.
		HIDD_ATTRIBUTES attrib;
		attrib.Size = sizeof(HIDD_ATTRIBUTES);
		HidD_GetAttributes(write_handle, &attrib);
		//wprintf(L"Product/Vendor: %x %x\n", attrib.ProductID, attrib.VendorID);

		// Check the VID/PID to see if we should add this
		// device to the enumeration list.
		if ((vendor_id == 0x0 && product_id == 0x0) || 
			(attrib.VendorID == vendor_id && attrib.ProductID == product_id)) {

			#define WSTR_LEN 512
			const char *str;
			struct hid_device_info *tmp;
			HIDP_PREPARSED_DATA *pp_data = NULL;
			HIDP_CAPS caps;
			BOOLEAN res;
			NTSTATUS nt_res;
			wchar_t wstr[WSTR_LEN]; // TODO: Determine Size
			size_t len;

			/* VID/PID match. Create the record. */
			tmp = (hid_device_info*) calloc(1, sizeof(struct hid_device_info));
			if (cur_dev) {
				cur_dev->next = tmp;
			}
			else {
				root = tmp;
			}
			cur_dev = tmp;

			// Get the Usage Page and Usage for this device.
			res = HidD_GetPreparsedData(write_handle, &pp_data);
			if (res) {
				nt_res = HidP_GetCaps(pp_data, &caps);
				if (nt_res == HIDP_STATUS_SUCCESS) {
					cur_dev->usage_page = caps.UsagePage;
					cur_dev->usage = caps.Usage;
				}

				HidD_FreePreparsedData(pp_data);
			}
			
			/* Fill out the record */
			cur_dev->next = NULL;
			str = device_interface_detail_data->DevicePath;
			if (str) {
				len = strlen(str);
				cur_dev->path = (char*) calloc(len+1, sizeof(char));
				strncpy(cur_dev->path, str, len+1);
				cur_dev->path[len] = '\0';
			}
			else
				cur_dev->path = NULL;

			/* Serial Number */
			res = HidD_GetSerialNumberString(write_handle, wstr, sizeof(wstr));
			wstr[WSTR_LEN-1] = 0x0000;
			if (res) {
				cur_dev->serial_number = _wcsdup(wstr);
			}

			/* Manufacturer String */
			res = HidD_GetManufacturerString(write_handle, wstr, sizeof(wstr));
			wstr[WSTR_LEN-1] = 0x0000;
			if (res) {
				cur_dev->manufacturer_string = _wcsdup(wstr);
			}

			/* Product String */
			res = HidD_GetProductString(write_handle, wstr, sizeof(wstr));
			wstr[WSTR_LEN-1] = 0x0000;
			if (res) {
				cur_dev->product_string = _wcsdup(wstr);
			}

			/* VID/PID */
			cur_dev->vendor_id = attrib.VendorID;
			cur_dev->product_id = attrib.ProductID;

			/* Release Number */
			cur_dev->release_number = attrib.VersionNumber;

			/* Interface Number (Unsupported on Windows)*/
			cur_dev->interface_number = -1;
		}

cont_close:
		CloseHandle(write_handle);
cont:
		// We no longer need the detail data. It can be freed
		free(device_interface_detail_data);

		device_index++;

	}

	// Close the device information handle.
	SetupDiDestroyDeviceInfoList(device_info_set);

	return root;

}