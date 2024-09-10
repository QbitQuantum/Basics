		bool openSAMP()
		{
			if (!openProcess())
				return false;

			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_dwPID);
			if (hSnapshot == INVALID_HANDLE_VALUE)
				return false;

			MODULEENTRY32 entry;
			entry.dwSize = sizeof(MODULEENTRY32);

			Module32First(hSnapshot, &entry);
			do
			{
#ifdef UNICODE
                if (_wcsicmp(entry.szModule, L"samp.dll") == 0)
#else
				if (_stricmp(entry.szModule, "samp.dll") == 0)
#endif
				{
					m_dwSAMPBase = (DWORD) entry.modBaseAddr;
					break;
				}
			} 
			while (Module32Next(hSnapshot, &entry));

			CloseHandle(hSnapshot);
			return m_dwSAMPBase != 0;
		}