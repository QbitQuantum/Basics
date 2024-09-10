void
RegistryMonitor::initialiseObjectNameMap()
{
	HKEY hTestKey;
	wchar_t szTemp[256];

	DWORD dwError = RegOpenCurrentUser(KEY_READ , &hTestKey);
	if (dwError == ERROR_SUCCESS )
	{
		NTSTATUS status;
		DWORD RequiredLength;
		PPUBLIC_OBJECT_TYPE_INFORMATION t;

		typedef DWORD (WINAPI *pNtQueryObject)(HANDLE,DWORD,VOID*,DWORD,VOID*);
		pNtQueryObject NtQueryObject = (pNtQueryObject)GetProcAddress(GetModuleHandle(L"ntdll.dll"), (LPCSTR)"NtQueryObject");
		
		status = NtQueryObject(hTestKey, 1, NULL,0,&RequiredLength);

		if(status == STATUS_INFO_LENGTH_MISMATCH)
		{
			t = (PPUBLIC_OBJECT_TYPE_INFORMATION)VirtualAlloc(NULL, RequiredLength, MEM_COMMIT, PAGE_READWRITE);
			if(status != NtQueryObject(hTestKey, 1,t,RequiredLength,&RequiredLength))
			{
				ZeroMemory(szTemp, 256);
				CopyMemory(&szTemp, t->TypeName.Buffer, RequiredLength);

				// Dont change the order of these ... _Classes should be inserted first
				// Small bug but who cares
				wstring temp2 = szTemp;
				temp2 += L"_CLASSES";
				wstring name2 = L"HKCR";
				objectNameMap.push_back(ObjectPair(temp2, name2));
				wstring temp1 = szTemp;
				wstring name1 = L"HKCU";
				objectNameMap.push_back(ObjectPair(temp1, name1));
				wstring temp3 = L"\\REGISTRY\\MACHINE";
				wstring name3 = L"HKLM";
				objectNameMap.push_back(ObjectPair(temp3, name3));
				wstring temp4 = L"\\REGISTRY\\USER";
				wstring name4 = L"HKU";
				objectNameMap.push_back(ObjectPair(temp4, name4));
				wstring temp5 = L"\\Registry\\Machine";
				wstring name5 = L"HKLM";
				objectNameMap.push_back(ObjectPair(temp5, name5));

			}
			VirtualFree(t, 0, MEM_RELEASE);
		}
	}
}