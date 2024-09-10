/*
	Unload Dll from process

	RETURN:
		Error code
*/
DWORD CMemDll::Unload()
{
	HANDLE hThread = NULL;
	HMODULE hDll = NULL;

    if(!CMemCore::Instance().m_hProcess)
        return ERROR_INVALID_HANDLE;

	//Search for dll in process
	if((hDll = (HMODULE)GetModuleAddress(GetProcessId(CMemCore::Instance().m_hProcess), TEXT(DLL_NAME))) !=0 )
	{
		hThread = CreateRemoteThread
			(
				CMemCore::Instance().m_hProcess, 
				NULL, 0, 
				(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "FreeLibrary"), 
				(void*)hDll, 
				0, NULL
			);

		if(hThread == NULL)
		{
			MessageBox(NULL, TEXT("Cannot create thread"), TEXT("Error"), MB_ICONERROR);
			return GetLastError();
		}
		//Wait for completion
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}

    return ERROR_SUCCESS;
}