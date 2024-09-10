/*--------------------------------------------------------------------------
 Launches NetShell, waits for Netshell and all of NetShell's launched
   processes to die and then relaunches NetShell if nothing exited with
   non-zero exit status.
--------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hinstExe, HINSTANCE hinstExePrev, LPSTR lpszCmdLine, int nCmdShow)
{
	int firsttime = 1;
	char cmd[2*MAX_PATH];
	char args[MAX_PATH];
	char cwd[MAX_PATH];
	char strhandle[MAX_HSTR];
	DWORD nhandles = 0;
	DWORD exitCode = 0;
	DWORD dwThreadId, iSignal;
	HANDLE hpipeRead, hpipeWrite, hSelf;
	HANDLE *hArray, *hStartArr;
	SECURITY_ATTRIBUTES saAttr;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

#ifdef DEBUG
#ifndef PRINT_STDOUT
	{	char logfile[MAX_PATH];
		sprintf(logfile, "%x", time(NULL));
		strcat(logfile, ".log");
		flog = fopen(logfile, "w");
	}
#endif
#endif
	/* Pick random session id for benefit of serial and modem drivers */
	sprintf(strhandle, "%x", GetTickCount());
	if (!SetEnvironmentVariable(DPSTUBID, strhandle)) {
		DPRINT(("stub: set environment variable error %x.\n", GetLastError()));
		exit(1);
	}
	hArray = (HANDLE *)malloc(MAXIMUM_WAIT_OBJECTS * sizeof(HANDLE));
	hStartArr = hArray;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	if (!DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(), &hSelf,  0, TRUE, DUPLICATE_SAME_ACCESS)) {
		DPRINT(("stub: error duplicating own handle\n"));
		exit(1);
	}
	sprintf(strhandle, "%x", hSelf);
	if (!SetEnvironmentVariable(DPSTUB, strhandle)) {
		DPRINT(("stub: set environment variable error %x.\n", GetLastError()));
		exit(1);
	}
//	DPRINT(("stub: current process handle is %s\n", strhandle));

	/* create event so read thread can signal when it's read a new process */
	if (!(hreadEvent = CreateEvent(NULL, FALSE, FALSE, "ReadEvent"))) {
		DPRINT(("stub: create read event error %x.\n", GetLastError()));
		exit(1);
	}
	*hArray++ = hreadEvent;
	nhandles++;
//	DPRINT(("stub: read event handle is %x\n", *(hArray - 1)));

	/* create event so read thread knows main thread has finished processing
	   hSpawn and can continue to get new processes */
	if (!(hcontEvent = CreateEvent(NULL, FALSE, FALSE, "ContinueReadEvent"))) {
		DPRINT(("stub: create continue read event error %x.\n", GetLastError()));
		exit(1);
	}
//	DPRINT(("stub: continue read event handle is %x\n", hcontEvent));

	/* create a pipe with read end uninheritable and write end inheritable*/
	if(!CreatePipe(&hpipeRead, &hpipeWrite, &saAttr, sizeof(HANDLE))) {
		DPRINT(("stub: create pipe error %x.\n", GetLastError()));
		exit(1);
	}
	sprintf(strhandle, "%x", hpipeWrite);
	if (!SetEnvironmentVariable(DPSTUBWPIPE, strhandle)) {
		DPRINT(("stub: set environment variable error %x.\n", GetLastError()));
		exit(1);
	}
	if (!DuplicateHandle(GetCurrentProcess(), hpipeRead, GetCurrentProcess(), &hpipeReadDup,  0, FALSE, DUPLICATE_SAME_ACCESS)) {
		DPRINT(("stub: error duplicating uninheritable handle\n"));
		exit(1);
	}
	CloseHandle(hpipeRead);
