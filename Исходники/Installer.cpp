int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	HKL kl;
	MessageBox(NULL,"DEBUG\n","Debug",0);
	HKEY hk = NULL;
	if( ERROR_SUCCESS != RegCreateKeyEx( HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\New Chewing IM", 0, 
			NULL, 0, KEY_ALL_ACCESS , NULL, &hk, NULL) )
		hk = NULL;
	printf("DEBUG\n");
	if( strstr( lpCmdLine, "/uninstall" ) )
	{
	
		char temp[1024];
		_gen_event_name(temp, sizeof(temp), "ChewingServer");
		HWND hwnd = FindWindow(temp, NULL);
		if ( hwnd ) {
			SendMessage(hwnd, WM_DESTROY, 0, 0);
		}


		if( hk )
		{
			DWORD type = REG_DWORD, size = sizeof(DWORD);
			if(	ERROR_SUCCESS == RegQueryValueEx( hk, "KeyboardLayout", 0, &type, (LPBYTE)&kl, &size ) )
			{
				UnloadKeyboardLayout( kl );
				char klstr[10];
				wsprintf( klstr, "%X", kl );
				char regpath[256];
				lstrcpy( regpath, "Keyboard Layout\\Preload" );
				HKEY hk2 = NULL;

				// Windows NT only, 9x will be supported in the future
				if( (GetVersion() < 0x80000000) )
				{
					if( ERROR_SUCCESS == RegOpenKey( HKEY_CURRENT_USER, regpath, &hk2 ) )
					{
						for( int i = 1; i <= 100; ++i )
						{
							char num[4];
							wsprintf( num, "%d", i );
							type = REG_SZ;	size = sizeof(regpath);
							if(	ERROR_SUCCESS != RegQueryValueEx( hk2, num, 0, &type, (LPBYTE)regpath, &size ) )
								continue;
							if( 0 == lstrcmp( regpath, klstr ) )
							{
								RegDeleteValue( hk2, num );
								break;
							}
						}
						RegCloseKey(hk2);
					}
				}

				wsprintf( regpath, "SYSTEM\\CurrentControlSet\\Control\\Keyboard Layouts\\%s", klstr );
				RegDeleteKey( HKEY_LOCAL_MACHINE, regpath );
			}
		}
	}
	else if ( strstr( lpCmdLine, "/privilege" ) )
	{
		enable_access("ch_index.dat");
		enable_access("dict.dat");
		enable_access("us_freq.dat");
		enable_access("ph_index.dat");
		enable_access("fonetree.dat");
	}
	else
	{
		char path[MAX_PATH];
		GetSystemDirectory(path, MAX_PATH);

		lstrcat( path, "\\Chewing.ime" );
		printf("Install Path:%s\n",path);
		kl = ImmInstallIME( path, 
			(GetVersion() < 0x80000000) ? "中文 (繁體) - 新酷音輸入法" : "新酷音輸入法" );

		printf("Imm Install IME Result: %d\n",kl);
		if( hk )
			RegSetValueEx( hk, "KeyboardLayout", 0, REG_DWORD, (LPBYTE)&kl, sizeof(DWORD) );
	}

	RegCloseKey( hk );

	return 0;
}