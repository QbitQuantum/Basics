////////////////////////////////////////////////////////////////////////////////
//	G e t U S B D e v i c e s
////////////////////////////////////////////////////////////////////////////////
INT GetUSBDevices( INT nMaxDevices, USB_DEVICE_NAME *lpUsbDevices, USB_ERROR_INFO *lpUsbErrorInfo )
{
	int									ii;
	DWORD								dwBytes;
	INT									nDeviceFound;
	HDEVINFO							hDevInfo;
	LPTSTR								lpToken, lpWorkToken;
	GUID								guidUSBDeviceSupport;
	HANDLE								hUsbPrinter;
	SP_DEVICE_INTERFACE_DATA			deviceInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	deviceInterfaceDetailData;
	char								szUsb1284[1024];
	int									nDeviceIndex;
	HINSTANCE							pSetupAPI					= NULL;

	FAR HDEVINFO ( FAR WINAPI *SetupDiGetClassDevs )(CONST GUID *, PCTSTR, HWND, DWORD);
	FAR BOOL ( FAR WINAPI *SetupDiEnumDeviceInterfaces )(HDEVINFO, PSP_DEVINFO_DATA, CONST GUID *,DWORD, PSP_DEVICE_INTERFACE_DATA);
	FAR BOOL ( FAR WINAPI *SetupDiGetDeviceInterfaceDetail )(HDEVINFO, PSP_DEVICE_INTERFACE_DATA, PSP_DEVICE_INTERFACE_DETAIL_DATA, DWORD, PDWORD, PSP_DEVINFO_DATA);
	FAR BOOL ( FAR WINAPI *SetupDiDestroyDeviceInfoList )(HDEVINFO);



	//
	// The functions SetupDiGetClassDevs, SetupDiEnumDeviceInterfaces , 
	// SetupDiGetDeviceInterfaceDetail, SetupDiDestroyDeviceInfoList
	// are supported only on Windows 2000 and above and Windows 98 and above.
	// So link them dynamically to avoid windows errors.
	//
	pSetupAPI = LoadLibrary( "Setupapi" );

	if ( pSetupAPI != NULL )
	{

		SetupDiGetClassDevs = ( HDEVINFO ( WINAPI * )(CONST GUID *, PCTSTR, HWND, DWORD)) GetProcAddress( pSetupAPI, "SetupDiGetClassDevsA" );

		if ( SetupDiGetClassDevs == NULL )
		{
			lpUsbErrorInfo->dwSysLastError = ERROR_INVALID_FUNCTION;
			strcpy( lpUsbErrorInfo->szSysErrorMsg, "ERROR : Unable to get a pointer to SetupDiGetClassDevs");
		    FreeLibrary( pSetupAPI );
			return 0;
		}

		SetupDiEnumDeviceInterfaces = ( BOOL ( WINAPI * )(HDEVINFO, PSP_DEVINFO_DATA, CONST GUID *,DWORD, PSP_DEVICE_INTERFACE_DATA)) GetProcAddress( pSetupAPI, "SetupDiEnumDeviceInterfaces" );

		if ( SetupDiEnumDeviceInterfaces == NULL )
		{
			lpUsbErrorInfo->dwSysLastError = ERROR_INVALID_FUNCTION;
			strcpy( lpUsbErrorInfo->szSysErrorMsg, "ERROR : Unable to get a pointer to SetupDiEnumDeviceInterfaces");
		    FreeLibrary( pSetupAPI );
			return 0;
		}

		SetupDiGetDeviceInterfaceDetail = ( BOOL ( WINAPI * )(HDEVINFO, PSP_DEVICE_INTERFACE_DATA, PSP_DEVICE_INTERFACE_DETAIL_DATA, DWORD, PDWORD, PSP_DEVINFO_DATA)) GetProcAddress( pSetupAPI, "SetupDiGetDeviceInterfaceDetailA" );

		if ( SetupDiGetDeviceInterfaceDetail == NULL )
		{
			lpUsbErrorInfo->dwSysLastError = ERROR_INVALID_FUNCTION;
			strcpy( lpUsbErrorInfo->szSysErrorMsg, "ERROR : Unable to get a pointer to SetupDiGetDeviceInterfaceDetailA");
		    FreeLibrary( pSetupAPI );
			return 0;
		}

		SetupDiDestroyDeviceInfoList = ( BOOL ( WINAPI * )(HDEVINFO)) GetProcAddress( pSetupAPI, "SetupDiDestroyDeviceInfoList" );

		if ( SetupDiDestroyDeviceInfoList == NULL )
		{
			lpUsbErrorInfo->dwSysLastError = ERROR_INVALID_FUNCTION;
			strcpy( lpUsbErrorInfo->szSysErrorMsg, "ERROR : Unable to get a pointer to SetupDiDestroyDeviceInfoList");
		    FreeLibrary( pSetupAPI );
			return 0;
		}
	}
	else
	{
		lpUsbErrorInfo->dwSysLastError = ERROR_INVALID_HANDLE;
		strcpy( lpUsbErrorInfo->szSysErrorMsg, "ERROR : Unable to load Setupapi!");
		return 0;
	}



	//
	// initialize local variables and initialize error
	// struct if a non NULL pointer was passed.
	// 
	nDeviceFound = 0;
	if ( NULL != lpUsbErrorInfo )
		InitError( lpUsbErrorInfo );


	//
	// validate that the user passed in the number of
	// available USE_DEVICE_NAMES to fill with inofrmation.
	//
	if ( 0 == nMaxDevices )
	{	
		if ( NULL != lpUsbErrorInfo )
		{
			lpUsbErrorInfo->dwSysLastError = ERROR_INVALID_DATA;
			strcpy( lpUsbErrorInfo->szSysErrorMsg, "ERROR : nMaxDevices has a value of zero!");
		}
		return 0;
	};

	
	
	//
	// check that we can pass information back to the calling application!
	//
	if ( NULL == lpUsbDevices )
	{
		if ( NULL != lpUsbErrorInfo )
		{
			lpUsbErrorInfo->dwSysLastError = ERROR_INVALID_DATA;
			strcpy( lpUsbErrorInfo->szSysErrorMsg, "ERROR : lpUsbDevices is NULL!" );
		}
		return 0;
	}



	//
	// get a handle to the set of device information returned by the Win32 API
	// functions.  This handle points to an object that is then operated on 
	// by the SetupDiEnumDeviceInterfaces function.
	//
	guidUSBDeviceSupport = GUID_CLASS_USB_DEVICE;
	hDevInfo = SetupDiGetClassDevs(	&guidUSBDeviceSupport,
									0,
									0,
									0x12);	// TODO : Determine the constant
	if ( INVALID_HANDLE_VALUE == hDevInfo )
	{
		if ( NULL != lpUsbErrorInfo )
		{
			// get the last error from system
			lpUsbErrorInfo->dwSysLastError = GetLastError();

			// get the system defined message
			FormatMessage(	FORMAT_MESSAGE_FROM_SYSTEM			|
							FORMAT_MESSAGE_IGNORE_INSERTS,
							NULL,
							lpUsbErrorInfo->dwSysLastError,
							MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
							lpUsbErrorInfo->szSysErrorMsg,
							sizeof(lpUsbErrorInfo->szSysErrorMsg) / sizeof(lpUsbErrorInfo->szSysErrorMsg[0]),
							NULL );
		}
	}


	//
	//
	//
	nDeviceFound = nDeviceIndex = 0;	
	deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);
	for (nDeviceIndex = 0; SetupDiEnumDeviceInterfaces( hDevInfo,
									  NULL,
									  &guidUSBDeviceSupport,
									  nDeviceIndex,
									  &deviceInterfaceData );
		nDeviceIndex++) 
	{



		//
		// determine the amout of memory we need to allocate for the next
		// call to this function
		//
		dwBytes= 0;
		ii = SetupDiGetDeviceInterfaceDetail(	hDevInfo,
												&deviceInterfaceData,
												NULL,
												0,
												&dwBytes,
												NULL );
		if ( 0 == dwBytes )
		{
			//
			// Reinitialize the data for next pass
			// through this loop.
			//
			deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);
			continue;
		}


		
		//Set cbSize in the detailData structure.
		deviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc (dwBytes);
		deviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			
		//
		// get the device path for the current device we are enumerating over.
		//
		ii = SetupDiGetDeviceInterfaceDetail(	hDevInfo,
												&deviceInterfaceData,
												deviceInterfaceDetailData,
												dwBytes, 
												&dwBytes,
												NULL );
		if ( 0 == ii )
		{
			//
			// Free DetailData struct and reinitialize the data for next pass
			//	through this loop.
			//
			free(deviceInterfaceDetailData);
			deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);
			continue;
		}


		//
		// get handle to the device so that we can 
		//
		hUsbPrinter = CreateFile(	deviceInterfaceDetailData->DevicePath,
									GENERIC_READ		| 
										GENERIC_WRITE,
									FILE_SHARE_WRITE	|
										FILE_SHARE_READ,
									NULL,
									OPEN_EXISTING,
									0,
									NULL );


		//
		//
		//
		if ( INVALID_HANDLE_VALUE == hUsbPrinter )
		{
			//
			// Free DetailData struct and reinitialize the data for next pass
			// through this loop.
			//
			free(deviceInterfaceDetailData);
			deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);
			continue;
		}



		//
		//
		//
		dwBytes = 0;
		memset( szUsb1284, 0, sizeof(szUsb1284) );
		ii = DeviceIoControl(	hUsbPrinter,
								IOCTL_USBPRINT_GET_1284_ID,
								NULL,
								0,
								szUsb1284,
								sizeof(szUsb1284),
								&dwBytes,
								NULL );

		//
		//
		//
		CloseHandle( hUsbPrinter );



		//
		// parse the PNP string returned from the device.
		//		
		lpToken = strtok( szUsb1284, PNP_DELIMITOR );
		while ( NULL != lpToken )
		{
			// have the manfacturer.
			lpWorkToken = strstr(lpToken, MFG_TOKEN);
			if (lpWorkToken != NULL)
			{
				strcpy(	lpUsbDevices[nDeviceFound].szDeviceMfg, lpWorkToken + MFG_TOKEN_LEN);
				RTrim( lpUsbDevices[nDeviceFound].szDeviceMfg );
			}

			//	model of the printer
			lpWorkToken = strstr(lpToken, MDL_TOKEN);
			if (lpWorkToken != NULL)
			{
				strcpy(	lpUsbDevices[nDeviceFound].szDevicePdt, lpWorkToken + MDL_TOKEN_LEN );
				RTrim( lpUsbDevices[nDeviceFound].szDevicePdt );
			}


			// next token
			lpToken = strtok( NULL, PNP_DELIMITOR );
		}



		//
		//  if the we don't manage to get BOTH the manufacturer and the product
		// of the USB printer then don't return information back the calling code.
		//
		if (	strlen(lpUsbDevices[nDeviceFound].szDeviceMfg) + 
				strlen(lpUsbDevices[nDeviceFound].szDevicePdt) > 1 )
		{
			nDeviceFound++;
			
			//break after getting the number of devices requested.
			if (nMaxDevices == nDeviceFound)
			{
		        free(deviceInterfaceDetailData);
				break;

			}

		}
		else
		{
			lpUsbDevices[nDeviceFound].szDeviceMfg[0] = 
			lpUsbDevices[nDeviceFound].szDevicePdt[0] = 0;
		}



		//
		// Free DetailData struct and reinitialize the data for next pass
		// through this loop.
		//
        free(deviceInterfaceDetailData);
		deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);

	}

	//
	//Destroy device information set and free all associated memory. 
	//
	SetupDiDestroyDeviceInfoList(hDevInfo);

	//
	//Free setupapi library
	//
    FreeLibrary( pSetupAPI );

	return nDeviceFound;

}