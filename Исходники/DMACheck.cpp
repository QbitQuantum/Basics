static bool CheckRegKeyWXP(bool& dmaDisabled, std::vector<std::string>& dmaDisabledlist)
{
	dmaDisabled = false;
	HKEY hKey;
	LONG retCode = ERROR_SUCCESS;
	//HKLM\HARDWARE\DEVICEMAP\Scsi
	if(ERROR_SUCCESS != RegOpenKeyExA( HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\Scsi",
		0, KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hKey ))
		return false;

	char keyBuf[MAX_VALUE_NAME];
	DWORD max_path = MAX_VALUE_NAME;

	retCode = RegEnumKeyExA(hKey, 0, keyBuf, &max_path, 0, 0, 0, 0);
	if(retCode != ERROR_SUCCESS) 
	{
		RegCloseKey(hKey);
		return false;
	}	

	HKEY hPortKey;
	for(DWORD nPort=1, retCode=ERROR_SUCCESS; retCode==ERROR_SUCCESS; nPort++)
	{
		//HKLM\HARDWARE\DEVICEMAP\Scsi\Scsi Port 0...
		if( ERROR_SUCCESS == RegOpenKeyExA(hKey, keyBuf, 0, KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hPortKey) )
		{
			size_t dmaValue = 0;
			DWORD size = sizeof(DWORD);
			//DMAEnabled
			if( ERROR_SUCCESS != RegQueryValueExA(hPortKey, "DMAEnabled", 0, 0, (LPBYTE)&dmaValue, &size) )
			{
				RegCloseKey(hPortKey);
				RegCloseKey(hKey);
				return false;
			}
			if(dmaValue == 0x0)
			{
				dmaDisabled = true;
				HKEY hBusKey;
				for(DWORD nBus=0,retCode=ERROR_SUCCESS;retCode==ERROR_SUCCESS;nBus++)
				{
					max_path = MAX_VALUE_NAME;
					keyBuf[0] = '\0';
					retCode = RegEnumKeyExA(hPortKey, nBus, keyBuf, &max_path, 0, 0, 0, 0);
					if( retCode == ERROR_SUCCESS )
					{
						//HKLM\HARDWARE\DEVICEMAP\Scsi\Scsi Port 0\Scsi Bus 0...
						if( ERROR_SUCCESS == RegOpenKeyExA(hPortKey, keyBuf, 0, KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hBusKey) )
						{
							HKEY hTargetKey;
							for(DWORD nTarget=0,retCode=ERROR_SUCCESS;retCode==ERROR_SUCCESS;nTarget++)
							{
								max_path = MAX_VALUE_NAME;
								keyBuf[0] = '\0';
								retCode = RegEnumKeyExA(hBusKey, nTarget, keyBuf, &max_path, 0, 0, 0, 0);
								if( retCode==ERROR_SUCCESS )
								{
									std::string targetValue(keyBuf);
									if(targetValue.find("Target Id")==std::string::npos)
										continue;
									//HKLM\HARDWARE\DEVICEMAP\Scsi\Scsi Port 0\Scsi Bus 0\Target Id 0...
									targetValue += "\\Logical Unit Id 0";
									if( ERROR_SUCCESS == RegOpenKeyExA(hBusKey, targetValue.c_str(), 0, KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hTargetKey) )
									{
										max_path = MAX_VALUE_NAME;
										keyBuf[0] = '\0';
										retCode = RegQueryValueExA(hTargetKey, "Identifier", 0, 0, (LPBYTE)keyBuf, &max_path);
										if( retCode==ERROR_SUCCESS )
										{
											dmaDisabledlist.push_back(std::string(keyBuf));
										}
										RegCloseKey(hTargetKey);
									}
								}
							}
							RegCloseKey(hBusKey);
						}
					}
				}
			}
			RegCloseKey(hPortKey);
		}
		max_path = MAX_VALUE_NAME;
		keyBuf[0] = '\0';
		retCode = RegEnumKeyExA(hKey, nPort, keyBuf, &max_path, 0, 0, 0, 0);
	}
	RegCloseKey(hKey);
	return true;
}