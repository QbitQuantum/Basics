BOOL CALLBACK EWP_DirectInject(HWND hwnd, LPARAM lParam)
{
	CHAR name[500] = {0};
	struct INJ_DATA injdata = *(struct INJ_DATA*)lParam;

	// injection via windowtitle
	if(injdata.mode == 1)
	{
		GetWindowTextA(hwnd, name, 500 * sizeof(CHAR));

		if(strncmp((LPCSTR)injdata.name, name, strlen(name) + 1) == 0)
		{
			DWORD dwPid = 0;
			GetWindowThreadProcessId(hwnd, &dwPid);
			if(dwPid == 0)
			{
				PRINT_ERROR_MSGA("Could not get ProcessId from window handle (hwnd: 0x%p).",
					hwnd);
			}

			if(!CHECK_TARGET_PROC(dwPid))
			{
				PRINT_TARGET_PROC_ERROR(dwPid);
				return TRUE;
			}

			if(injdata.inject)
			{
				if(injdata.mm)
				{
					if(!MapRemoteModuleA(dwPid, injdata.libpath))
					{
						PRINT_ERROR_MSGA("Failed to map the PE file into the remote address space of a process (PID: %x)\n",
							dwPid);
					}
				}
				else
				{
					InjectLibraryA(dwPid, injdata.libpath);
				}
			}
			else
			{
				if(injdata.module_address)
				{
					EjectLibrary(dwPid, injdata.module_address);
				}
				else
				{
					EjectLibraryA(dwPid, injdata.libpath);
				}
			}
		}
	}

	// injection via windowclass
	if(injdata.mode == 2)
	{
		GetClassNameA(hwnd, name, 500 * sizeof(CHAR));
		if(strncmp((LPCSTR)injdata.name, name, strlen(name) + 1) == 0)
		{
			DWORD dwPid = 0;
			GetWindowThreadProcessId(hwnd, &dwPid);
			if(dwPid == 0)
			{
				PRINT_ERROR_MSGA("Could not get ProcessId from window handle (hwnd: 0x%p).",
					hwnd);
			}

			if(!CHECK_TARGET_PROC(dwPid))
			{
				PRINT_TARGET_PROC_ERROR(dwPid);
				return TRUE;
			}

			if(injdata.inject)
			{
				if(injdata.mm)
				{
					if(!MapRemoteModuleA(dwPid, injdata.libpath))
					{
						PRINT_ERROR_MSGA("Failed to map the PE file into the remote address space of a process (PID: %x)\n",
							dwPid);
					}
				}
				else
				{
					InjectLibraryA(dwPid, injdata.libpath);
				}
			}
			else
			{
				if(injdata.module_address)
				{
					EjectLibrary(dwPid, injdata.module_address);
				}
				else
				{
					EjectLibraryA(dwPid, injdata.libpath);
				}
			}
		}
	}

	return TRUE;
}