const T_HID_HDL* HidOpen( const char* const my_manufacturer, const char* const my_product )
{
	int f = 0;
	int i = 0;
	ULONG Needed, l;
	GUID HidGuid;
	HDEVINFO DeviceInfoSet;
	HIDD_ATTRIBUTES DeviceAttributes;
	SP_DEVICE_INTERFACE_DATA DevData;
	PSP_INTERFACE_DEVICE_DETAIL_DATA DevDetail;
	//SP_DEVICE_INTERFACE_DETAIL_DATA *MyDeviceInterfaceDetailData;
	HANDLE hHID = NULL;						// USB-IO dev handle
	T_HID_HDL_LOCAL*	libhid_handle = NULL;
	const int my_product_id = MY_PID;

	if( !hHID_DLL ) {
		return NULL;
	}

	DeviceAttributes.Size = sizeof(HIDD_ATTRIBUTES);
	DevData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	HidD_GetHidGuid( &HidGuid );

	DeviceInfoSet =
		SetupDiGetClassDevs( &HidGuid, NULL, NULL,
							DIGCF_PRESENT | DIGCF_DEVICEINTERFACE );

	while( SetupDiEnumDeviceInterfaces( DeviceInfoSet, 0, &HidGuid, i++, &DevData ) ) {
		SetupDiGetDeviceInterfaceDetail( DeviceInfoSet, &DevData, NULL, 0, &Needed, 0 );
		l = Needed;
		DevDetail =
			(SP_DEVICE_INTERFACE_DETAIL_DATA *) GlobalAlloc( GPTR, l + 4 );
		DevDetail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		SetupDiGetDeviceInterfaceDetail( DeviceInfoSet, &DevData, DevDetail,
										l, &Needed, 0 );

		hHID = CreateFile( DevDetail->DevicePath,
						   GENERIC_READ | GENERIC_WRITE,
						   FILE_SHARE_READ | FILE_SHARE_WRITE,
						   NULL, OPEN_EXISTING,
//						   FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING,
						   0, NULL );

		GlobalFree( DevDetail );

		if( hHID == INVALID_HANDLE_VALUE ) {	// Can't open a device
			continue;
		}
		HidD_GetAttributes( hHID, &DeviceAttributes );

		// HIDaspかどうか調べる.
		if( (DeviceAttributes.VendorID == MY_VID)
		 && (DeviceAttributes.ProductID == my_product_id)
		 && (check_product_string( hHID, my_manufacturer, my_product ) == 1)
		 ) {
			f = 1;				// 発見された.
			libhid_handle = malloc( sizeof(T_HID_HDL_LOCAL) );
			if( libhid_handle ) {
				libhid_handle->handle = hHID;
			}
			else {
				CloseHandle( hHID );
				hHID = NULL;
			}
			break;
		} else {
			// 違ったら閉じる
			CloseHandle( hHID );
			hHID = NULL;
		}
	}
	SetupDiDestroyDeviceInfoList( DeviceInfoSet );

	return (T_HID_HDL*)libhid_handle;
}