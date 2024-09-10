BOOL CALLBACK kull_m_handle_getHandlesOfType_callback(PSYSTEM_HANDLE pSystemHandle, PVOID pvArg)
{
	PHANDLE_ENUM_DATA pData = (PHANDLE_ENUM_DATA) pvArg;
	BOOL status = TRUE;
	HANDLE hProcess, hRemoteHandle;
	POBJECT_TYPE_INFORMATION pInfos;
	ULONG szNeeded;

	if(hProcess = OpenProcess(PROCESS_DUP_HANDLE, FALSE, pSystemHandle->ProcessId))
	{
		if(DuplicateHandle(hProcess, (HANDLE) pSystemHandle->Handle, GetCurrentProcess(), &hRemoteHandle, pData->dwDesiredAccess, TRUE, pData->dwOptions))
		{
			if(NtQueryObject(hRemoteHandle, ObjectTypeInformation, NULL, 0, &szNeeded) == STATUS_INFO_LENGTH_MISMATCH)
			{
				if(pInfos = (POBJECT_TYPE_INFORMATION) LocalAlloc(LPTR, szNeeded))
				{
					if(NT_SUCCESS(NtQueryObject(hRemoteHandle, ObjectTypeInformation, pInfos, szNeeded, &szNeeded)))
					{
						if(!pData->type || RtlEqualUnicodeString(&pInfos->TypeName, pData->type, TRUE))
							status = pData->callBack(hRemoteHandle, pSystemHandle, pData->pvArg);
					}
					LocalFree(pInfos);
				}
			}
			CloseHandle(hRemoteHandle);
		}
		CloseHandle(hProcess);
	}
	return status;
}