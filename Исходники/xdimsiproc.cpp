UINT
pxDiMsiUninstallPnpDevice(
	__in MSIHANDLE hInstall, 
	__in const XDIMSI_PROCESS_RECORD* ProcessRecord)
{
	BOOL reboot = FALSE;
	BOOL success = FALSE;

	while (TRUE) 
	{
		LPWSTR serviceList = NULL;
		LPWSTR infNameList = NULL;

		HRESULT hr = xDiRemoveDevices(
			NULL,
			NULL,
			NULL,
			ProcessRecord->HardwareId,
			DIGCF_ALLCLASSES,
			&serviceList,
			&infNameList);

		if (FAILED(hr) && 0 != ProcessRecord->ErrorNumber)
		{
			pxMsiTraceW(hInstall, 
				L"NdasDiRemoveDevice failed, hardwareId=%s, hr=0x%x\n",
				ProcessRecord->HardwareId, hr);

			UINT response = pxMsiErrorMessageBox(hInstall, ProcessRecord->ErrorNumber, hr);
			switch (response)
			{
			case IDRETRY:
				continue;
			case IDIGNORE:
				break;
			case 0:
			case IDABORT:
			default:
				return ERROR_INSTALL_FAILURE;
			}
		}

		if (XDI_S_REBOOT == hr)
		{
			reboot  = TRUE;
		}

		hr = xDiDeletePnpDriverServices(serviceList);

		if (XDI_S_REBOOT == hr)
		{
			reboot = TRUE;
		}

		for (LPCWSTR infName = infNameList; 
			*infName; 
			infName += lstrlenW(infName) + 1)
		{
			WCHAR infPath[MAX_PATH];

			GetWindowsDirectoryW(infPath, RTL_NUMBER_OF(infPath));
			PathAppendW(infPath, L"INF");
			PathAppend(infPath, infName);

			xDiDeleteDriverFiles(NULL, infPath, XDI_EDF_NO_CLASS_INSTALLER);
			xDiUninstallOEMInf(infNameList, 0);
		}

		break;
	}

	if (reboot) 
	{
		pxMsiQueueScheduleReboot(hInstall);
	}

	return ERROR_SUCCESS;
}