//	DPRINT(("stub: uninheritable pipe handle is %x.\n", hpipeReadDup));

	/* create a thread to read from pipe about new processes*/
	if (CreateThread(NULL, 0, readThread, 0, 0, &dwThreadId) < 0) {
		DPRINT(("stub: create thread error %x.\n", GetLastError()));
		exit(1);
	}

	/* set command and current working directory for CreateProcess() */
	{	char *buf;
		char path[2*MAX_PATH];
		char cmdline[1024];
		if (getinfo(path, args, cwd) != 0) {
			CHAR title[TITLELEN];
			CHAR msg[MSGLEN];
			LoadString(NULL, IDS_NO_JRE_TITLE, title, TITLELEN);
			LoadString(NULL, IDS_NO_JRE_MSG, msg, MSGLEN);
			MessageBox(NULL, msg, title,
				MB_OK | MB_ICONERROR | MB_TASKMODAL | MB_SETFOREGROUND);
			exit(1);
		}
		strcat(cmd, "\"");
		strcat(cmd, path);
		strcat(cmd, "\" ");
		strcat(cmd, args);

		buf = GetCommandLine();
		if (!buf) {
			DPRINT(("stub: error getting commandline args; quitting\n"));
			exit(1);
		}
		strcpy(cmdline, buf);
#ifdef DEFAULTARGS
		/* If no switches given, append default args */
		if (!strstr(cmdline, " -")) {
			strcat(cmdline, " ");
			strcat(cmdline, DEFAULTARGS);
		}
#endif
		buf = cmdline;
		DPRINT(("args: %s\n", buf));
		{
			OSVERSIONINFO VersionInfo;
			VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			if (!GetVersionEx(&VersionInfo)) {
				DPRINT(("stub: cannot determine OS; quitting\n"));
				exit(1); 
			}
			if (VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT || VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
				while (' ' == *buf || '\t' == *buf) buf++;
				if (*buf == '\"') {
					buf++;
					if (!(buf = strchr(buf, '\"'))) {
						DPRINT(("stub: cannot get commandline args; quitting\n"));
						exit(1);
					}
					buf++;
				} else {
					if (buf = strchr(buf, ' ')) {
						buf++;
					} else {
						buf = "\0";
					}
				}
			} else {
				CHAR title[TITLELEN];
				CHAR msg[MSGLEN];
				LoadString(NULL, IDS_UNSP_OS_TITLE, title, TITLELEN);
				LoadString(NULL, IDS_UNSP_OS_MSG, msg, MSGLEN);
				MessageBox(NULL, msg, title,
					MB_OK | MB_ICONERROR | MB_TASKMODAL | MB_SETFOREGROUND);
				DPRINT(("OS not supported; quitting\n"));
				exit(1);
			}
			while (' ' == *buf || '\t' == *buf) buf++;
			if (2 * MAX_PATH < strlen(cmd) + strlen(buf) + 2) {
				DPRINT(("stub: cmd buffer not large enough to hold args; quitting\n"));
				exit(1);
			}
			strcat(cmd, " ");
			strcat(cmd, buf);
		}
	}
	DPRINT(("cmd: %s\n", cmd));

	/* launch NetShell then wait for NetShell and all its launched processes
	   to die, then if all exit status are zero, relaunch NetShell */
	do {
		memset(&pi, 0, sizeof(pi));
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);
		/* launch NetShell */
    	DPRINT(("stub: Launching %s from %s.\n", cmd, cwd));
		if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, cwd, &si, &pi)) {
			DPRINT(("stub: Error launching %s from %s; quitting\n", cmd, cwd));
			DPRINT(("stub: GetLastError returns %x", GetLastError()));
			exit(1);
		}
		if (firsttime) {
			char *buf = " -r";
			if (2 * MAX_PATH < strlen(cmd) + strlen(buf) + 1) {
				DPRINT(("stub: cmd buffer not large enough to hold args\n"));
				exit(1);
			}
			strcat(cmd, buf);
			firsttime = 0;
		}
		CloseHandle(pi.hThread);
		*hArray++ = pi.hProcess;
		nhandles++;
		DPRINT(("stub: Launch complete; shell handle %x.\n", *(hArray-1)));

		/* Wait for NetShell and all its launched processes to exit */
		do {
			iSignal = WaitForMultipleObjects(nhandles, hStartArr, FALSE, INFINITE);
			if (WAIT_FAILED == iSignal) {
				DPRINT(("stub: wait error %x.\n", GetLastError()));
				exit(1);
			}
			iSignal -= WAIT_OBJECT_0;
			if (iSignal >= 0 && iSignal < nhandles) {
				if (*(hStartArr + iSignal) != hreadEvent) {
					if (!GetExitCodeProcess(*(hStartArr + iSignal), &exitCode)) {
						DPRINT(("stub: Error reading spawned process\n"));
						exit(1);
					}
					DPRINT(("stub: deleting handle %x, exit code %d.\n", *(hStartArr + iSignal), exitCode));
					if (exitCode) break;
					CloseHandle(*(hStartArr + iSignal));
					if (nhandles && iSignal < nhandles - 1) {
						*(hStartArr + iSignal) = *(hStartArr + nhandles - 1);
					}
					nhandles--;
					hArray = hStartArr + nhandles;
				} else {
					// DPRINT(("stub: got new handle %x\n", hSpawn));
					if (hSpawn != 0) {
						if (hSpawn < 0) {
							DPRINT(("stub: Error reading spawned process; hSpawn %x\n", hSpawn));
							exit(1);
						}
						DPRINT(("stub: adding handle %x.\n", hSpawn));
						*hArray++ = hSpawn;
						nhandles++;
						hSpawn = 0;
					} else if (hSerial != 0) {
						char *pstrhandle;
						if (hSerial < 0 && hSerial != INVALID_HANDLE_VALUE) {
							DPRINT(("stub: Error reading serial handle; hSerial %x\n", hSerial));
							exit(1);
						}
						if (hSerial == INVALID_HANDLE_VALUE) {
							if (GetEnvironmentVariable(DPSTUBMODEM, strhandle, 256)) {
								HANDLE baseadr;
								sscanf(strhandle, "%x", &baseadr);
								CloseHandle(baseadr);
								DPRINT(("stub: deleted serial h:%x\n",baseadr));
								pstrhandle = NULL;
							}
						} else {
							DPRINT(("stub: setting serial h:%x.\n", hSerial));
							sprintf(strhandle, "%x", hSerial);
							pstrhandle = strhandle;
						}
						if (!SetEnvironmentVariable(DPSTUBMODEM, pstrhandle)) {
							DPRINT(("stub: set environment variable error %x.\n", GetLastError()));
							exit(1);
						}
						hSerial = 0;
					} else {
						DPRINT(("stub: Error no handle set\n"));
						exit(1);
					}
					if (!SetEvent(hcontEvent)) {
						DPRINT(("stub: set continue read event error %x.\n", GetLastError()));
						exit(1);
					}
				}
			} else {
				DPRINT(("stub: error wait returned invalid handle %d\n", iSignal));
				exit(1);
			}
//			DPRINT(("stub: nhandles = %d\n", nhandles));
		} while (nhandles > 1);
//		DPRINT(("stub: exited inside loop\n"));
#ifdef NOLOOP		
		break;
#endif
	} while (!exitCode);
	return 0;
}