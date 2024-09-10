BOOL
FixIAT(
	DWORD dwProcessId,
	HANDLE hProcess,
	PBYTE imageBase,
	PIMAGE_NT_HEADERS pNtHeader,
	PIMAGE_IMPORT_DESCRIPTOR pImgImpDesc
	)
{
	BOOL bRet = FALSE;
	LPSTR lpModuleName = 0;
	HMODULE hLocalModule = 0;
	HMODULE hRemoteModule = 0;
	WCHAR modulePath[MAX_PATH + 1] = {0};
	WCHAR moduleNtPath[500 + 1] = {0};
	WCHAR targetProcPath[MAX_PATH + 1] = {0};
	WCHAR *pch = 0;

	__try
	{
		//printf("Fixing Imports:\n");

		// get target process path
		if(!GetModuleFileNameExW(hProcess, (HMODULE)0, targetProcPath, MAX_PATH))
		{
			PRINT_ERROR_MSGA("Could not get path to target process.");
			__leave;
		}

		pch = wcsrchr(targetProcPath, '\\');
		if(pch)
		{
			targetProcPath[ pch - targetProcPath + 1 ] = (WCHAR)0;
		}

		if(!SetDllDirectoryW(targetProcPath))
		{
			PRINT_ERROR_MSGW(L"Could not set path to target process (%s).", targetProcPath);
			__leave;
		}

		while((lpModuleName = (LPSTR)GetPtrFromRVA(pImgImpDesc->Name, pNtHeader, imageBase)))
		{
			PIMAGE_THUNK_DATA itd = 0;

			//printf("module: %s\n", lpModuleName);

			// ACHTUNG: LoadLibraryEx kann eine DLL nur anhand des Namen aus einem anderen
			// Verzeichnis laden wie der Zielprozess!
			hLocalModule = LoadLibraryExA(lpModuleName, 0, DONT_RESOLVE_DLL_REFERENCES);
			if(!hLocalModule)
			{
				PRINT_ERROR_MSGA("Could not load module locally.");
				__leave;
			}

			// get full path of module
			if(!GetModuleFileNameW(hLocalModule, modulePath, MAX_PATH))
			{
				PRINT_ERROR_MSGA("Could not get path to module (%s).", lpModuleName);
				__leave;
			}

			// get nt path
			if(!GetFileNameNtW(modulePath, moduleNtPath, 500))
			{
				PRINT_ERROR_MSGA("Could not get the NT namespace path.");
				__leave;
			}

			// Module already in process?
			hRemoteModule = (HMODULE)ModuleInjectedW(hProcess, moduleNtPath);
			if(!hRemoteModule)
			{
				if(!InjectLibraryW(dwProcessId, modulePath))
				{
					PRINT_ERROR_MSGW(L"Could not inject required module (%s).\n", modulePath);
					__leave;
				}
				
				hRemoteModule = (HMODULE)ModuleInjectedW(hProcess, moduleNtPath);
			}

			itd = (PIMAGE_THUNK_DATA)GetPtrFromRVA(pImgImpDesc->FirstThunk, pNtHeader, imageBase);

			while(itd->u1.AddressOfData)
			{
				IMAGE_IMPORT_BY_NAME *iibn =
					(PIMAGE_IMPORT_BY_NAME)GetPtrFromRVA(itd->u1.AddressOfData, pNtHeader, imageBase);
				itd->u1.Function = (DWORD_PTR)GetRemoteProcAddress(hProcess, hRemoteModule, (LPCSTR)iibn->Name);

				//printf("Function: %s\n", (LPCSTR)iibn->Name);

				itd++;
			}      

			pImgImpDesc++;
		}

		bRet = TRUE;
	}
	__finally
	{
		if(hLocalModule)
		{
			FreeLibrary(hLocalModule);
		}
	}

	return bRet;
}