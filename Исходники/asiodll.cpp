/*****************************************************************************
 * LookupClassId()
 *****************************************************************************
 */
GUID
LookupClassId
(
	IN		LPTSTR	SymbolicLink
)
{
	GUID ClassId;

	HKEY EmuPublicKey = NULL;

	DWORD w32Error = RegCreateKeyEx(HKEY_LOCAL_MACHINE, EMU_PUBLIC_KEY, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &EmuPublicKey, NULL);

	if (ERROR_SUCCESS == w32Error)
	{
		HKEY ClassKey = NULL;

		w32Error = RegCreateKeyEx(EmuPublicKey, "{EB5A82E1-B4E7-47e8-97B0-F0751F97C2D1}", 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &ClassKey, NULL);

		if (ERROR_SUCCESS == w32Error)
		{
			TCHAR ValueName[MAX_PATH]; _tcscpy(ValueName, SymbolicLink);

			TCHAR * token = _tcschr(ValueName, '\\');

			while (token)
			{
				*token = '#';

				token = _tcschr(token+1, '\\');
			}
 
			ULONG Type = 0;
			ULONG Size = sizeof(ClassId);
						
			w32Error = RegQueryValueEx(ClassKey, ValueName, 0, &Type, PBYTE(&ClassId), &Size);

			if (ERROR_SUCCESS != w32Error)
			{
				CoCreateGuid(&ClassId);
				
				RegSetValueEx(ClassKey, ValueName, 0, REG_BINARY, (BYTE*)&ClassId, sizeof(ClassId));

				w32Error = ERROR_SUCCESS;
			}

			RegCloseKey(ClassKey);
		}

		RegCloseKey(EmuPublicKey);
	}
	
	if (ERROR_SUCCESS != w32Error)
	{
		CoCreateGuid(&ClassId);
	}

	return ClassId;
}