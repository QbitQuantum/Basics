/*
 * Find the name of the most specific driver which is currently associated with the 
 * given HID device instance.
 *
 * A HID device can be on USB, I2C, BLUETOOTH or pseudo.
 */
jstring find_driver_for_given_hiddevice(JNIEnv *env, jstring hidDevNode) {

	int x = 0;
	BOOL ret = FALSE;
	LONG status = 0;
	DWORD error_code = 0;
	DWORD errorVal = 0;
	DWORD size = 0;
	DWORD charbuffer_size = 0;
	DWORD driver_name_size = 0;
	ULONG buffer_size = 0;
	DWORD hid_member_index = 0;
	HDEVINFO hid_dev_info_set;
	SP_DEVINFO_DATA hid_dev_instance;
	ULONG devprop_buffer_size = 0;
	const jchar* device_node = NULL;
	jstring driver_name = NULL;

	/* size of these buffers is hardcoded in functions using them */
	TCHAR buffer[1024];
	TCHAR keybuf[1024];
	TCHAR charbuffer[128];

	/* extract HID device name to match (as an array of Unicode characters) */
	device_node = (*env)->GetStringChars(env, hidDevNode, JNI_FALSE);
	if ((device_node == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
		throw_serialcom_exception(env, 3, 0, E_GETSTRCHARSTR);
		return NULL;
	}

	/* get information set for all usb devices matching the GUID */
	hid_dev_info_set = SetupDiGetClassDevs(&GUID_DEVINTERFACE_HID, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hid_dev_info_set == INVALID_HANDLE_VALUE) {
		SetupDiDestroyDeviceInfoList(hid_dev_info_set);
		(*env)->ReleaseStringChars(env, hidDevNode, device_node);
		throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
		return NULL;
	}

	/* enumerate all devices in this information set */
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
				SetupDiDestroyDeviceInfoList(hid_dev_info_set);
				(*env)->ReleaseStringChars(env, hidDevNode, device_node);
				throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(error_code), NULL);
				return NULL;
			}
		}

		/* for this device find its instance ID, for example; HID\VID_04D8&PID_00DF&MI_02\7&33842C3F&0&0000
		 * this is variable 'Device Instance Path' in device manager. */
		memset(buffer, '\0', 1024);
		ret = SetupDiGetDeviceInstanceId(hid_dev_info_set, &hid_dev_instance, buffer, 1024, &size);
		if (ret == FALSE) {
			SetupDiDestroyDeviceInfoList(hid_dev_info_set);
			(*env)->ReleaseStringChars(env, hidDevNode, device_node);
			throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
			return NULL;
		}

		/* match device path */
		ret = _tcsicmp(device_node, buffer);
		if (ret != 0) {
			hid_member_index++;
			continue;
		}

		/* reaching here means this is the device for which driver is to be found. 
		   HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\HID\VID_VID+PID_PID\Serial_Number */
		memset(keybuf, '\0', 1024);
		_stprintf_s(keybuf, 1024, TEXT("SYSTEM\\CurrentControlSet\\Enum\\%s"), buffer);

		/* HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\HID\VID_VID+PID_PID\Serial_Number\Service */
		charbuffer_size = sizeof(charbuffer);
		memset(charbuffer, '\0', 128);
		status = RegGetValue(HKEY_LOCAL_MACHINE, keybuf, TEXT("Service"), RRF_RT_REG_SZ, NULL, (PVOID)charbuffer, &charbuffer_size);
		if (status != ERROR_SUCCESS) {
			errorVal = GetLastError();
			if (errorVal == 0x00) {
				/* this indicates Service registery entry does not exist, we assume windows provided 
				   default HidClass driver is driving this device */
				driver_name = (*env)->NewStringUTF(env, "HidClass");
				if ((driver_name == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
					(*env)->ExceptionClear(env);
					SetupDiDestroyDeviceInfoList(hid_dev_info_set);
					(*env)->ReleaseStringChars(env, hidDevNode, device_node);
					throw_serialcom_exception(env, 3, 0, E_NEWSTRUTFSTR);
					return NULL;
				}
				return driver_name;
			}else {
				SetupDiDestroyDeviceInfoList(hid_dev_info_set);
				(*env)->ReleaseStringChars(env, hidDevNode, device_node);
				throw_serialcom_exception(env, 4, errorVal, NULL);
				return NULL;
			}
		}

		/* return the driver name found as indicated by Service registry entry */
		driver_name = (*env)->NewString(env, charbuffer, (jsize)_tcslen(charbuffer));
		if ((driver_name == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
			(*env)->ExceptionClear(env);
			SetupDiDestroyDeviceInfoList(hid_dev_info_set);
			(*env)->ReleaseStringChars(env, hidDevNode, device_node);
			throw_serialcom_exception(env, 3, 0, E_NEWSTRUTFSTR);
			return NULL;
		}

		SetupDiDestroyDeviceInfoList(hid_dev_info_set);
		(*env)->ReleaseStringChars(env, hidDevNode, device_node);
		return driver_name;
	}

	/* reaching here means that the no driver was found for given device path, 
	   return empty string */
	driver_name = (*env)->NewStringUTF(env, "");
	if ((driver_name == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
		(*env)->ExceptionClear(env);
		throw_serialcom_exception(env, 3, 0, E_NEWSTRUTFSTR);
		return NULL;
	}
	return driver_name;
}