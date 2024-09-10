//
// If succeeded, returns the device file of the LANSCSI Bus Enumerator
// If failed, return INVALID_HANDLE_VALUE
//
static HANDLE OpenBusInterface(VOID)
{
	BOOL fSuccess = FALSE;
	DWORD err = ERROR_SUCCESS;
	HANDLE hDevice = INVALID_HANDLE_VALUE;
    HDEVINFO hDevInfoSet = INVALID_HANDLE_VALUE;
	SP_INTERFACE_DEVICE_DATA devIntfData = {0};
    PSP_INTERFACE_DEVICE_DETAIL_DATA devIntfDetailData = NULL;
    ULONG predictedLength = 0;
    ULONG requiredLength = 0;

	hDevInfoSet = SetupDiGetClassDevs (
		(LPGUID)&GUID_LANSCSI_BUS_ENUMERATOR_INTERFACE_CLASS,
		NULL, // Define no enumerator (global)
		NULL, // Define no
		(DIGCF_PRESENT | // Only Devices present
		DIGCF_INTERFACEDEVICE)); // Function class devices.

    if (INVALID_HANDLE_VALUE == hDevInfoSet)
    {
		DebugPrintErrEx(_T("OpenBusInterface: SetupDiGetClassDevs failed: "));
		goto cleanup;
    }

    devIntfData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);

	fSuccess = SetupDiEnumDeviceInterfaces (
		hDevInfoSet,
		0, // No care about specific PDOs
		(LPGUID)&GUID_LANSCSI_BUS_ENUMERATOR_INTERFACE_CLASS,
		0, //
		&devIntfData);

	if (!fSuccess) {
		DebugPrintErrEx(_T("OpenBusInterface: SetupDiEnumDeviceInterfaces failed: "));
		if (ERROR_NO_MORE_ITEMS == GetLastError()) {
			DebugPrint(1, _T("OpenBusInterface: Interface")
				_T(" GUID_LANSCSI_BUS_ENUMERATOR_INTERFACE_CLASS is not registered.\n"));
		}
		goto cleanup;
	}

	fSuccess = SetupDiGetInterfaceDeviceDetail (
            hDevInfoSet,
            &devIntfData,
            NULL, // probing so no output buffer yet
            0, // probing so output buffer length of zero
            &requiredLength,
            NULL // not interested in the specific dev-node
			);

	if (!fSuccess && ERROR_INSUFFICIENT_BUFFER != GetLastError()) {
		DebugPrintErrEx(_T("OpenBusInterface: SetupDiGetInterfaceDeviceDetail failed: "));
		goto cleanup;
	}

    predictedLength = requiredLength;

	devIntfDetailData = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, predictedLength);
	devIntfDetailData->cbSize = sizeof (SP_INTERFACE_DEVICE_DETAIL_DATA);
    
	fSuccess = SetupDiGetInterfaceDeviceDetail(
		hDevInfoSet,
		&devIntfData,
		devIntfDetailData,
		predictedLength,
		&requiredLength,
		NULL);

	if (!fSuccess) {
		DebugPrintErrEx(_T("OpenBusInterface: SetupDiGetInterfaceDeviceDetail failed: "));
		goto cleanup;
	}

	DebugPrint(3, _T("OpenBusInterface: Opening %s\n"), devIntfDetailData->DevicePath);

    hDevice = CreateFile (
		devIntfDetailData->DevicePath,
		GENERIC_READ | GENERIC_WRITE,
		0, // FILE_SHARE_READ | FILE_SHARE_WRITE
		NULL, // no SECURITY_ATTRIBUTES structure
		OPEN_EXISTING, // No special create flags
		0, // No special attributes
		NULL); // No template file

    if (INVALID_HANDLE_VALUE == hDevice) {
		DebugPrintErrEx(_T("OpenBusInterface: Device not ready: "));
		goto cleanup;
    }
    
	DebugPrint(3, _T("OpenBusInterface: Device file %s opened successfully.\n"),
		devIntfDetailData->DevicePath);

cleanup:

	err = GetLastError();

	if (INVALID_HANDLE_VALUE != hDevInfoSet) {
		SetupDiDestroyDeviceInfoList(hDevInfoSet);
	}

	if (NULL != devIntfDetailData) {
		HeapFree(GetProcessHeap(), 0, devIntfDetailData);
	}

	SetLastError(err);

	return hDevice;
}