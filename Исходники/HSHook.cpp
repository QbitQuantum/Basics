BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	BOOL bRet = FALSE;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);

		bRet = (CStackStorage::GetInstance()->InitSharedFileMapping(0) 
			&& CStackStorage::GetInstance()->Open());

		if (TRUE == bRet)
		{
			bRet = DetoursorHelper::AddAllFunctionsToDetoursor(CDetoursor::GetInstance());		
			if (TRUE == bRet)
			{
				bRet = CDetoursor::GetInstance()->DoHook();
			}
		}
		break;
	case DLL_PROCESS_DETACH:
		bRet = CDetoursor::GetInstance()->UndoHook();
		if (TRUE == bRet)
		{			
			WCHAR wcsExeFilePathName[_MAX_PATH];
			ZeroMemory(wcsExeFilePathName, sizeof(_MAX_PATH));
			GetModuleFileNameW(NULL, wcsExeFilePathName, _countof(wcsExeFilePathName));
			
			CDetoursor::GetInstance()->ClearFunctionTable();
			
			CStackStorage::GetInstance()->SetModInfoData(CCallStack::GetModInfoVector());
			CStackStorage::GetInstance()->SetHeaderData(wcsExeFilePathName);
			CStackStorage::GetInstance()->Close();
		}
		break;
	}

    return bRet;
}