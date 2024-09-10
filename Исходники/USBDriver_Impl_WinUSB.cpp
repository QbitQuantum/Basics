/* There are not words for how much I hate Microsoft APIs. -- vyhd */
bool USBDriver_Impl_WinUSB::Open( int iVendorID, int iProductID )
{
	// get a set of all the devices currently on the system
	HDEVINFO hDeviceInfo = SetupDiGetClassDevs( NULL, NULL, NULL, DIGCF_PRESENT );

	if( hDeviceInfo == INVALID_HANDLE_VALUE )
	{
		LOG->Trace( "WinUSB: SetupDiGetClassDevs failed (error %i)", GetLastError() );
		return false;
	}

	SP_DEVINFO_DATA DeviceInfoData;
	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
	PSP_DEVICE_INTERFACE_DATA pInterfaceDetailData = NULL;

	LPTSTR lpDevicePath = NULL;

	for( int i = 0; SetupDiEnumDeviceInfo(hDeviceInfo, i, &DeviceInfoData); ++i )
	{
		if( lpDevicePath )
			LocalFree( lpDevicePath );
		if( pDeviceInterfaceData )
			LocalFree( pDeviceInterfaceData );

		DeviceInterfaceData.czSize = sizeof(SP_DEVICE_INTERFACE_DATA);

		bool bSuccess = SetupDiEnumDeviceInterfaces( hDeviceInfo, &DeviceInfoData, NULL, i, &DeviceInterfaceData );

		if( GetLastError() == ERROR_NO_MORE_ITEMS )
			break;

		if( !bSuccess )
		{
			LOG->Warn( "SetupDiEnumDeviceInterfaces failed with %d", GetLastError() );
			break;
		}

		int iRequiredLength = -1;

		bResult = SetupDiGetDeviceInterfaceDetail( hDeviceInfo, &DeviceInterfaceData, NULL, 0, &iRequiredLength, NULL );

		if( !bResult && GetLastError() == ERROR_INSUFFICIENT_BUFFER )
		{
			pInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, iRequiredLength);

			if( !pInterfaceDetailData )
			{
				LOG->Warn( "Error allocating pInterfaceDetailData." );
				break;
			}
		}

		if( pInterfaceDetailSize )
			pInterfaceDetailSize->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		else
			LOG->Warn( "XXX pInterfaceDetailSize is NULL, assumed not NULL" );

		bResult = SetupDiGetDeviceInterfaceDetail( hDeviceInfo, &DeviceInterfaceData, pInterfaceDetailData, iRequiredLength, NULL, &DeviceInfoData );

		if( !bResult )
		{
			LOG->Warn( "SetupDiGetDeviceInterfaceDetai: %d", GetLastError() );
			break;
		}

		
	return SetupDiDestroyDeviceInfoList( hDeviceInfo );
}

void USBDriver_Impl_WinUSB::Close()
{
}

int USBDriver_Impl_WinUSB::ControlMessage( int iType, int iRequest, int iValue, int iIndex, char *pData, int iSize, int iTimeout )
{
	// TODO: use WinUsb_SetPipePolicy to set timeout?
	WINUSB_SETUP_PACKET msg;
	msg.RequestType = iType;
	msg.Request = iRequest;
	msg.Value = iValue;
	msg.Index = iIndex;
	msg.Length = iSize;

	int iRet = -1;

	// TODO: are we sure that iRet will stay -1 when the call fails?
	WinUsb_ControlTransfer( m_pDevice, &msg, pData, iSize, &iRet );
	return iRet;
}