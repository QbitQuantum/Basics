BOOL kull_m_registry_RegQueryValueEx(IN PKULL_M_REGISTRY_HANDLE hRegistry, IN HKEY hKey, IN OPTIONAL LPCWSTR lpValueName, IN LPDWORD lpReserved, OUT OPTIONAL LPDWORD lpType, OUT OPTIONAL LPBYTE lpData, IN OUT OPTIONAL LPDWORD lpcbData)
{
	BOOL status = FALSE;
	DWORD dwErrCode, i, szData;
	PKULL_M_REGISTRY_HIVE_KEY_NAMED pKn;
	PKULL_M_REGISTRY_HIVE_VALUE_LIST pVl;
	PKULL_M_REGISTRY_HIVE_VALUE_KEY pVk, pFvk = NULL;
	wchar_t * buffer;
	PVOID dataLoc;

	switch(hRegistry->type)
	{
		case KULL_M_REGISTRY_TYPE_OWN:
			dwErrCode = RegQueryValueEx(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
			if(!(status = (dwErrCode == ERROR_SUCCESS)))
				SetLastError(dwErrCode);
			break;
		case KULL_M_REGISTRY_TYPE_HIVE:
			pKn = hKey ? (PKULL_M_REGISTRY_HIVE_KEY_NAMED) hKey : hRegistry->pHandleHive->pRootNamedKey;
			if(pKn->tag == 'kn')
			{
				if(pKn->nbValues && (pKn->offsetValues != -1))
				{
					pVl = (PKULL_M_REGISTRY_HIVE_VALUE_LIST) (hRegistry->pHandleHive->pStartOf + pKn->offsetValues);
					for(i = 0 ; i < pKn->nbValues && !pFvk; i++)
					{
						pVk = (PKULL_M_REGISTRY_HIVE_VALUE_KEY) (hRegistry->pHandleHive->pStartOf + pVl->offsetValue[i]);
						if(pVk->tag == 'kv')
						{
							if(lpValueName)
							{
								if(pVk->szValueName)
								{
									if(pVk->flags & KULL_M_REGISTRY_HIVE_VALUE_KEY_FLAG_ASCII_NAME)
										buffer = kull_m_string_qad_ansi_c_to_unicode((char *) pVk->valueName, pVk->szValueName);
									else if(buffer = (wchar_t *) LocalAlloc(LPTR, pVk->szValueName + sizeof(wchar_t)))
										RtlCopyMemory(buffer, pVk->valueName, pVk->szValueName);

									if(buffer)
									{
										if(_wcsicmp(lpValueName, buffer) == 0)
											pFvk = pVk;
										LocalFree(buffer);
									}
								}
							}
							else if(!pVk->szValueName)
								pFvk = pVk;

							if(status = (pFvk != NULL))
							{
								szData = pFvk->szData & ~0x80000000;
								if(lpType)
									*lpType = pFvk->typeData;
								
								if(lpcbData)
								{
									if(lpData)
									{
										if(status = (*lpcbData >= szData))
										{
											dataLoc = (pFvk->szData & 0x80000000) ? &pFvk->offsetData : (PVOID) &(((PKULL_M_REGISTRY_HIVE_BIN_CELL) (hRegistry->pHandleHive->pStartOf + pFvk->offsetData))->data);
											RtlCopyMemory(lpData, dataLoc , szData);
										}
									}
									*lpcbData = szData;
								}
							}
						}
					}
				}
			}
			break;
		default:
			break;
	}
	return status;
}