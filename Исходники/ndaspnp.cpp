HRESULT
CNdasServiceDeviceEventHandler::pRegisterLogicalUnits()
{
	HRESULT hr;

	HDEVINFO devInfoSet = SetupDiGetClassDevsW(
		NULL,
		NULL,
		NULL,
		DIGCF_ALLCLASSES | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (INVALID_HANDLE_VALUE == devInfoSet)
	{
		hr = HRESULT_FROM_SETUPAPI(GetLastError());
		XTLTRACE2(NDASSVC_PNP, TRACE_LEVEL_ERROR,
			"SetupDiGetClassDevsW failed, hr=0x%X\n", hr);
		return hr;
	}

	SP_DEVINFO_DATA devInfoData;

	for (DWORD index = 0; ; ++index)
	{
		devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
		BOOL success = SetupDiEnumDeviceInfo(devInfoSet, index, &devInfoData);
		if (!success)
		{
			if (ERROR_NO_MORE_ITEMS != GetLastError())
			{
				hr = HRESULT_FROM_SETUPAPI(GetLastError());
				XTLTRACE2(NDASSVC_PNP, TRACE_LEVEL_ERROR,
					"SetupDiEnumDeviceInfo failed, hr=0x%X\n", hr);
			}
			break;
		}
		devInfoData.ClassGuid;
	}

	const struct {
		LPCGUID Guid;
		LPCSTR TypeName;
	} LogicalUnitInterfaces[] = {
		&GUID_DEVINTERFACE_DISK, "DISK",
		&GUID_DEVINTERFACE_CDROM, "CDROM",
		&GUID_DEVINTERFACE_TAPE, "TAPE",
		&GUID_DEVINTERFACE_WRITEONCEDISK, "WRITEONCEDISK",
		&GUID_DEVINTERFACE_MEDIUMCHANGER, "MEDIUMCHANGER",
		&GUID_DEVINTERFACE_CDCHANGER, "CDCHANGER",
	};

	for (DWORD i = 0; i < RTL_NUMBER_OF(LogicalUnitInterfaces); ++i)
	{
		XTLTRACE2(NDASSVC_PNP, TRACE_LEVEL_WARNING,
			"Enumerating %hs...\n", LogicalUnitInterfaces[i].TypeName);

		pRegisterLogicalUnit(
			devInfoSet, 
			LogicalUnitInterfaces[i].Guid);
	}

	XTLVERIFY( SetupDiDestroyDeviceInfoList(devInfoSet) );

	return S_OK;
}