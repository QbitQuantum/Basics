std::list<ADAPTER_INFO>
KLOP_GetAdapterList()
{
	std::list<ADAPTER_INFO> RetList;
	ADAPTER_INFO	AI;	
	HKEY			hKey = NULL;
	FILETIME		ftLastWriteTime;      // last write time 
	CHAR			achKey[MAX_PATH]; 
	wchar_t			wchKey[MAX_PATH];
	ULONG			KeyLength;
	int				i;
	DWORD			retCode;

	if ( KLOP_isWinNT() )
	{
		/*
		if ( ERROR_SUCCESS == RegOpenKey( HKEY_LOCAL_MACHINE, NT_ADAPTERS_KEY, &hKey ) )
		{
			for (i = 0, retCode = ERROR_SUCCESS; retCode == ERROR_SUCCESS; i++ )
			{ 
				KeyLength = MAX_PATH;

				retCode = RegEnumKeyExW(hKey, i, wchKey, &KeyLength, NULL, NULL, NULL, &ftLastWriteTime );

				if ( ERROR_SUCCESS == retCode )
				{
					memset ( &AI , 0, sizeof ( AI ) );
					wcscpy ( (wchar_t*)AI.AdapterBuffer, L"\\Device\\");
					wcscat ( (wchar_t*)AI.AdapterBuffer, wchKey );
					AI.AdapterNameSize = ( wcslen ( (wchar_t*)AI.AdapterBuffer ) + 1 ) << 1;
					AI.LocalIp = 0;

					RetList.push_back( AI );
				}
			} 
		}
		else
		*/
		{
			// Winnt4.0
			if ( ERROR_SUCCESS == RegOpenKey( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\NetworkCards", &hKey ) )
			{
				for ( i = 0, retCode = ERROR_SUCCESS; retCode == ERROR_SUCCESS; i++ )
				{
					HKEY hSubKey = NULL;
					KeyLength = MAX_PATH;
					retCode = RegEnumKeyExW(hKey, i, wchKey, &KeyLength, NULL, NULL, NULL, &ftLastWriteTime );
					
					if ( retCode == ERROR_SUCCESS )
					{
						retCode = RegOpenKeyW(hKey, wchKey, &hSubKey );
					}

					if ( retCode == ERROR_SUCCESS )
					{			
						KeyLength = MAX_PATH;
						DWORD	type = REG_SZ;

						if ( ERROR_SUCCESS == RegQueryValueExW( 
							hSubKey, 
							L"ServiceName", 
							NULL,
							&type,
							(LPBYTE)wchKey, 
							(ULONG*)&KeyLength ) )
						{
							memset ( &AI , 0, sizeof ( AI ) );
							wcscpy ( (wchar_t*)AI.AdapterBuffer, L"\\Device\\");
							wcscat ( (wchar_t*)AI.AdapterBuffer, wchKey );
							AI.AdapterNameSize = ( wcslen ( (wchar_t*)AI.AdapterBuffer ) + 1 ) << 1;
							AI.LocalIp = 0;
							
							// Если открывается и не Hidden, тогда добавляем для проверки.
							if ( scan( (wchar_t*)wchKey ) && !IsHidden(hSubKey) )
								RetList.push_back( AI );
						}
					}

					if ( hSubKey )
						RegCloseKey( hSubKey );
				}
			}			
		}
	}
	else
	{
		if ( ERROR_SUCCESS == RegOpenKey( HKEY_LOCAL_MACHINE, W9X_ADAPTER_KEY, &hKey ) )
		{			
			for (i = 0, retCode = ERROR_SUCCESS; retCode == ERROR_SUCCESS; i++ )
			{ 
				KeyLength = MAX_PATH;

				retCode = RegEnumKeyExA(hKey, i, achKey, &KeyLength, NULL, NULL, NULL, &ftLastWriteTime);
				
				if ( ERROR_SUCCESS == retCode )
				{
					memset ( &AI , 0, sizeof ( AI ) );					
					strcpy ( AI.AdapterBuffer, achKey );
					AI.AdapterNameSize = strlen ( achKey ) + 1;
					AI.LocalIp = 0;

					RetList.push_back( AI );
				}				
			} 
		}
	}

	if ( hKey )
	{
		RegCloseKey( hKey );
	}

	return RetList;
}