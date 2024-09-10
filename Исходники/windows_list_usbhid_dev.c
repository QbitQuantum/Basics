/*
 * Finds information about USB HID devices using setup class API.
 *
 * The sequence of entries in array must match with what java layer expect. If a particular USB
 * attribute is not set in descriptor or can not be obtained "---" is placed in its place.
 *
 * The array returned will be in following sequence; transport, device node, vendor ID,
 * product ID, serial, product, manufacturer, USB bus number, USB device number, location.
 *
 * For an HID interface in a USB device, Windows create a device instance for the USB interface
 * (GUID_DEVINTERFACE_HID_DEVICE) and another device instance for the HID collection (GUID_DEVINTERFACE_HID).
 * This function relate HID collection device instance to its USB interface (physical USB device) through
 * HardwareID. A hardware ID is a vendor-defined identification string that Windows uses to match a
 * device to an INF file. In most cases, a device has associated with it a list of hardware IDs.
 * (However, there are exceptions − see Identifiers for 1394 Devices). When an enumerator reports a
 * list of hardware IDs for a device, the hardware IDs should be listed in order of decreasing suitability.
 *
 * This key contains symbolic links to HID device instances :
 * HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses\{4d1e55b2-f16f-11cf-88cb-001111000030}
 * 
 * This function basically collect information from USB and HID subsystems and relate them to identify a device
 * and then create a unified information to be sent to java application.
 */
