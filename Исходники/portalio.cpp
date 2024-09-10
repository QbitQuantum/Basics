BOOL OpenPortalHandleFromGUID(GUID guid, PHANDLE phPortalHandle)
{
	int memberIndex = 0;
	BOOL bResult = TRUE;
	HDEVINFO hDevInfo;
	SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA pInterfaceDetailData = NULL;
	HIDD_ATTRIBUTES attributes;

	ULONG requiredLength=0;
	
	hDevInfo = SetupDiGetClassDevs(&guid, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	deviceInterfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
	*phPortalHandle = NULL;

	for(memberIndex = 0;
		SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &guid, memberIndex, &deviceInterfaceData);
		memberIndex++)
	{
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &deviceInterfaceData, NULL, 0, &requiredLength, NULL);

		//we got the size, allocate buffer
		pInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, requiredLength);
		assert(pInterfaceDetailData);

		//get the interface detailed data
		pInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &deviceInterfaceData, pInterfaceDetailData, requiredLength, &requiredLength, NULL))
		{
			continue;
		}

		*phPortalHandle = CreateFile (
			pInterfaceDetailData->DevicePath,
			GENERIC_EXECUTE | GENERIC_ALL,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			NULL);

		LocalFree(pInterfaceDetailData); 
		pInterfaceDetailData = NULL;

		if(guid == xbox_guid) {
			break; // we are done. xbox_guid does not have HID attributes
		}

		if (*phPortalHandle != INVALID_HANDLE_VALUE)
		{
			if (HidD_GetAttributes(*phPortalHandle , &attributes))
			{
				if (((attributes.VendorID == 0x12ba) || (attributes.VendorID == 0x54c)) || (attributes.VendorID == 0x1430))
				{
					if ((attributes.ProductID == 0x150) || (attributes.ProductID == 0x967))
					{
						break;  // found the portal. leave the handle open
					}
				}
			}
			CloseHandle(*phPortalHandle);
			*phPortalHandle = NULL;
		}
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return (*phPortalHandle != NULL);
}