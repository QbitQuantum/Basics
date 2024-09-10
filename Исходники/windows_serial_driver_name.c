/*
 * Check if the given COM port name belongs to a multi port serial adaptor device. If yes, get its driver name
 * and return to caller.
 *
 * Return 1 if found, 0 if not found, -1 if an error occurs (also throws exception in this case).
 */
int get_driver_com_port_multiportadaptor(JNIEnv *env, const jchar *port_name, TCHAR *driver_name) {

	int x = 0;
	BOOL ret = FALSE;
	LONG status = 0;
	DWORD error_code = 0;
	DWORD size = 0;
	DWORD regproptype;
	DWORD charbuffer_size = 0;
	DWORD driver_name_size = 0;
	ULONG buffer_size = 0;
	DWORD multiport_member_index = 0;
	HDEVINFO multiport_dev_info_set;
	SP_DEVINFO_DATA multiport_dev_instance;
	ULONG devprop_buffer_size = 0;
	DEVPROPTYPE proptype;
	CONFIGRET cmret = 0;
	DEVINST firstchild = 0;
	DEVINST next_sibling = 0;
	DEVINST current_sibling = 0;

	/* size of these buffers is hardcoded in functions using them */
	TCHAR buffer[1024];
	TCHAR devprop_buffer[1024];
	TCHAR keybuf[1024];
	TCHAR charbuffer[128];
	char cmerror[256];

	/* get information set for all multi port serial adaptor devices matching the GUID */
	multiport_dev_info_set = SetupDiGetClassDevs(&GUID_MULTIPORT_SERIAL_ADAPTOR_DEVICE, NULL, NULL, DIGCF_DEVICEINTERFACE);
	if (multiport_dev_info_set == INVALID_HANDLE_VALUE) {
		SetupDiDestroyDeviceInfoList(multiport_dev_info_set);
		throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(GetLastError()), NULL);
		return -1;
	}

	/* enumerate all devices in this information set */
	multiport_member_index = 0;
	while (1) {
		ZeroMemory(&multiport_dev_instance, sizeof(multiport_dev_instance));
		multiport_dev_instance.cbSize = sizeof(multiport_dev_instance);

		/* from information set, get device by index */
		ret = SetupDiEnumDeviceInfo(multiport_dev_info_set, multiport_member_index, &multiport_dev_instance);
		if (ret == FALSE) {
			error_code = GetLastError();
			if (error_code == ERROR_NO_MORE_ITEMS) {
				break;
			}else {
				SetupDiDestroyDeviceInfoList(multiport_dev_info_set);
				throw_serialcom_exception(env, 4, HRESULT_FROM_SETUPAPI(error_code), NULL);
				return -1;
			}
		}

		/* for this device find its instance ID (USB\VID_04D8&PID_00DF\000098037)
		 * this is variable 'Device Instance Path' in device manager. */
		cmret = CM_Get_Device_ID(multiport_dev_instance.DevInst, buffer, 1024, 0);
		if (cmret != CR_SUCCESS) {
			SetupDiDestroyDeviceInfoList(multiport_dev_info_set);
			_snprintf_s(cmerror, 256, 256, "CM_Get_Device_ID CR_xxxx error code : 0x%X\0", cmret);
			throw_serialcom_exception(env, 3, 0, cmerror);
			return -1;
		}

		/* get its COM port name/number for this device */
		memset(keybuf, '\0', 1024);
		_stprintf_s(keybuf, 1024, TEXT("SYSTEM\\CurrentControlSet\\Enum\\%s\\Device Parameters"), buffer);

		charbuffer_size = sizeof(charbuffer);
		memset(charbuffer, '\0', 128);
		/* ignore error as some devices might not have portname registry key */
		status = RegGetValue(HKEY_LOCAL_MACHINE, keybuf, TEXT("PortName"), RRF_RT_REG_SZ, NULL, (PVOID)charbuffer, &charbuffer_size);
		if (status == ERROR_SUCCESS) {
			/* match port name */
			ret = _tcsicmp(charbuffer, port_name);
			if (ret == 0) {
				/* get driver name */
				memset(keybuf, '\0', 1024);
				_stprintf_s(keybuf, 1024, TEXT("SYSTEM\\CurrentControlSet\\Enum\\%s"), buffer);

				/* HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\XXXX\XXX\XXX\Service */
				charbuffer_size = sizeof(charbuffer);
				memset(charbuffer, '\0', 128);
				status = RegGetValue(HKEY_LOCAL_MACHINE, keybuf, TEXT("Service"), RRF_RT_REG_SZ, NULL, (PVOID)charbuffer, &charbuffer_size);
				if (status != ERROR_SUCCESS) {
					SetupDiDestroyDeviceInfoList(multiport_dev_info_set);
					throw_serialcom_exception(env, 4, GetLastError(), NULL);
					return -1;
				}

				/* populate array to be returned to caller */
				memset(driver_name, '\0', 128);
				for (x = 0; x < _tcslen(charbuffer); x++) {
					driver_name[x] = charbuffer[x];
				}

				/* clean up and return 1 to indicate driver found */
				SetupDiDestroyDeviceInfoList(multiport_dev_info_set);
				return 1;
			}
		}

		/* increment to get and examine the next multiport device for COM ports class */
		multiport_member_index++;
	}

	/* reaching here means given COM port does not belong to multi-port serial adaptor device */
	SetupDiDestroyDeviceInfoList(multiport_dev_info_set);
	return 0;
}