jobjectArray enumerate_usb_hid_devices(JNIEnv *env, jint vendor_to_match) {

	int q = 0;
	int i = 0;
	int x = 0;
	BOOL ret = FALSE;
	LONG status = 0;
	DWORD error_code = 0;
	DWORD errorVal = 0;
	DWORD size = 0;
	DWORD charbuffer_size = 0;
	DWORD driver_name_size = 0;
	ULONG buffer_size = 0;
	ULONG devprop_buffer_size = 0;
	DEVPROPTYPE proptype;
	DWORD regproptype;

	CONFIGRET cmret = 0;
	DEVINST firstchild = 0;
	DEVINST next_sibling = 0;
	DEVINST current_sibling = 0;

	struct hiddev_inst_cont_id *instidinfo;
	struct hiddev_instance_list hiddevinst_list = { 0 };
	struct jstrarray_list list = { 0 };

	DWORD hid_member_index = 0;
	HDEVINFO hid_dev_info_set;
	SP_DEVINFO_DATA hid_dev_instance;

	DWORD usb_member_index = 0;
	HDEVINFO usb_dev_info_set;
	SP_DEVINFO_DATA usb_dev_instance;

	/* size of these buffers is hardcoded in functions using them */
	TCHAR buffer[1024];
	TCHAR devprop_buffer[1024];
	TCHAR keybuf[1024];
	TCHAR charbuffer[512];
	TCHAR tmpbuf[128];
	char cmerror[256];

	jstring usb_dev_info;
	jclass strClass = NULL;
	jobjectArray usbHidDevicesFound = NULL;

	/* allocate memory to hold information used during processing and returning information
	   to caller. */
	x = init_hiddev_instance_list(&hiddevinst_list, 25);
	if (x < 0) {
		return clean_throw_exp_usbenumeration(env, 0, 1, 0, E_CALLOCSTR, NULL, NULL, NULL, NULL);
	}

	/* ~~~~~~~~~~~~~ ENUMERATE ALL HID DEVICES ~~~~~~~~~~~~~ */

	/* get information set for all HID devices matching the GUID. It an array of 
	   structures containing information about all attached and enumerated HID devices.	*/
	hid_dev_info_set = SetupDiGetClassDevs(&GUID_DEVINTERFACE_HID, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hid_dev_info_set == INVALID_HANDLE_VALUE) {
		return clean_throw_exp_usbenumeration(env, 1, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, NULL, &hiddevinst_list, NULL, &hid_dev_info_set);
	}

	/* enumerate all devices in this information set starting from 0th index */
	hid_member_index = 0;
	while (1) {
		ZeroMemory(&hid_dev_instance, sizeof(hid_dev_instance));
		hid_dev_instance.cbSize = sizeof(hid_dev_instance);

		/* from information set, get device by index */
		ret = SetupDiEnumDeviceInfo(hid_dev_info_set, hid_member_index, &hid_dev_instance);
		if (ret == FALSE) {
			error_code = GetLastError();
			if (error_code == ERROR_NO_MORE_ITEMS) {
				break;
			}else {
				return clean_throw_exp_usbenumeration(env, 1, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, NULL, &hiddevinst_list, NULL, &hid_dev_info_set);
			}
		}

		/* for this device find its instance ID, for example; HID\VID_04D8&PID_00DF&MI_02\7&33842C3F&0&0000
		 * this is variable 'Device Instance Path' in device manager. */
		memset(buffer, '\0', 1024);
		ret = SetupDiGetDeviceInstanceId(hid_dev_info_set, &hid_dev_instance, buffer, 1024, &size);
		if (ret == FALSE) {
			return clean_throw_exp_usbenumeration(env, 1, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, NULL, &hiddevinst_list, NULL, &hid_dev_info_set);
		}

		/* get HardwareID of this device;
		   HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\HID\VID_04D8&PID_00DF&MI_02\7&33842C3F&0&0000\HardwareID */
		memset(keybuf, '\0', 1024);
		_stprintf_s(keybuf, 1024, TEXT("SYSTEM\\CurrentControlSet\\Enum\\%s"), buffer);

		charbuffer_size = sizeof(charbuffer);
		memset(charbuffer, '\0', 512);

		status = RegGetValue(HKEY_LOCAL_MACHINE, keybuf, TEXT("HardwareID"), RRF_RT_REG_MULTI_SZ, NULL, (PVOID)charbuffer, &charbuffer_size);
		if (status != ERROR_SUCCESS) {
			return clean_throw_exp_usbenumeration(env, 1, 2, GetLastError(), NULL, NULL, &hiddevinst_list, NULL, &hid_dev_info_set);
		}

		/* save device instance and hardware id (including terminating null character) in the
		   list for later comparision */
		instidinfo = NULL;
		instidinfo = (struct hiddev_inst_cont_id *) malloc(sizeof(struct hiddev_inst_cont_id));
		if (instidinfo == NULL) {
			return clean_throw_exp_usbenumeration(env, 1, 1, 0, E_MALLOCSTR, NULL, &hiddevinst_list, NULL, &hid_dev_info_set);
		}
		_tcscpy_s(instidinfo->instance, 512, buffer);
		_tcscpy_s(instidinfo->hwid, 512, charbuffer);

		insert_hiddev_instance_list(&hiddevinst_list, instidinfo);

		/* increment to get the next HID device instance */
		hid_member_index++;
	}

	/* release HID info set as it is no longer needed */
	SetupDiDestroyDeviceInfoList(hid_dev_info_set);

	/* allocate memory to hold information used during processing and returning information
	to caller. */
	x = init_jstrarraylist(&list, 100);
	if (x < 0) {
		return clean_throw_exp_usbenumeration(env, 2, 1, 0, E_CALLOCSTR, NULL, &hiddevinst_list, NULL, NULL);
	}

	/* From here onwards, enumerate over all USB interfaces looking for HID interface and try to
	   associate with its device instance and then create information that will be passed to
	   application. */

	/* ~~~~~~~~~~~~~ ENUMERATE ALL USB DEVICES ~~~~~~~~~~~~~ */

	/* get information set for all usb devices matching the GUID */
	usb_dev_info_set = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (usb_dev_info_set == INVALID_HANDLE_VALUE) {
		return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
	}

	/* enumerate all devices in this information set */
	usb_member_index = 0;
	while (1) {
		ZeroMemory(&usb_dev_instance, sizeof(usb_dev_instance));
		usb_dev_instance.cbSize = sizeof(usb_dev_instance);

		/* from information set, get device by index */
		ret = SetupDiEnumDeviceInfo(usb_dev_info_set, usb_member_index, &usb_dev_instance);
		if (ret == FALSE) {
			error_code = GetLastError();
			if (error_code == ERROR_NO_MORE_ITEMS) {
				break;
			}else {
				return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
			}
		}

		/* for this device find its instance ID (USB\VID_04D8&PID_00DF\000098037)
		 * this is the variable 'Device Instance Path' in device manager. */
		memset(buffer, '\0', sizeof(buffer));
		ret = SetupDiGetDeviceInstanceId(usb_dev_info_set, &usb_dev_instance, buffer, 1024, &size);
		if (ret == FALSE) {
			return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
		}

		/* fetch and examine USB interface */
		cmret = CM_Get_Child(&firstchild, usb_dev_instance.DevInst, 0);
		if (cmret != CR_SUCCESS) {
			if (cmret == CR_NO_SUCH_DEVNODE) {
				/* this device does not have any child, so check if this is a HID class device or not */
				memset(devprop_buffer, '\0', 1024);
				ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_CLASSGUID, &regproptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size);
				if (ret == FALSE) {
					return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}

				/* check if this is a HID device interface, if it is not than loop back to examine next USB device */
				ret = _tcsicmp(devprop_buffer, TEXT("{745A17A0-74D3-11D0-B6FE-00A0C90F57DA}"));
				if (ret != 0) {
					usb_member_index++;
					continue;
				}

				/* reaching here means that the device is a HID device, so create all the information
				that will be passed to java layer. */

				/* get the HardwareID of this USB HID interface. HardwareID is multi-sz, however
				   we use only 1st string from multi-string HardwareID for our matching.
				   HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_04D8&PID_00DF&MI_02\7&33842C3F&0&0000\HardwareID 
				   The buffer contains device instance path of USB device */
				memset(keybuf, '\0', 1024);
				_stprintf_s(keybuf, 1024, TEXT("SYSTEM\\CurrentControlSet\\Enum\\%s"), buffer);

				charbuffer_size = sizeof(charbuffer);
				memset(charbuffer, '\0', 512);

				/* USB\VID_04D8&PID_00DF&REV_0101 and USB\VID_04D8&PID_00DF and so on */
				status = RegGetValue(HKEY_LOCAL_MACHINE, keybuf, TEXT("HardwareID"), RRF_RT_REG_MULTI_SZ, NULL, (PVOID)charbuffer, &charbuffer_size);
				if (status != ERROR_SUCCESS) {
					return clean_throw_exp_usbenumeration(env, 3, 2, GetLastError(), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}

				/* charbuffer now contains hardwareID, cook it a little bit to enable suitable matching */
				if ((charbuffer[0] == 'U') && (charbuffer[1] == 'S') && (charbuffer[2] == 'B')) {
					charbuffer[0] = 'H';
					charbuffer[1] = 'I';
					charbuffer[2] = 'D';
				}

				for (q = 0; q < hiddevinst_list.index; q++) {

					/* check association between HID collection device instance and USB device instance */
					ret = _tcsicmp(charbuffer, hiddevinst_list.base[q]->hwid);
					if (ret != 0) {
						continue;
					}

					/* reaching here means this HID collection belongs to this USB HID device, so glean information
					   to be passed to java layer. */

					/* TRANSPORT */
					usb_dev_info = (*env)->NewStringUTF(env, "USB");
					if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
						return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
					insert_jstrarraylist(&list, usb_dev_info);

					/* DEVICE NODE */
					usb_dev_info = (*env)->NewString(env, hiddevinst_list.base[q]->instance, (jsize)_tcslen(hiddevinst_list.base[q]->instance));
					if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
						return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
					insert_jstrarraylist(&list, usb_dev_info);

					/* USB-IF VENDOR ID
					   (extracted from USB device instance for example: USB\VID_04D8&PID_00DF\000098037) */
					x = 0;
					while (buffer[x] != '\0') {
						if ((buffer[x] == 'V') && (buffer[x + 1] == 'I') && (buffer[x + 2] == 'D') && (buffer[x + 3] == '_')) {
							break;
						}
						x++;
					}
					x = x + 4;
					i = 0;
					while (buffer[x] != '&') {
						tmpbuf[i] = buffer[x];
						i++;
						x++;
					}
					tmpbuf[i] = '\0'; /* indicate end of string */
					usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
					if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
						return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
					insert_jstrarraylist(&list, usb_dev_info);

					/* USB product ID
					   (extracted from USB device instance for example: USB\VID_04D8&PID_00DF\000098037) */
					x = 6;
					while (buffer[x] != '\0') {
						if ((buffer[x] == 'P') && (buffer[x + 1] == 'I') && (buffer[x + 2] == 'D') && (buffer[x + 3] == '_')) {
							break;
						}
						x++;
					}
					x = x + 4;
					i = 0;
					while (buffer[x] != '\\') {
						tmpbuf[i] = buffer[x];
						i++;
						x++;
					}
					tmpbuf[i] = '\0'; /* indicate end of string */
					usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
					if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
						return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
					insert_jstrarraylist(&list, usb_dev_info);

					/* SERIAL NUMBER */
					x++;
					i = 0;
					while (buffer[x] != '\0') {
						tmpbuf[i] = buffer[x];
						i++;
						x++;
					}
					tmpbuf[i] = '\0';
					usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
					if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
						return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
					insert_jstrarraylist(&list, usb_dev_info);

					/* PRODUCT
					   (iProduct field of USB device descriptor) */
					memset(devprop_buffer, '\0', sizeof(devprop_buffer));
					ret = SetupDiGetDeviceProperty(usb_dev_info_set, &usb_dev_instance, &DEVPKEY_Device_BusReportedDeviceDesc, &proptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size, 0);
					if (ret == FALSE) {
						/* fallback to SPDRP_DEVICEDESC if DEVPKEY_Device_BusReportedDeviceDesc fails */
						ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_DEVICEDESC, &regproptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size);
						if (ret == FALSE) {
							/* if second attempt fails, throw error, we need to investigate drivers/firmware etc */
							return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
						}
					}
					usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
					insert_jstrarraylist(&list, usb_dev_info);

					/* MANUFACTURER */
					memset(devprop_buffer, '\0', sizeof(devprop_buffer));
					ret = SetupDiGetDeviceProperty(usb_dev_info_set, &usb_dev_instance, &DEVPKEY_Device_Manufacturer, &proptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size, 0);
					if (ret == FALSE) {
						return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
					usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
					insert_jstrarraylist(&list, usb_dev_info);

					/* LOCATION
					   (Location paths + Location info, get separately and then create a single string) */

					// PCIROOT(0)#PCI(1400)#USBROOT(0)#USB(3)
					memset(devprop_buffer, '\0', sizeof(devprop_buffer));
					ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_LOCATION_PATHS, &regproptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size);
					if (ret == FALSE) {
						return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
					// Port_#0003.Hub_#0001
					memset(charbuffer, '\0', sizeof(charbuffer));
					ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_LOCATION_INFORMATION, &regproptype, (BYTE *)charbuffer, sizeof(charbuffer), &size);
					if (ret == FALSE) {
						return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}

					i = 0;
					x = (int)_tcslen(devprop_buffer);
					devprop_buffer[x] = '-';
					x++;
					for (i = 0; i < (int)_tcslen(charbuffer); i++) {
						devprop_buffer[x] = charbuffer[i];
						x++;
					}
					devprop_buffer[x] = '\0';

					usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
					insert_jstrarraylist(&list, usb_dev_info);
				}

				/* loop back to get next USB device */
				usb_member_index++;
				continue;
			}else {
				/* error happend when getting child of USB device */
				_snprintf_s(cmerror, 256, 256, "CM_Get_Child failed with CR_xxxx error code : 0x%X\0", cmret);
				return clean_throw_exp_usbenumeration(env, 3, 1, 0, cmerror, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
			}
		}

		/* reaching here means that this USB device has at-least one child device node, examine first child now */
		devprop_buffer_size = sizeof(devprop_buffer);
		memset(devprop_buffer, '\0', 1024);

		cmret = CM_Get_DevNode_Registry_Property(firstchild, CM_DRP_CLASSGUID, &proptype, (PVOID)devprop_buffer, &devprop_buffer_size, 0);
		if (cmret != CR_SUCCESS) {
			_snprintf_s(cmerror, 256, 256, "CM_Get_DevNode_Registry_Property failed with CR_xxxx error code : 0x%X\0", cmret);
			return clean_throw_exp_usbenumeration(env, 3, 1, 0, cmerror, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
		}

		/* check if first child is a HID device interface */
		ret = _tcsicmp(devprop_buffer, TEXT("{745A17A0-74D3-11D0-B6FE-00A0C90F57DA}"));
		if (ret == 0) {
			/* reaching here means that this sibling (interface) is a HID type, get its device instance path */
			memset(devprop_buffer, '\0', 1024);
			cmret = CM_Get_Device_ID(firstchild, devprop_buffer, 1024, 0);
			if (cmret != CR_SUCCESS) {
				_snprintf_s(cmerror, 256, 256, "CM_Get_Device_ID failed with CR_xxxx error code : 0x%X\0", cmret);
				return clean_throw_exp_usbenumeration(env, 3, 1, 0, cmerror, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
			}

			/* get the HardwareID of this USB HID interface. HardwareID is multi-sz, however
			   we use only 1st string from multi-string HardwareID for our matching.
			   HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_04D8&PID_00DF&MI_02\7&33842C3F&0&0000\HardwareID */
			memset(charbuffer, '\0', 512);
			buffer_size = sizeof(charbuffer);
			cmret = CM_Get_DevNode_Registry_Property(firstchild, CM_DRP_HARDWAREID, NULL, (PVOID)charbuffer, &buffer_size, 0);
			if (cmret != CR_SUCCESS) {
				_snprintf_s(cmerror, 256, 256, "CM_Get_Device_ID failed with CR_xxxx error code : 0x%X\0", cmret);
				return clean_throw_exp_usbenumeration(env, 3, 1, 0, cmerror, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
			}

			if ((charbuffer[0] == 'U') && (charbuffer[1] == 'S') && (charbuffer[2] == 'B')) {
				charbuffer[0] = 'H';
				charbuffer[1] = 'I';
				charbuffer[2] = 'D';
			}

			for (q = 0; q < hiddevinst_list.index; q++) {

				/* check association between HID collection device instance and USB interface device instance */
				ret = _tcsncicmp(charbuffer, hiddevinst_list.base[q]->hwid, 512);
				if (ret != 0) {
					continue;
				}

				/* reaching here means this HID collection belongs to this USB HID interface, so glean information
				   to be passed to java layer. */

				/* TRANSPORT */
				usb_dev_info = (*env)->NewStringUTF(env, "USB");
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* DEVICE NODE */
				usb_dev_info = (*env)->NewString(env, hiddevinst_list.base[q]->instance, (jsize)_tcslen(hiddevinst_list.base[q]->instance));
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* USB-IF VENDOR ID
				   (extracted from USB device instance for example: USB\VID_04D8&PID_00DF\000098037) */
				x = 0;
				while (buffer[x] != '\0') {
					if ((buffer[x] == 'V') && (buffer[x + 1] == 'I') && (buffer[x + 2] == 'D') && (buffer[x + 3] == '_')) {
						break;
					}
					x++;
				}
				x = x + 4;
				i = 0;
				while (buffer[x] != '&') {
					tmpbuf[i] = buffer[x];
					i++;
					x++;
				}
				tmpbuf[i] = '\0'; /* indicate end of string */
				usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* USB product ID
				   (extracted from USB device instance for example: USB\VID_04D8&PID_00DF\000098037) */
				x = 6;
				while (buffer[x] != '\0') {
					if ((buffer[x] == 'P') && (buffer[x + 1] == 'I') && (buffer[x + 2] == 'D') && (buffer[x + 3] == '_')) {
						break;
					}
					x++;
				}
				x = x + 4;
				i = 0;
				while (buffer[x] != '\\') {
					tmpbuf[i] = buffer[x];
					i++;
					x++;
				}
				tmpbuf[i] = '\0'; /* indicate end of string */
				usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* SERIAL NUMBER */
				x++;
				i = 0;
				while (buffer[x] != '\0') {
					tmpbuf[i] = buffer[x];
					i++;
					x++;
				}
				tmpbuf[i] = '\0';
				usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* PRODUCT
				   (iProduct field of USB device descriptor) */
				memset(devprop_buffer, '\0', sizeof(devprop_buffer));
				ret = SetupDiGetDeviceProperty(usb_dev_info_set, &usb_dev_instance, &DEVPKEY_Device_BusReportedDeviceDesc, &proptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size, 0);
				if (ret == FALSE) {
					/* fallback to SPDRP_DEVICEDESC if DEVPKEY_Device_BusReportedDeviceDesc fails */
					ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_DEVICEDESC, &regproptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size);
					if (ret == FALSE) {
						/* if second attempt fails, throw error, we need to investigate drivers/firmware etc */
						return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
				}
				usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
				insert_jstrarraylist(&list, usb_dev_info);

				/* MANUFACTURER */
				memset(devprop_buffer, '\0', sizeof(devprop_buffer));
				ret = SetupDiGetDeviceProperty(usb_dev_info_set, &usb_dev_instance, &DEVPKEY_Device_Manufacturer, &proptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size, 0);
				if (ret == FALSE) {
					return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
				insert_jstrarraylist(&list, usb_dev_info);

				/* LOCATION
				  (Location paths + Location info, get separately and then create a single string) */

				// PCIROOT(0)#PCI(1400)#USBROOT(0)#USB(3)
				memset(devprop_buffer, '\0', sizeof(devprop_buffer));
				ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_LOCATION_PATHS, &regproptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size);
				if (ret == FALSE) {
					return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				// Port_#0003.Hub_#0001
				memset(charbuffer, '\0', sizeof(charbuffer));
				ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_LOCATION_INFORMATION, &regproptype, (BYTE *)charbuffer, sizeof(charbuffer), &size);
				if (ret == FALSE) {
					return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}

				i = 0;
				x = (int)_tcslen(devprop_buffer);
				devprop_buffer[x] = '-';
				x++;
				for (i = 0; i < (int)_tcslen(charbuffer); i++) {
					devprop_buffer[x] = charbuffer[i];
					x++;
				}
				devprop_buffer[x] = '\0';

				usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
				insert_jstrarraylist(&list, usb_dev_info);
			}
		}

		/* check if this usb device has more than one interface. if it has enumerate over each
		   one by one and collecting information for every HID interface found and sending it to 
		   java layer. */
		current_sibling = firstchild;
		while (1) {
			cmret = CM_Get_Sibling(&next_sibling, current_sibling, 0);
			if (cmret != CR_SUCCESS) {
				if (cmret == CR_NO_SUCH_DEVNODE) {
					/* done iterating over all interfaces, move to next examine next USB device */
					break;
				}else {
					_snprintf_s(cmerror, 256, 256, "CM_Get_Sibling failed with CR_xxxx error code : 0x%X\0", cmret);
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, cmerror, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
			}

			/* reaching here means USB device has more than 1 interfaces, get class of this interface (sibling) */
			devprop_buffer_size = sizeof(devprop_buffer);
			memset(devprop_buffer, '\0', sizeof(devprop_buffer));
			cmret = CM_Get_DevNode_Registry_Property(next_sibling, CM_DRP_CLASSGUID, &proptype, (VOID *)devprop_buffer, &devprop_buffer_size, 0);
			if (cmret != CR_SUCCESS) {
				_snprintf_s(cmerror, 256, 256, "CM_Get_DevNode_Registry_Property failed with CR_xxxx error code : 0x%X\0", cmret);
				return clean_throw_exp_usbenumeration(env, 3, 1, 0, cmerror, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
			}

			/* check if this is a HID device interface */
			ret = _tcsicmp(devprop_buffer, TEXT("{745A17A0-74D3-11D0-B6FE-00A0C90F57DA}"));
			if (ret != 0) {
				/* this is not HID interface, move to check next interface */
				current_sibling = next_sibling;
				continue;
			}

			/* reaching here means that this sibling (interface) is a HID type, get its device instance path */
			memset(devprop_buffer, '\0', 1024);
			cmret = CM_Get_Device_ID(next_sibling, devprop_buffer, 1024, 0);
			if (cmret != CR_SUCCESS) {
				_snprintf_s(cmerror, 256, 256, "CM_Get_Device_ID failed with CR_xxxx error code : 0x%X\0", cmret);
				return clean_throw_exp_usbenumeration(env, 3, 1, 0, cmerror, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
			}

			/* get the HardwareID of this USB HID interface. HardwareID is multi-sz, however
			   we use only 1st string from multi-string HardwareID for our matching.
			   HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_04D8&PID_00DF&MI_02\7&33842C3F&0&0000\HardwareID */
			memset(charbuffer, '\0', 512);
			buffer_size = sizeof(charbuffer);

			cmret = CM_Get_DevNode_Registry_Property(next_sibling, CM_DRP_HARDWAREID, NULL, (PVOID)charbuffer, &buffer_size, 0);
			if (cmret != CR_SUCCESS) {
				_snprintf_s(cmerror, 256, 256, "CM_Get_Device_ID failed with CR_xxxx error code : 0x%X\0", cmret);
				return clean_throw_exp_usbenumeration(env, 3, 1, 0, cmerror, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
			}

			if ((charbuffer[0] == 'U') && (charbuffer[1] == 'S') && (charbuffer[2] == 'B')) {
				charbuffer[0] = 'H';
				charbuffer[1] = 'I';
				charbuffer[2] = 'D';
			}

			for (q = 0; q < hiddevinst_list.index; q++) {

				/* check association between HID collection device instance and USB interface device instance */
				ret = _tcsncicmp(charbuffer, hiddevinst_list.base[q]->hwid, 512);
				if (ret != 0) {
					continue;
				}

				/* reaching here means this HID collection belongs to this USB HID interface, so glean information
				   to be passed to java layer. */

				/* TRANSPORT */
				usb_dev_info = (*env)->NewStringUTF(env, "USB");
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* DEVICE NODE */
				usb_dev_info = (*env)->NewString(env, hiddevinst_list.base[q]->instance, (jsize)_tcslen(hiddevinst_list.base[q]->instance));
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* USB-IF VENDOR ID
				   (extracted from USB device instance for example: USB\VID_04D8&PID_00DF\000098037) */
				x = 0;
				while (buffer[x] != '\0') {
					if ((buffer[x] == 'V') && (buffer[x + 1] == 'I') && (buffer[x + 2] == 'D') && (buffer[x + 3] == '_')) {
						break;
					}
					x++;
				}
				x = x + 4;
				i = 0;
				while (buffer[x] != '&') {
					tmpbuf[i] = buffer[x];
					i++;
					x++;
				}
				tmpbuf[i] = '\0'; /* indicate end of string */
				usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* USB product ID
				   (extracted from USB device instance for example: USB\VID_04D8&PID_00DF\000098037) */
				x = 6;
				while (buffer[x] != '\0') {
					if ((buffer[x] == 'P') && (buffer[x + 1] == 'I') && (buffer[x + 2] == 'D') && (buffer[x + 3] == '_')) {
						break;
					}
					x++;
				}
				x = x + 4;
				i = 0;
				while (buffer[x] != '\\') {
					tmpbuf[i] = buffer[x];
					i++;
					x++;
				}
				tmpbuf[i] = '\0'; /* indicate end of string */
				usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* SERIAL NUMBER */
				x++;
				i = 0;
				while (buffer[x] != '\0') {
					tmpbuf[i] = buffer[x];
					i++;
					x++;
				}
				tmpbuf[i] = '\0';
				usb_dev_info = (*env)->NewString(env, tmpbuf, (jsize)_tcslen(tmpbuf));
				if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWSTRUTFSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				insert_jstrarraylist(&list, usb_dev_info);

				/* PRODUCT
				   (iProduct field of USB device descriptor) */
				memset(devprop_buffer, '\0', sizeof(devprop_buffer));
				ret = SetupDiGetDeviceProperty(usb_dev_info_set, &usb_dev_instance, &DEVPKEY_Device_BusReportedDeviceDesc, &proptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size, 0);
				if (ret == FALSE) {
					/* fallback to SPDRP_DEVICEDESC if DEVPKEY_Device_BusReportedDeviceDesc fails */
					ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_DEVICEDESC, &regproptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size);
					if (ret == FALSE) {
						/* if second attempt fails, throw error, we need to investigate drivers/firmware etc */
						return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
					}
					usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
					insert_jstrarraylist(&list, usb_dev_info);
				}else {
					usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
					insert_jstrarraylist(&list, usb_dev_info);
				}

				/* MANUFACTURER */
				memset(devprop_buffer, '\0', sizeof(devprop_buffer));
				ret = SetupDiGetDeviceProperty(usb_dev_info_set, &usb_dev_instance, &DEVPKEY_Device_Manufacturer, &proptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size, 0);
				if (ret == FALSE) {
					return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
				insert_jstrarraylist(&list, usb_dev_info);

				/* LOCATION
				   (Location paths + Location info, get separately and then create a single string) */

				// PCIROOT(0)#PCI(1400)#USBROOT(0)#USB(3)
				memset(devprop_buffer, '\0', sizeof(devprop_buffer));
				ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_LOCATION_PATHS, &regproptype, (BYTE *)devprop_buffer, sizeof(devprop_buffer), &size);
				if (ret == FALSE) {
					return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}
				// Port_#0003.Hub_#0001
				memset(charbuffer, '\0', sizeof(charbuffer));
				ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_LOCATION_INFORMATION, &regproptype, (BYTE *)charbuffer, sizeof(charbuffer), &size);
				if (ret == FALSE) {
					return clean_throw_exp_usbenumeration(env, 3, 2, HRESULT_FROM_SETUPAPI(GetLastError()), NULL, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
				}

				i = 0;
				x = (int)_tcslen(devprop_buffer);
				devprop_buffer[x] = '-';
				x++;
				for (i = 0; i < (int)_tcslen(charbuffer); i++) {
					devprop_buffer[x] = charbuffer[i];
					x++;
				}
				devprop_buffer[x] = '\0';

				usb_dev_info = (*env)->NewString(env, devprop_buffer, (jsize)_tcslen(devprop_buffer));
				insert_jstrarraylist(&list, usb_dev_info);
			}

			/* set this sibling as base sibling for fetching next sibling, loop over to get and check next
			   interface (sibling) */
			current_sibling = next_sibling;
		}

		/* increment to get and examine the next usb device for HID class */
		usb_member_index++;
	}

	strClass = (*env)->FindClass(env, JAVALSTRING);
	if ((strClass == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
		return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_FINDCLASSSSTRINGSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
	}

	usbHidDevicesFound = (*env)->NewObjectArray(env, (jsize)list.index, strClass, NULL);
	if ((usbHidDevicesFound == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
		return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_NEWOBJECTARRAYSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
	}

	for (x = 0; x < list.index; x++) {
		(*env)->SetObjectArrayElement(env, usbHidDevicesFound, x, list.base[x]);
		if ((*env)->ExceptionOccurred(env)) {
			return clean_throw_exp_usbenumeration(env, 3, 1, 0, E_SETOBJECTARRAYSTR, &list, &hiddevinst_list, &usb_dev_info_set, NULL);
		}
	}

	/* clean up and return result to java layer application */
	free_jstrarraylist(&list);
	free_hiddev_instance_list(&hiddevinst_list);
	SetupDiDestroyDeviceInfoList(usb_dev_info_set);
	return usbHidDevicesFound;
}