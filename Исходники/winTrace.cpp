bool DebuggingLoop()
{
	DEBUG_EVENT DebugEvent;
	CONTEXT ctxThreadContext;
	DWORD dwDebugState = NULL;

	PTCHAR sTemp = (PTCHAR)malloc(255 * sizeof(TCHAR));
	szTempSym = (PCHAR)malloc(MAX_SYM_NAME);

	ctxThreadContext.ContextFlags = CONTEXT_FULL;
	
	while(bDebugging)
	{
		if(!WaitForDebugEvent(&DebugEvent,INFINITE))
		{
			free(sTemp);
			free(szTempSym);
			return false;
		}

		switch(DebugEvent.dwDebugEventCode)
		{
		case LOAD_DLL_DEBUG_EVENT:
			{
				SymRefreshModuleList(piProcInfo.hProcess);
				dwDebugState = DBG_CONTINUE;
				break;
			}
		case CREATE_PROCESS_DEBUG_EVENT:
			{
				if(!bSymInit)
					bSymInit = SymInitialize(piProcInfo.hProcess,NULL,FALSE);
				dwDebugState = DBG_CONTINUE;
				break;
			}
		case CREATE_THREAD_DEBUG_EVENT:
			{
				HANDLE hThread = OpenThread(THREAD_ALL_ACCESS,false,DebugEvent.dwThreadId);
				GetThreadContext(hThread,&ctxThreadContext);
				ctxThreadContext.EFlags |= 0x100;
				SetThreadContext(hThread,&ctxThreadContext);

				dwDebugState = DBG_CONTINUE;
				break;
			}
		case EXIT_PROCESS_DEBUG_EVENT:
			{
				bDebugging = false;
				dwDebugState = DBG_CONTINUE;
				break;
			}
		case EXCEPTION_DEBUG_EVENT:
			{
				switch(DebugEvent.u.Exception.ExceptionRecord.ExceptionCode)
				{
				case EXCEPTION_BREAKPOINT:
					{
						dwDebugState = DBG_CONTINUE;
						break;
					}
				case EXCEPTION_SINGLE_STEP:
					{	
						HANDLE hThread = OpenThread(THREAD_ALL_ACCESS,false,DebugEvent.dwThreadId);
						GetThreadContext(hThread,&ctxThreadContext);
						InsertInfo((DWORD)DebugEvent.u.Exception.ExceptionRecord.ExceptionAddress,DebugEvent.dwThreadId,sTemp);
						ctxThreadContext.EFlags |= 0x100;
						SetThreadContext(hThread,&ctxThreadContext);
						dwDebugState = DBG_CONTINUE;
						break;
					}
				default:
					dwDebugState = DBG_EXCEPTION_NOT_HANDLED;
				}
				break;
			}
		default:
			dwDebugState = DBG_EXCEPTION_NOT_HANDLED;
		}
		ContinueDebugEvent(DebugEvent.dwProcessId,DebugEvent.dwThreadId,dwDebugState);
	}
	free(sTemp);
	free(szTempSym);
	return false;
}