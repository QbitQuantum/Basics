DWORD WINAPI
NetClassInstaller(
	IN DI_FUNCTION InstallFunction,
	IN HDEVINFO DeviceInfoSet,
	IN PSP_DEVINFO_DATA DeviceInfoData OPTIONAL)
{
	SP_DRVINFO_DATA_W DriverInfoData;
	SP_DRVINFO_DETAIL_DATA_W DriverInfoDetail;
	WCHAR SectionName[LINE_LEN];
	HINF hInf = INVALID_HANDLE_VALUE;
	INFCONTEXT InfContext;
	UINT ErrorLine;
	INT CharacteristicsInt;
	DWORD Characteristics;
	LPWSTR BusType = NULL;
	RPC_STATUS RpcStatus;
	UUID Uuid;
	LPWSTR UuidRpcString = NULL;
	LPWSTR UuidString = NULL;
	LONG rc;
	DWORD dwLength;

	if (InstallFunction != DIF_INSTALLDEVICE)
		return ERROR_DI_DO_DEFAULT;

	DPRINT("%lu %p %p\n", InstallFunction, DeviceInfoSet, DeviceInfoData);

	/* Get driver info details */
	DriverInfoData.cbSize = sizeof(SP_DRVINFO_DATA_W);
	if (!SetupDiGetSelectedDriverW(DeviceInfoSet, DeviceInfoData, &DriverInfoData))
	{
		rc = GetLastError();
		DPRINT("SetupDiGetSelectedDriverW() failed with error 0x%lx\n", rc);
		goto cleanup;
	}
	DriverInfoDetail.cbSize = sizeof(SP_DRVINFO_DETAIL_DATA_W);
	if (!SetupDiGetDriverInfoDetailW(DeviceInfoSet, DeviceInfoData, &DriverInfoData, &DriverInfoDetail, sizeof(DriverInfoDetail), NULL)
	 && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
	{
		rc = GetLastError();
		DPRINT("SetupDiGetDriverInfoDetailW() failed with error 0x%lx\n", rc);
		goto cleanup;
	}
	hInf = SetupOpenInfFileW(DriverInfoDetail.InfFileName, NULL, INF_STYLE_WIN4, &ErrorLine);
	if (hInf == INVALID_HANDLE_VALUE)
	{
		rc = GetLastError();
		DPRINT("SetupOpenInfFileW() failed with error 0x%lx\n", rc);
		goto cleanup;
	}
	if (!SetupDiGetActualSectionToInstallW(hInf, DriverInfoDetail.SectionName, SectionName, LINE_LEN, NULL, NULL))
	{
		rc = GetLastError();
		DPRINT("SetupDiGetActualSectionToInstallW() failed with error 0x%lx\n", rc);
		goto cleanup;
	}

	/* Get Characteristics and BusType (optional) from .inf file */
	if (!SetupFindFirstLineW(hInf, SectionName, L"Characteristics", &InfContext))
	{
		rc = GetLastError();
		DPRINT("Unable to find key %S in section %S of file %S (error 0x%lx)\n",
			L"Characteristics", SectionName, DriverInfoDetail.InfFileName, rc);
		goto cleanup;
	}
	if (!SetupGetIntField(&InfContext, 1, &CharacteristicsInt))
	{
		rc = GetLastError();
		DPRINT("SetupGetIntField() failed with error 0x%lx\n", rc);
		goto cleanup;
	}
	Characteristics = (DWORD)CharacteristicsInt;
	if (IsEqualIID(&DeviceInfoData->ClassGuid, &GUID_DEVCLASS_NET))
	{
		if (SetupFindFirstLineW(hInf, SectionName, L"BusType", &InfContext))
		{
			if (!SetupGetStringFieldW(&InfContext, 1, NULL, 0, &dwLength))
			{
				rc = GetLastError();
				DPRINT("SetupGetStringFieldW() failed with error 0x%lx\n", rc);
				goto cleanup;
			}
			BusType = HeapAlloc(GetProcessHeap(), 0, dwLength * sizeof(WCHAR));
			if (!BusType)
			{
				DPRINT("HeapAlloc() failed\n");
				rc = ERROR_NOT_ENOUGH_MEMORY;
				goto cleanup;
			}
			if (!SetupGetStringFieldW(&InfContext, 1, BusType, dwLength, NULL))
			{
				rc = GetLastError();
				DPRINT("SetupGetStringFieldW() failed with error 0x%lx\n", rc);
				goto cleanup;
			}
		}
	}

	/* Create a new UUID */
	RpcStatus = UuidCreate(&Uuid);
	if (RpcStatus != RPC_S_OK && RpcStatus != RPC_S_UUID_LOCAL_ONLY)
	{
		DPRINT("UuidCreate() failed with RPC status 0x%lx\n", RpcStatus);
		rc = ERROR_GEN_FAILURE;
		goto cleanup;
	}
	RpcStatus = UuidToStringW(&Uuid, &UuidRpcString);
	if (RpcStatus != RPC_S_OK)
	{
		DPRINT("UuidToStringW() failed with RPC status 0x%lx\n", RpcStatus);
		rc = ERROR_GEN_FAILURE;
		goto cleanup;
	}

	/* Add curly braces around Uuid */
	UuidString = HeapAlloc(GetProcessHeap(), 0, (2 + wcslen(UuidRpcString)) * sizeof(WCHAR) + sizeof(UNICODE_NULL));
	if (!UuidString)
	{
		DPRINT("HeapAlloc() failed\n");
		rc = ERROR_NOT_ENOUGH_MEMORY;
		goto cleanup;
	}
	wcscpy(UuidString, L"{");
	wcscat(UuidString, UuidRpcString);
	wcscat(UuidString, L"}");

	if (IsEqualIID(&DeviceInfoData->ClassGuid, &GUID_DEVCLASS_NET))
		rc = InstallNetDevice(DeviceInfoSet, DeviceInfoData, UuidString, Characteristics, BusType);
	else if (IsEqualIID(&DeviceInfoData->ClassGuid, &GUID_DEVCLASS_NETCLIENT))
		rc = InstallNetClient();
	else if (IsEqualIID(&DeviceInfoData->ClassGuid, &GUID_DEVCLASS_NETSERVICE))
		rc = InstallNetService();
	else if (IsEqualIID(&DeviceInfoData->ClassGuid, &GUID_DEVCLASS_NETTRANS))
		rc = InstallNetTransport();
	else
	{
		DPRINT("Invalid class guid\n");
		rc = ERROR_GEN_FAILURE;
	}

cleanup:
	if (hInf != INVALID_HANDLE_VALUE)
		SetupCloseInfFile(hInf);
	if (UuidRpcString != NULL)
		RpcStringFreeW(&UuidRpcString);
	HeapFree(GetProcessHeap(), 0, BusType);
	HeapFree(GetProcessHeap(), 0, UuidString);

	if (rc == ERROR_SUCCESS)
		rc = ERROR_DI_DO_DEFAULT;
	DPRINT("Returning 0x%lx\n", rc);
	return rc;
}