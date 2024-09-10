void AdbManager::internal_scan_timeout(void* arg)
{
	g_adb_manager->mLocalTimer = NULL;
	//scan
	for (int i = 0; i < 1 && g_adb_manager->mShouldScan; i++)
	{
		HANDLE                pipe_read, pipe_write;
		SECURITY_ATTRIBUTES   sa;
		STARTUPINFO           startup;
		PROCESS_INFORMATION   pinfo;
		char                  program_path[MAX_PATH];
		int                   ret;

		ZeroMemory(&sa, sizeof(sa));
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;

		/* create pipe, and ensure its read handle isn't inheritable */
		ret = MyCreatePipeEx(&pipe_read, &pipe_write, &sa, 0);
		if (!ret) {
			fprintf(stderr, "CreatePipe() failure, error %ld\n", GetLastError());
			break;
		}

		SetHandleInformation(pipe_read, HANDLE_FLAG_INHERIT, 0);

		ZeroMemory(&startup, sizeof(startup));
		startup.cb = sizeof(startup);
		startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		startup.hStdOutput = pipe_write;
		startup.hStdError = pipe_write;// GetStdHandle(STD_ERROR_HANDLE);
		startup.dwFlags = STARTF_USESTDHANDLES;

		ZeroMemory(&pinfo, sizeof(pinfo));

		/* get path of current program */
		GetModuleFileName(NULL, program_path, sizeof(program_path));
		char * ch = strrchr(program_path, '\\');
		//if (ch){ ch++; strcpy(ch, "adb.exe devices"); }
		if (ch){ ch++; strcpy(ch, "adb.exe devices"); }

		ret = CreateProcess(
			NULL,                              /* program path  */
			program_path,
			/* the fork-server argument will set the
			debug = 2 in the child           */
			NULL,                   /* process handle is not inheritable */
			NULL,                    /* thread handle is not inheritable */
			TRUE,                          /* yes, inherit some handles */
			DETACHED_PROCESS, /* the new process doesn't have a console */
			NULL,                     /* use parent's environment block */
			NULL,                    /* use parent's starting directory */
			&startup,                 /* startup info, i.e. std handles */
			&pinfo);

		CloseHandle(pipe_write);

		if (!ret) {
			fprintf(stderr, "CreateProcess failure, error %ld\n", GetLastError());
			CloseHandle(pipe_read);
			break;
		}

		CloseHandle(pinfo.hThread);


		char  temp[65536];
		int total_count = 0;
		DWORD  count;
		ULONGLONG start_time = GetTickCount64();
		OVERLAPPED overlapped;
		ZeroMemory(&overlapped, sizeof(OVERLAPPED));
		do{
			count = 0;
			ret = ReadFile(pipe_read, temp + total_count, sizeof(temp)-total_count, &count, &overlapped);
			total_count += count;
			//if (GetTickCount64() - start_time > 10 * 1000){ break; }
			if (!ret) {
				int err = GetLastError();
				if (err == ERROR_IO_PENDING)
				{ 
					Sleep(1000);
					GetOverlappedResult(pipe_read, &overlapped, &count, FALSE);
					total_count += count;
					continue; 
				}
				fprintf(stderr, "could not read ok from ADB Server, error = %ld\n", err);
				break;
			}
			else{
				Sleep(100);
			}
		} while (1);
		CloseHandle(pipe_read);
		TerminateProcess(pinfo.hProcess, 0);
		CloseHandle(pinfo.hProcess);
		g_adb_manager->parse_device(temp);
		break;
	}
	g_adb_manager->internal_start_scan();
}