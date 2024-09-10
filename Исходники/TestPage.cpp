BOOLEAN CTestPage::SavePCIConfiguration( BYTE ucBusNumber, BYTE ucDevice )
/////////////////////////////////////////////////////////////////////////////
{
#ifdef USEHARDWARE
	HKEY	hKey;
	DWORD	dwDisposition;
	ULONG	ulValue;
	BYTE	ucDeviceFunction;
	int		i;
	char	szBuffer[ 128 ];

	sprintf( szBuffer, REG_STR_PATH, ucBusNumber, ucDevice );

	ucDeviceFunction = ucDevice << 3;

	RegCreateKeyEx( HKEY_CURRENT_USER, szBuffer, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition );

	ReadConfigurationArea( READ_CONFIG_BYTE, ucBusNumber, ucDeviceFunction, PCI_CS_CACHE_LINE_SIZE, &ulValue );
	ulValue &= 0xFF;
	RegSetValueEx( hKey, "CacheLineSize", 0, REG_DWORD, (LPBYTE)&ulValue, sizeof( ULONG ) );

	ReadConfigurationArea( READ_CONFIG_BYTE, ucBusNumber, ucDeviceFunction, PCI_CS_MASTER_LATENCY, &ulValue );
	ulValue &= 0xFF;
	RegSetValueEx( hKey, "MasterLatency", 0, REG_DWORD, (LPBYTE)&ulValue, sizeof( ULONG ) );

	for( i=0; i<PCI_TYPE0_ADDRESSES; i++ )
	{
		ReadConfigurationArea( 
			READ_CONFIG_DWORD, 
			ucBusNumber, ucDeviceFunction, 
			PCI_CS_BASE_ADDRESS_0+(i*sizeof(ULONG)), 
			&ulValue );
		sprintf( szBuffer, "BAR%d", i );
		RegSetValueEx( hKey, szBuffer, 0, REG_DWORD, (LPBYTE)&ulValue, sizeof( ULONG ) );
	}

	ReadConfigurationArea( READ_CONFIG_BYTE, ucBusNumber, ucDeviceFunction, PCI_CS_INTERRUPT_LINE, &ulValue );
	ulValue &= 0xFF;
	RegSetValueEx( hKey, "InterruptLine", 0, REG_DWORD, (LPBYTE)&ulValue, sizeof( ULONG ) );

	RegFlushKey( hKey );
	RegCloseKey( hKey );

#endif
	return( TRUE );
}