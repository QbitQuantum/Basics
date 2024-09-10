bool W7EUtils::GetProcessList(HWND hWnd, std::map< DWORD, std::wstring > &mapProcs)
{
	// Note: We probably need to target a process which has the same ASLR setting as us, i.e. ON.
	// Explorer.exe is our default since it has ASLR on, is always running and can do the COM silent-elevation stuff by default.

	bool bResult = false;

	mapProcs.clear();

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		//MessageBox(hWnd, L"CreateToolhelp32Snapshot failed", L"Win7Elevate", MB_OK | MB_ICONWARNING);
		CLogger::LogLine(L"CreateToolhelp32Snapshot failed");
	}
	else
	{
		bool bFirst = true;
		PROCESSENTRY32 pe;

		while(true)
		{
			ZeroMemory(&pe, sizeof(pe));
			pe.dwSize = sizeof(pe);

			BOOL bPR = FALSE;

			if (bFirst)
			{
				bFirst = false;
				bPR = Process32First(hSnapshot, &pe);
			}
			else
			{
				bPR = Process32Next(hSnapshot, &pe);
			}

			if (!bPR)
			{
				DWORD dwErr = GetLastError();

				if (ERROR_NO_MORE_FILES != dwErr)
				{
					//MessageBox(hWnd, L"Process32Next/First failed", L"Win7Elevate", MB_OK | MB_ICONWARNING);
					CLogger::LogLine(L"Process32Next/First failed");
				}
				else if (mapProcs.empty())
				{
					//MessageBox(hWnd, L"Process32Next/First returned nothing", L"Win7Elevate", MB_OK | MB_ICONWARNING);
					CLogger::LogLine(L"Process32Next/First returned nothing");
				}
				else
				{
					bResult = true;
				}

				break; // Stop enumerating.
			}

			// Only insert processes that we can open

			HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);

			if (hProc != 0)
			{
				CloseHandle(hProc);
				mapProcs.insert( std::make_pair( pe.th32ProcessID, pe.szExeFile ) );
			}
		}

		CloseHandle(hSnapshot);
	}

	return bResult;
}