std::vector<J2534Library> J2534_API::searchLibValuesRecursive(HKEY hKey, std::vector<J2534Library> PTlibs)
{
	HKEY hKey2;
	DWORD index = 0;
	char KeyName[256] = "";
	J2534Library PTlib;
	PTlib.api = J2534_API_v0404;
	char ValueName[256] = "";
	unsigned long szValueName = 256;// variable that specifies the size (in characters, including the terminating null char) of the buffer pointed to by the "ValueName" parameter.
	unsigned char Data[256] = "";	// buffer that receives the data for the value entry. This parameter can be NULL if the data is not required
	unsigned long szData = 256;	// variable that specifies the size, in bytes, of the buffer pointed to by the lpData parameter.
	long ret = 0;
	unsigned long ValueDataType = REG_NONE;
	// Check values :
	while ((RegEnumValueA(hKey, index, ValueName, &szValueName, NULL, &ValueDataType, Data, &szData)) != ERROR_NO_MORE_ITEMS)
	{
		if (ValueDataType == REG_SZ)
		{
			if (!strncmp(ValueName,"FunctionLibrary",15))
			{
				PTlib.path = (char*)(Data);
			}
			else if (!strncmp(ValueName,"Name",4))
			{
				PTlib.name = (char*)(Data);
			}
			else if (!strncmp(ValueName,"ProtocolsSupported",18))	// 02.02-API
			{
				std::string protocol_str = (char*)(Data);
				if (protocol_str.find("J1850VPW") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_J1850VPW;
				if (protocol_str.find("J1850PWM") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_J1850PWM;
				if (protocol_str.find("ISO9141") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_ISO9141;
				if (protocol_str.find("ISO14230") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_ISO14230;
				if (protocol_str.find("ISO15765") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_ISO15765;
				if (protocol_str.find("CAN") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_CAN;
				if (protocol_str.find("SCI_A_ENGINE") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_SCI_A_ENGINE;
				if (protocol_str.find("SCI_A_TRANS") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_SCI_A_TRANS;
				if (protocol_str.find("SCI_B_ENGINE") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_SCI_B_ENGINE;
				if (protocol_str.find("SCI_B_TRANS") != std::string::npos)
					PTlib.protocols |= PROTOCOL_FLAG_SCI_B_TRANS;
				PTlib.api = J2534_API_v0202;
			}
		}
		else if (ValueDataType == REG_DWORD)	// 04.04-API
		{
			DWORD key_value = *((DWORD*)(void*)(Data));
			if (key_value)
			{
				if (!strncmp(ValueName,"J1850VPW",7))
				{
					PTlib.protocols |= PROTOCOL_FLAG_J1850VPW;;
				}
				else if (!strncmp(ValueName,"J1850PWM", 7))
				{
					PTlib.protocols |= PROTOCOL_FLAG_J1850PWM;
				}
				else if (!strncmp(ValueName,"ISO9141", 7))
				{
					PTlib.protocols |= PROTOCOL_FLAG_ISO9141;
				}
				else if (!strncmp(ValueName,"ISO14230", 8))
				{
					PTlib.protocols |= PROTOCOL_FLAG_ISO14230;
				}
				else if (!strncmp(ValueName,"ISO15765", 8))
				{
					PTlib.protocols |= PROTOCOL_FLAG_ISO15765;
				}
				else if (!strncmp(ValueName,"CAN", 3))
				{
					PTlib.protocols |= PROTOCOL_FLAG_CAN;
				}
				else if (!strncmp(ValueName,"SCI_A_ENGINE", 12))
				{
					PTlib.protocols |= PROTOCOL_FLAG_SCI_A_ENGINE;
				}
				else if (!strncmp(ValueName,"SCI_A_TRANS", 11))
				{
					PTlib.protocols |= PROTOCOL_FLAG_SCI_A_TRANS;
				}
				else if (!strncmp(ValueName,"SCI_B_ENGINE", 12))
				{
					PTlib.protocols |= PROTOCOL_FLAG_SCI_B_ENGINE;
				}
				else if (!strncmp(ValueName,"SCI_B_TRANS", 11))
				{
					PTlib.protocols |= PROTOCOL_FLAG_SCI_B_TRANS;
				}
			}
		}
		szValueName = 256;	// because RegEnumValue has changed value !
		szData = 256;		// because RegEnumValue has changed value !
		index++;
	}
	if (PTlib.path.size() > 0)
		PTlibs.push_back( PTlib );
	// Check sub-keys:
	index = 0;
	while (RegEnumKeyA(hKey, index, KeyName, 256) != ERROR_NO_MORE_ITEMS)
	{
		ret = RegOpenKeyExA(hKey, KeyName, 0, KEY_READ, &hKey2);
		if (ret == ERROR_SUCCESS)
		{
			PTlibs = searchLibValuesRecursive(hKey2, PTlibs);
			ret = RegCloseKey(hKey2);
#ifdef __J2534_API_DEBUG__
			if (ret != ERROR_SUCCESS)
				std::cout << "J2534interface::searchLibValuesRecursive():   RegCloseKey(...) failed with error " << ret << "\n";
#endif
		}
#ifdef __J2534_API_DEBUG__
		else
		{
			std::cout << "J2534interface::getAvailableJ2534Libs():   RegOpenKexEx(...) for key " << KeyName << " failed with error " << ret << "\n";
		}
#endif
		index++;
	}
	return PTlibs;
}