UINT16 CUARTApp::ScanSerialPort(UCHAR * numBuff)
{
#define MAX_KEY_LENGTH   255
#define MAX_VALUE_NAME  16383
	HKEY hTestKey;
	int nIndex = 0;

	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hTestKey))
	{
		TCHAR   achClass[MAX_PATH] = TEXT(""); // buffer for class name
		DWORD   cchClassName = MAX_PATH; // size of class string
		DWORD   cSubKeys = 0;                  // number of subkeys
		DWORD   cbMaxSubKey;             // longest subkey size
		DWORD   cchMaxClass;             // longest class string
		DWORD   cValues;             // number of values for key
		DWORD   cchMaxValue;         // longest value name
		DWORD   cbMaxValueData;      // longest value data
		DWORD   cbSecurityDescriptor; // size of security descriptor
		FILETIME ftLastWriteTime;     // last write time

		DWORD i, retCode;
		//TCHAR achValue[MAX_VALUE_NAME];
		CHAR achValue[MAX_VALUE_NAME];
		DWORD cchValue = MAX_VALUE_NAME;
		LONG lResult;

		// Get the class name and the value count.
		retCode = RegQueryInfoKey(
			hTestKey,                   // key handle
			achClass,               // buffer for class name
			&cchClassName,          // size of class string
			NULL,                   // reserved
			&cSubKeys,              // number of subkeys
			&cbMaxSubKey,           // longest subkey size
			&cchMaxClass,           // longest class string
			&cValues,               // number of values for this key
			&cchMaxValue,           // longest value name
			&cbMaxValueData,        // longest value data
			&cbSecurityDescriptor,  // security descriptor
			&ftLastWriteTime);      // last write time
		if (cValues > 0)
		{

			for (i = 0; i<cValues; i++)
			{
				cchValue = MAX_VALUE_NAME;
				achValue[0] = '\0';
				lResult = RegEnumValueA(hTestKey, i, achValue, &cchValue, NULL, NULL, NULL, NULL);
				if (ERROR_SUCCESS == lResult)
				{
					BYTE strDSName[50];
					//memset(strDSName, 0, 100);
					strDSName[0] = '\n';
					DWORD  nBuffLen = 50;
					//if (ERROR_SUCCESS == RegQueryValueEx(hTestKey, (LPCTSTR)achValue, NULL,&nValueType, strDSName, &nBuffLen))
					if (ERROR_SUCCESS == RegQueryValueExA(hTestKey, achValue, NULL, NULL, strDSName, &nBuffLen))
					{
						//						UCHAR num;
						numBuff[nIndex++] = atoi((char*)(strDSName + 3));
						//CString str(strDSName);
						//combobox->AddString(str);
					}
				}
				else
				{
					TRACE("error\r\n");
				}
			}
		}
		else
		{
			//AfxMessageBox(_T("PC机没有COM口....."));
		}
	}
	RegCloseKey(hTestKey);
	return nIndex;
}