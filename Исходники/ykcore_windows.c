void * _ykusb_open_device(int vendor_id, int *product_ids, size_t pids_len)
{
	HDEVINFO hi;
	SP_DEVICE_INTERFACE_DATA di;
	PSP_DEVICE_INTERFACE_DETAIL_DATA pi;
	int i, numDev = 0;
	LPTSTR path = 0;
	DWORD len, rc;
	HANDLE ret_handle = NULL;

	yk_errno = YK_EUSBERR;

	hi = SetupDiGetClassDevs(&GUID_DEVINTERFACE_KEYBOARD, 0, 0,
				 DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hi == INVALID_HANDLE_VALUE)
		return NULL;

	di.cbSize = sizeof (SP_DEVICE_INTERFACE_DATA);

	for (i = 0; i < 1000; i++) {
		if (!SetupDiEnumDeviceInterfaces(hi, 0, &GUID_DEVINTERFACE_KEYBOARD, i, &di))
			break;

		if (SetupDiGetDeviceInterfaceDetail(hi, &di, 0, 0, &len, 0) || GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			break;

		pi = malloc (len);
		if (!pi) {
			yk_errno = YK_ENOMEM;
			goto done;
		}
		pi->cbSize = sizeof (SP_DEVICE_INTERFACE_DETAIL_DATA);

		rc = SetupDiGetDeviceInterfaceDetail(hi, &di, pi, len, &len, 0);
		if (rc) {
			HANDLE m_handle;

			m_handle = CreateFile(pi->DevicePath, GENERIC_WRITE,
					      FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
			if (m_handle != INVALID_HANDLE_VALUE) {
				HIDD_ATTRIBUTES devInfo;

				if (HidD_GetAttributes(m_handle, &devInfo)) {
					if (devInfo.VendorID == vendor_id) {
						size_t j;
						for (j = 0; j < pids_len; j++) {
							if (devInfo.ProductID == product_ids[j]) {
								if(ret_handle == NULL) {
									ret_handle = m_handle;
									break;
								} else {
									yk_errno = YK_EMORETHANONE;
									ret_handle = NULL;
									CloseHandle (m_handle);
									goto done;
								}
							}
						}
					}
				}
			}
			if(ret_handle == NULL) {
				CloseHandle (m_handle);
			}
		}

		free (pi);
	}
	if(ret_handle != NULL) {
		goto done;
	}

	yk_errno = YK_ENOKEY;

done:
	SetupDiDestroyDeviceInfoList(hi);
	return ret_handle;
}