	// ////////////////////////////////////////////////////////////////////////////////
	// @private IsClassNet 
	//
	static BOOL IsClassNet( GUID * ClassGuid )
	{
#define MAX_NUM  50

		HKEY hKeyClass;
		LONG lRet;
		WCHAR ClassType[MAX_NUM];
		WCHAR NetClass[MAX_NUM] = L"Net";
		DWORD dwLength = MAX_NUM,dwType = REG_SZ;

		if (hKeyClass = SetupDiOpenClassRegKey(ClassGuid,KEY_READ))
		{
			lRet = RegQueryValueExW(
				hKeyClass, 
				L"Class", 
				NULL, 
				&dwType, 
				LPBYTE(ClassType), 
				&dwLength);

			RegCloseKey(hKeyClass);

			if ( lRet != ERROR_SUCCESS )
			{
				return FALSE;
			}

			if ( !wcscmp(ClassType,NetClass) )
			{
				return TRUE;
			}
		}                                 

		return FALSE;
	}