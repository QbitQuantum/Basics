bool WindowsTimestamper::HWTimestamper_init( InterfaceLabel *iface_label, OSNetworkInterface *net_iface ) {
	char network_card_id[64];
	LinkLayerAddress *addr = dynamic_cast<LinkLayerAddress *>(iface_label);
	if( addr == NULL ) return false;
	PIP_ADAPTER_INFO pAdapterInfo;
	IP_ADAPTER_INFO AdapterInfo[32];       // Allocate information for up to 32 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo( AdapterInfo, &dwBufLen );
	if( dwStatus != ERROR_SUCCESS ) return false;

	for( pAdapterInfo = AdapterInfo; pAdapterInfo != NULL; pAdapterInfo = pAdapterInfo->Next ) {
		if( pAdapterInfo->AddressLength == ETHER_ADDR_OCTETS && *addr == LinkLayerAddress( pAdapterInfo->Address )) { 
			break;
		}
	}

	if( pAdapterInfo == NULL ) return false;

	if( strstr( pAdapterInfo->Description, NANOSECOND_CLOCK_PART_DESCRIPTION ) != NULL ) {
		netclock_hz.QuadPart = NETCLOCK_HZ_NANO;
	} else {
		netclock_hz.QuadPart = NETCLOCK_HZ_OTHER;
	}
	fprintf( stderr, "Adapter UID: %s(%s)\n", pAdapterInfo->AdapterName, pAdapterInfo->Description+(strlen(pAdapterInfo->Description)-7));
	PLAT_strncpy( network_card_id, NETWORK_CARD_ID_PREFIX, 63 );
	PLAT_strncpy( network_card_id+strlen(network_card_id), pAdapterInfo->AdapterName, 63-strlen(network_card_id) );

	miniport = CreateFile( network_card_id,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, 0, NULL );
	if( miniport == INVALID_HANDLE_VALUE ) return false;

	tsc_hz.QuadPart = getTSCFrequency( 1000 );
	if( tsc_hz.QuadPart == 0 ) {
		return false;
	}

	return true;
}