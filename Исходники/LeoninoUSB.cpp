	__declspec(dllexport) BOOL  __stdcall GetDeviceHandle ( CONST GUID * guidDeviceInterface,PHANDLE hDeviceHandle)
	{	
		BOOL bResult = TRUE;
		HDEVINFO hDeviceInfo;
		SP_DEVINFO_DATA DeviceInfoData;

		SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
		PSP_DEVICE_INTERFACE_DETAIL_DATA pInterfaceDetailData = NULL;

		ULONG requiredLength=0;

		LPTSTR lpDevicePath = NULL;

		DWORD index = 0;

		// Get information about all the installed devices for the specified
		// device interface class.
		hDeviceInfo = SetupDiGetClassDevs( 
			guidDeviceInterface,
			NULL, 
			NULL,
			DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

		if (hDeviceInfo == INVALID_HANDLE_VALUE) 
		{ 
			// ERROR 
			printf("Error SetupDiGetClassDevs: %d.\n", GetLastError());
			goto done;
		}

		//Enumerate all the device interfaces in the device information set.
		DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

		//for (index = 0; SetupDiEnumDeviceInfo(hDeviceInfo, index, &DeviceInfoData); index++)
		if(SetupDiEnumDeviceInfo(hDeviceInfo, 0, &DeviceInfoData))
		{
			//Reset for this iteration
			if (lpDevicePath)
			{
				LocalFree(lpDevicePath);
			}

			if (pInterfaceDetailData)
			{
				LocalFree(pInterfaceDetailData);
			}

			deviceInterfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);

			//Get information about the device interface.
			bResult = SetupDiEnumDeviceInterfaces( 
				hDeviceInfo,
				&DeviceInfoData,
				guidDeviceInterface,
				0, 
				&deviceInterfaceData);

			// Check if last item
			if (GetLastError () == ERROR_NO_MORE_ITEMS)
			{
				//break;
			}

			//Check for some other error
			if (!bResult) 
			{
				printf("Error SetupDiEnumDeviceInterfaces: %d.\n", GetLastError());
				goto done;
			}

			//Interface data is returned in SP_DEVICE_INTERFACE_DETAIL_DATA
			//which we need to allocate, so we have to call this function twice.
			//First to get the size so that we know how much to allocate
			//Second, the actual call with the allocated buffer

			bResult = SetupDiGetDeviceInterfaceDetail(
				hDeviceInfo,
				&deviceInterfaceData,
				NULL, 0,
				&requiredLength,
				NULL);


			//Check for some other error
			if (!bResult) 
			{
				if ((ERROR_INSUFFICIENT_BUFFER==GetLastError()) && (requiredLength>0))
				{
					//we got the size, allocate buffer
					pInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, requiredLength);

					if (!pInterfaceDetailData) 
					{ 
						// ERROR 
						printf("Error allocating memory for the device detail buffer.\n");
						goto done;
					}
				}
				else
				{
					printf("Error SetupDiEnumDeviceInterfaces: %d.\n", GetLastError());
					goto done;
				}
			}

			//get the interface detailed data
			pInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			//Now call it with the correct size and allocated buffer
			bResult = SetupDiGetDeviceInterfaceDetail(
				hDeviceInfo,
				&deviceInterfaceData,
				pInterfaceDetailData,
				requiredLength,
				NULL,
				&DeviceInfoData);

			//Check for some other error
			if (!bResult) 
			{
				printf("Error SetupDiGetDeviceInterfaceDetail: %d.\n", GetLastError());
				goto done;
			}

			//copy device path

			size_t nLength = wcslen (pInterfaceDetailData->DevicePath) + 1;  
			lpDevicePath = (TCHAR *) LocalAlloc (LPTR, nLength * sizeof(TCHAR));
			StringCchCopy(lpDevicePath, nLength, pInterfaceDetailData->DevicePath);

			lpDevicePath[nLength-1] = 0;

			//printf("Device path:  %s\n", lpDevicePath);

		}

		if (!lpDevicePath)
		{
			//Error.
			printf("Error %d.", GetLastError());
			goto done;
		}

		//Open the device
		*hDeviceHandle = CreateFile (
			lpDevicePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (*hDeviceHandle == INVALID_HANDLE_VALUE)
		{
			//Error.
			printf("Error %d.", GetLastError());
			goto done;
		}



done:
		LocalFree(lpDevicePath);
		LocalFree(pInterfaceDetailData);    
		bResult = SetupDiDestroyDeviceInfoList(hDeviceInfo);

		return bResult;
	}	