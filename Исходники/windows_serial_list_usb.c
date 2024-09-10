/*
 * The sequence of entries in array must match with what java layer expect (6 informations
 * per USB device). If a particular USB attribute is not set in descriptor or can not be
 * obtained "---" is placed in its place.
 *
 * Returns array of USB device's information found, empty array if no USB device is found,
 * NULL if an error occurs (additionally throws exception).
 */
jobjectArray list_usb_devices(JNIEnv *env, jint vendor_to_match) {

	int x = 0;
	int i = 0;
	int vid = 0;
	BOOL ret = FALSE;
	DWORD error_code = 0;
	DWORD size = 0;
	TCHAR *ptrend;
	DWORD usb_member_index = 0;
	HDEVINFO usb_dev_info_set;
	SP_DEVINFO_DATA usb_dev_instance;
	DEVPROPTYPE proptype;
	DWORD regproptype;
	TCHAR buffer[1024];
	TCHAR charbuffer[1024];

	struct jstrarray_list list = { 0 };
	jstring usb_dev_info;
	jclass strClass = NULL;
	jobjectArray usbDevicesFound = NULL;

	init_jstrarraylist(&list, 50);

	/* get information set for all usb devices matching the GUID */
	usb_dev_info_set = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (usb_dev_info_set == INVALID_HANDLE_VALUE) {
		SetupDiDestroyDeviceInfoList(usb_dev_info_set);
		free_jstrarraylist(&list);
		throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
		return NULL;
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
			}
			else {
				SetupDiDestroyDeviceInfoList(usb_dev_info_set);
				free_jstrarraylist(&list);
				throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(error_code), NULL);
				return NULL;
			}
		}

		/* for this device find its instance ID (USB\VID_04D8&PID_00DF\000098037)
		 * this is the variable 'Device Instance Path' in device manager. */
		memset(buffer, '\0', sizeof(buffer));
		ret = SetupDiGetDeviceInstanceId(usb_dev_info_set, &usb_dev_instance, buffer, sizeof(buffer), &size);
		if (ret == FALSE) {
			SetupDiDestroyDeviceInfoList(usb_dev_info_set);
			free_jstrarraylist(&list);
			throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
			return NULL;
		}

		/* USB-IF vendor ID, extract and match, if matched continue further otherwise loop back */
		x = 0;
		while (buffer[x] != '\0') {
			if((buffer[x] == 'V') && (buffer[x + 1] == 'I') && (buffer[x + 2] == 'D') && (buffer[x + 3] == '_')) {
				break;
			}
			x++;
		}
		x = x + 4;
		i = 0;
		while (buffer[x] != '&') {
			charbuffer[i] = buffer[x];
			i++;
			x++;
		}
		charbuffer[i] = '\0'; /* indicate end of string */

		vid = (int)_tcstol(charbuffer, &ptrend, 16);

		if(vendor_to_match != 0) {
			/* we need to apply filter for identify specific vendor */
			if(vid != vendor_to_match) {
				usb_member_index++;
				continue;
			}
		}

		usb_dev_info = (*env)->NewString(env, charbuffer, (jsize) _tcslen(charbuffer));
		if((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
			(*env)->ExceptionClear(env);
			SetupDiDestroyDeviceInfoList(usb_dev_info_set);
			free_jstrarraylist(&list);
			throw_serialcom_exception(env, 3, 0, E_NEWSTRSTR);
			return NULL;
		}
		insert_jstrarraylist(&list, usb_dev_info);

		/* USB product ID */
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
			charbuffer[i] = buffer[x];
			i++;
			x++;
		}
		charbuffer[i] = '\0';

		usb_dev_info = (*env)->NewString(env, charbuffer, (jsize) _tcslen(charbuffer));
		if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
			(*env)->ExceptionClear(env);
			SetupDiDestroyDeviceInfoList(usb_dev_info_set);
			free_jstrarraylist(&list);
			throw_serialcom_exception(env, 3, 0, E_NEWSTRSTR);
			return NULL;
		}
		insert_jstrarraylist(&list, usb_dev_info);

		/* SERIAL NUMBER */
		x++;
		i = 0;
		while (buffer[x] != '\0') {
			charbuffer[i] = buffer[x];
			i++;
			x++;
		}
		charbuffer[i] = '\0';

		usb_dev_info = (*env)->NewString(env, charbuffer, (jsize) _tcslen(charbuffer));
		if ((usb_dev_info == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
			(*env)->ExceptionClear(env);
			SetupDiDestroyDeviceInfoList(usb_dev_info_set);
			free_jstrarraylist(&list);
			throw_serialcom_exception(env, 3, 0, E_NEWSTRSTR);
			return NULL;
		}
		insert_jstrarraylist(&list, usb_dev_info);
		
		/* PRODUCT
			(idProduct field of USB device descriptor) */
		memset(buffer, '\0', sizeof(buffer));
		ret = SetupDiGetDeviceProperty(usb_dev_info_set, &usb_dev_instance, &DEVPKEY_Device_BusReportedDeviceDesc, &proptype, (BYTE *)buffer, sizeof(buffer), &size, 0);
		if (ret == FALSE) {
			/* fallback to SPDRP_DEVICEDESC if DEVPKEY_Device_BusReportedDeviceDesc fails */
			ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_DEVICEDESC, &regproptype, (BYTE *)buffer, sizeof(buffer), &size);
			if (ret == FALSE) {
				/* if second attempt fails, throw error, we need to investigate drivers/firmware etc */
				SetupDiDestroyDeviceInfoList(usb_dev_info_set);
				free_jstrarraylist(&list);
				throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
				return NULL;
			}
			usb_dev_info = (*env)->NewString(env, buffer, (jsize)_tcslen(buffer));
			insert_jstrarraylist(&list, usb_dev_info);
		}else {
			usb_dev_info = (*env)->NewString(env, buffer, (jsize)_tcslen(buffer));
			insert_jstrarraylist(&list, usb_dev_info);
		}

		/* MANUFACTURER */
		memset(buffer, '\0', sizeof(buffer));
		ret = SetupDiGetDeviceProperty(usb_dev_info_set, &usb_dev_instance, &DEVPKEY_Device_Manufacturer, &proptype, (BYTE *)buffer, sizeof(buffer), &size, 0);
		if (ret == FALSE) {
			SetupDiDestroyDeviceInfoList(usb_dev_info_set);
			free_jstrarraylist(&list);
			throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
			return NULL;
		}
		usb_dev_info = (*env)->NewString(env, buffer, (jsize) _tcslen(buffer));
		insert_jstrarraylist(&list, usb_dev_info);

		/* LOCATION (Location paths + Location info, get separately and then create a single string) */
		memset(buffer, '\0', sizeof(buffer));
		ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_LOCATION_PATHS, &regproptype, (BYTE *)buffer, sizeof(buffer), &size);
		if (ret == FALSE) {
			SetupDiDestroyDeviceInfoList(usb_dev_info_set);
			free_jstrarraylist(&list);
			throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
			return NULL;
		}

		memset(charbuffer, '\0', sizeof(charbuffer));
		ret = SetupDiGetDeviceRegistryProperty(usb_dev_info_set, &usb_dev_instance, SPDRP_LOCATION_INFORMATION, &regproptype, (BYTE *)charbuffer, sizeof(charbuffer), &size);
		if (ret == FALSE) {
			SetupDiDestroyDeviceInfoList(usb_dev_info_set);
			free_jstrarraylist(&list);
			throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
			return NULL;
		}

		i = 0;
		x = (int)_tcslen(buffer);
		buffer[x] = '-';
		x++;
		for (i = 0; i < (int)_tcslen(charbuffer); i++) {
			buffer[x] = charbuffer[i];
			x++;
		}
		buffer[x] = '\0';

		usb_dev_info = (*env)->NewString(env, buffer, (jsize)_tcslen(buffer));
		insert_jstrarraylist(&list, usb_dev_info);

		/* loop to get next USB device */
		usb_member_index++;
	}

	SetupDiDestroyDeviceInfoList(usb_dev_info_set);

	strClass = (*env)->FindClass(env, JAVALSTRING);
	if((strClass == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
		(*env)->ExceptionClear(env);
		free_jstrarraylist(&list);
		throw_serialcom_exception(env, 3, 0, E_FINDCLASSSSTRINGSTR);
		return NULL;
	}

	usbDevicesFound = (*env)->NewObjectArray(env, (jsize)list.index, strClass, NULL);
	if((usbDevicesFound == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
		(*env)->ExceptionClear(env);
		free_jstrarraylist(&list);
		throw_serialcom_exception(env, 3, 0, E_NEWOBJECTARRAYSTR);
		return NULL;
	}

	for (x = 0; x < list.index; x++) {
		(*env)->SetObjectArrayElement(env, usbDevicesFound, x, list.base[x]);
		if ((*env)->ExceptionOccurred(env)) {
			(*env)->ExceptionClear(env);
			free_jstrarraylist(&list);
			throw_serialcom_exception(env, 3, 0, E_SETOBJECTARRAYSTR);
			return NULL;
		}
	}

	free_jstrarraylist(&list);
	return usbDevicesFound;
}