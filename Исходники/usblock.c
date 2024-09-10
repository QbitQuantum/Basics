INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *lpCmdLine, int cmdShow)
{
	HKEY hKey;
	long ret;
	LPTSTR pszMessage;
	DWORD dwLastError;
	DWORD val=0,valSize,valType;
	DWORD dwStart=3;
	
	
	ret=RegOpenKeyExW(HKEY_LOCAL_MACHINE,USB_KEY,0,KEY_ALL_ACCESS,&hKey);
	if(ret == ERROR_SUCCESS)
		{
			valSize=sizeof(val);
			ret = RegQueryValueExW(hKey,START_KEY,0,&valType,(LPBYTE)&val,&valSize);
			
			if(ret == ERROR_SUCCESS)
				{
					if(val == 3)
						{
							dwStart=4;
							
						}
					else
						{
							dwStart=3;		
						}
					
					ret = RegSetValueExW(hKey,START_KEY,0,REG_DWORD,(LPBYTE)&dwStart,valSize);
							
					if(ret == ERROR_SUCCESS)
					{
						if(dwStart == 4)
							MessageBoxW(0,L"USB lock Success!",L"Message",MB_OK);
						else
							MessageBoxW(0,L"USB Unlock Success!",L"Message",MB_OK);
					}
				}

			RegCloseKey(hKey);
		}
		else
			{
    		dwLastError = GetLastError(); 

    		FormatMessage(
	        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
	        FORMAT_MESSAGE_FROM_SYSTEM |
	        FORMAT_MESSAGE_IGNORE_INSERTS,
	        NULL,
	        dwLastError,
	        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	        (LPTSTR)&pszMessage,
	        0, NULL );
				
				MessageBoxW(0,pszMessage,L"Error",MB_OK);
			}	
			
			
	return 1;
}