DWORD CServerDef::StatGet(SERV_STAT_TYPE i) const
{
	ADDTOCALLSTACK("CServerDef::StatGet");
	ASSERT( i >= 0 && i <= SERV_STAT_QTY );
	DWORD	d = m_dwStat[i];
	EXC_TRY("StatGet");
	if ( i == SERV_STAT_MEM )	// memory information
	{
		d = 0;
		if ( m_bPmemory )
		{
#ifdef _WIN32
			if ( !m_hmPsapiDll )			// try to load psapi.dll if not loaded yet
			{
				EXC_SET("load process info");
				m_hmPsapiDll = LoadLibrary(TEXT("psapi.dll"));
				if (m_hmPsapiDll == NULL)
				{
					m_bPmemory = false;
					g_Log.EventError(("Unable to load process information PSAPI.DLL library. Memory information will be not available.\n"));
				}
				else
				{
					m_GetProcessMemoryInfo = reinterpret_cast<pGetProcessMemoryInfo>(::GetProcAddress(m_hmPsapiDll,"GetProcessMemoryInfo"));
				}
			}

			if ( m_GetProcessMemoryInfo ) {
				EXC_SET("open process");
				HANDLE hProcess = GetCurrentProcess();
				if ( hProcess ) {
					ASSERT( hProcess == (HANDLE)-1 );
					EXC_SET("get memory info");
					if ( m_GetProcessMemoryInfo(hProcess, &pcnt, sizeof(pcnt)) ) {
						EXC_SET("read memory info");
						d = pcnt.WorkingSetSize;
					}
					CloseHandle(hProcess);
				}
			}
#else
			struct rusage usage;
			int res = getrusage(RUSAGE_SELF, &usage);

			if ( res == 0 && usage.ru_idrss )
				d = usage.ru_idrss;
			else
			{
				CFileText inf;
				TCHAR * buf = Str_GetTemp(), * head;

				sprintf(buf, "/proc/%d/status", getpid());
				if ( inf.Open(buf, OF_READ|OF_TEXT) )
				{
					for (;;)
					{
						if ( !inf.ReadString(buf, SCRIPT_MAX_LINE_LEN) )
							break;

						if ( (head = strstr(buf, "VmSize:")) != NULL )
						{
							head += 7;
							GETNONWHITESPACE(head)
							d = ATOI(head) * 1000;
							break;
						}
					}
					inf.Close();
				}
			}

			if ( !d )
			{
				g_Log.EventError(("Unable to load process information from getrusage() and procfs. Memory information will be not available.\n"));
				m_bPmemory = false;
			}
#endif

			if ( d != 0 )
				d /= 1024;
		}
	}
	return d;

	EXC_CATCH;
	EXC_DEBUG_START;
	g_Log.EventDebug("stat '%d', val '%lu'\n", i, d);
	EXC_DEBUG_END;
	return 0;
}