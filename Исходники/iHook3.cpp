// The command below tells the OS that this EXE has an export function so we can use the global hook without a DLL
__declspec(dllexport) LRESULT CALLBACK g_LLKeyboardHookCallback(
   int nCode,      // The hook code
   WPARAM wParam,  // The window message (WM_KEYUP, WM_KEYDOWN, etc.)
   LPARAM lParam   // A pointer to a struct with information about the pressed key
) 
{
	/*	typedef struct {
	    DWORD vkCode;
	    DWORD scanCode;
	    DWORD flags;
	    DWORD time;
	    ULONG_PTR dwExtraInfo;
	} KBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;*/
	
	// Get out of hooks ASAP; no modal dialogs or CPU-intensive processes!
	// UI code really should be elsewhere, but this is just a test/prototype app
	// In my limited testing, HC_ACTION is the only value nCode is ever set to in CE
	static int iActOn = HC_ACTION;
	PROCESS_INFORMATION pi;
	int i;
	bool processed_key=false;
	if (nCode == iActOn) 
	{ 
		PKBDLLHOOKSTRUCT pkbhData = (PKBDLLHOOKSTRUCT)lParam;
		if ( (wParam == WM_KEYUP) && (processed_key==false) )
		{
			Add2Log(L"# hook got 0x%02x (%i). Looking for match...\r\n", pkbhData->vkCode, pkbhData->vkCode);
			BOOL bMatchFound=FALSE;
			for (i=0; i<=lastKey; i++) 
			{
				if (pkbhData->vkCode == kMap[i].keyCode)
				{
					bMatchFound=TRUE;
					DEBUGMSG(1, (L"# hook Catched key 0x%0x, launching '%s'\n", kMap[i].keyCode, kMap[i].keyCmd));
					Add2Log(L"# hook Matched key 0x%0x, launching '%s'\n", kMap[i].keyCode, kMap[i].keyCmd);
					runStruct run;
					run.szCmd=kMap[i].keyCmd;
					run.szArg=kMap[i].keyArg;
					hThread = CreateThread(NULL, 0, runExe, &run, 0, &dwThreadID);
					//if (CreateProcess(kMap[i].keyCmd, kMap[i].keyArg, NULL, NULL, NULL, 0, NULL, NULL, NULL, &pi))
					//{
					//	Add2Log(L"# hook CreateProcess OK\r\n", FALSE);
					//	CloseHandle(pi.hProcess);
					//	CloseHandle(pi.hThread);
					//}
					//else{
					//	Add2Log(L"# hook CreateProcess FAILED. LastError=%i (0x%x)\r\n", GetLastError(), GetLastError());
					//}
					processed_key=true;
					Add2Log(L"# hook processed_key is TRUE\r\n", FALSE);

				}
			}
			if(!bMatchFound)
				Add2Log(L"# hook No match found\r\n", FALSE);
		}
		else if(wParam == WM_KEYDOWN){
			Add2Log(L"# hook got keydown: %i (0x%x). processed_key is '%i'\r\n", pkbhData->vkCode, pkbhData->vkCode, processed_key);
		}
	}
	//shall we forward processed keys?
	if (processed_key)
	{
		if (bForwardKey){
			Add2Log(L"# hook bForwardKey is TRUE. Resetting processed_key\r\n", FALSE);
			processed_key=false; //reset flag
			Add2Log(L"# hook CallNextHookEx() with processed_key=false\r\n", FALSE);
			return CallNextHookEx(g_hInstalledLLKBDhook, nCode, wParam, lParam);
		}
		else{
			Add2Log(L"# hook bForwardKey is FALSE. Returning...\r\n", FALSE);
			return true;
		}
	}
	else{
		Add2Log(L"# hook CallNextHookEx()\r\n", FALSE);
		return CallNextHookEx(g_hInstalledLLKBDhook, nCode, wParam, lParam);
	}
}