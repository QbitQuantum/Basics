int main( int argc, char* argv[] )
{
	int SerialNo;
	bool fPlugin, fUnplug, fEject;
	HDEVINFO hdevinfo;
	SP_DEVICE_INTERFACE_DATA devIntData;
	BOOL bresult;
	unique_handle hfile = INVALID_HANDLE_VALUE;

	fPlugin = fUnplug = fEject = false;

	if( argc < 3 ) {
		usage();
	}

	char* arg1 = argv[1];

	if( arg1[0] == '-' ) {
		SerialNo = std::atoi( argv[2] );
		char opt = arg1[1];

		switch( opt ) {
		case 'p':
			fPlugin = true;
			break;
		case 'u':
			fUnplug = true;
			break;
		case 'e':
			fEject = true;
			break;
		default:
			usage();
			break;
		}
	}
	else {
		usage();
	}

	hdevinfo = SetupDiGetClassDevs( &GUID_DEVINTERFACE_RoboBus, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE );
	if( hdevinfo == INVALID_HANDLE_VALUE ) {
		throw std::exception( "SetupDiGetClassDevs failed" );
	}

	memset( &devIntData, 0, sizeof(devIntData) );
	devIntData.cbSize = sizeof(devIntData);


	bresult = SetupDiEnumDeviceInterfaces( hdevinfo, 0, &GUID_DEVINTERFACE_RoboBus, 0, &devIntData );
	if( !bresult ) {
		throw std::exception( "SetupDiEnumDeviceInterface failed", GetLastError() );
	}

    hfile = openBusInterface( hdevinfo, &devIntData );

	if( fPlugin ) {
		ULONG bytes = sizeof(BUSENUM_PLUGIN_HARDWARE) + sizeof(BUS_HARDWARE_IDS);
		std::unique_ptr<BYTE> buffer( new BYTE[bytes] );
		BUSENUM_PLUGIN_HARDWARE* pplugin = (BUSENUM_PLUGIN_HARDWARE*)buffer.get();
		pplugin->Size = sizeof(BUSENUM_PLUGIN_HARDWARE);
		pplugin->SerialNo = SerialNo;
		memcpy( pplugin->HardwareIDs, BUS_HARDWARE_IDS, sizeof(BUS_HARDWARE_IDS) );

		bresult = DeviceIoControl( hfile, IOCTL_BUSENUM_PLUGIN_HARDWARE, pplugin, bytes, NULL, 0, &bytes, NULL );
		if( !bresult ) {
			throw std::exception( "Failed DeviceIoControl", GetLastError() );
		}
	}

	if( fUnplug ) {
		BUSENUM_UNPLUG_HARDWARE unplug;
		ULONG bytes;

		unplug.Size = bytes = sizeof(unplug);
        unplug.SerialNo = SerialNo;
		bresult = DeviceIoControl( hfile, IOCTL_BUSENUM_UNPLUG_HARDWARE, &unplug, bytes, NULL, 0, &bytes, NULL );
		if( !bresult ) {
			throw std::exception( "Failed DeviceIoControl", GetLastError() );
		}
	}

	if( fEject ) {
		BUSENUM_EJECT_HARDWARE eject;
		ULONG bytes;

		eject.Size = bytes = sizeof(eject);
        eject.SerialNo = SerialNo;
		bresult = DeviceIoControl( hfile, IOCTL_BUSENUM_EJECT_HARDWARE, &eject, bytes, NULL, 0, &bytes, NULL );
		if( !bresult ) {
			throw std::exception( "Failed DeviceIoControl", GetLastError() );
		}
	}

    SetupDiDestroyDeviceInfoList( hdevinfo );

	if( hfile != INVALID_HANDLE_VALUE ) {
		CloseHandle( hfile );
	}



    return 0;

}