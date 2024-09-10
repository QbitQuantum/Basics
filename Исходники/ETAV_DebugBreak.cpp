STATUS 
DbgThreadSetBreakpoint(
	IN PHWBREAKDATA BreakpointData
	)
{
	HANDLE hThread;
	DWORD dwDebugRegister;
	CONTEXT	ctxThreadContext = {0};
	ERRORINFO err;
	CHAR szBreakType[20] = {'\0'};
	ctxThreadContext.ContextFlags = CONTEXT_DEBUG_REGISTERS;

	/* Open thread with desired access */
	hThread = OpenThread( THREAD_SET_CONTEXT | THREAD_GET_CONTEXT | THREAD_SUSPEND_RESUME , 
		                   FALSE, 
						   BreakpointData->dwThreadId);
	if ( hThread == NULL )
	{
		REPORT_ERROR("OpenThread()", &err);
		/* Set the Error Flag to proper value */
		BreakpointData->dwStatus = DR_BREAK_ERROR_UNK; 
		return PWNYPOT_STATUS_INTERNAL_ERROR;
	}

	/* Is thread already suspend ? */
	if ( BreakpointData->dwThreadStatus != THREAD_ALREADY_SUSPEND )
	{
		/* Suspend thread for getting/setting thread context in a safe manner */
		if ( SuspendThread(hThread) == -1 )
		{
			REPORT_ERROR("SuspendThread()",&err);
			BreakpointData->dwStatus = DR_BREAK_ERROR_UNK;
			return PWNYPOT_STATUS_INTERNAL_ERROR;

		}
	}
	
	/* Get thread current context */
	if ( !GetThreadContext(hThread,&ctxThreadContext) )
	{
		REPORT_ERROR("GetThreadContext()",&err);
		BreakpointData->dwStatus = DR_BREAK_ERROR_UNK;
		return PWNYPOT_STATUS_INTERNAL_ERROR;
	}
	
	/* check if Dr(n) is busy with another Hardware Breakpoint? */
	if ( !IsBitSet(ctxThreadContext.Dr7,0) || !IsBitSet(ctxThreadContext.Dr7,1) )
	{
		/* Set the Debug Register */
		dwDebugRegister = 0;
		/* Set the breakpoint address */
		ctxThreadContext.Dr0 = (DWORD)BreakpointData->Address;
		/* Set Dr(n) state as a busy register, it can be use for removing specific breakpoint */
		BreakpointData->dwDrBusyRemove = dwDebugRegister;

	} else if ( !IsBitSet(ctxThreadContext.Dr7,2) || !IsBitSet(ctxThreadContext.Dr7,3) )
	{
		dwDebugRegister = 1;
		ctxThreadContext.Dr1 = (DWORD)BreakpointData->Address;
		BreakpointData->dwDrBusyRemove = dwDebugRegister;

	} else if ( !IsBitSet(ctxThreadContext.Dr7,4) || !IsBitSet(ctxThreadContext.Dr7,5) )
	{
		dwDebugRegister = 2;
		ctxThreadContext.Dr2 = (DWORD)BreakpointData->Address;
		BreakpointData->dwDrBusyRemove = dwDebugRegister;

	} else if ( !IsBitSet(ctxThreadContext.Dr7,6) || !IsBitSet(ctxThreadContext.Dr7,7) )
	{
		dwDebugRegister = 3;
		ctxThreadContext.Dr3 = (DWORD)BreakpointData->Address;
		BreakpointData->dwDrBusyRemove = dwDebugRegister;

	} else 
	{
		/* All Debug Registers are busy */
		BreakpointData->dwStatus = DR_ALL_BUSY;
		return PWNYPOT_STATUS_GENERAL_FAIL;
	}

	/* Set the proper bit in Dr7 for used Debug Register and Breakpoint type */
	ctxThreadContext.Dr7 |= 1 << (dwDebugRegister * 2);
	ctxThreadContext.Dr7 |= BreakpointData->dwCondition << ((dwDebugRegister * 4) + 16);
	ctxThreadContext.Dr7 |= 1 << ((dwDebugRegister * 4) + 18);

	/* Enable the Breakpoint for thread by setting the thread context */
	if ( !SetThreadContext(hThread,&ctxThreadContext) )
	{
		REPORT_ERROR("GetThreadContext()",&err);
		BreakpointData->dwStatus = DR_BREAK_ERROR_UNK;
		return PWNYPOT_STATUS_INTERNAL_ERROR;
	}

	BreakpointData->dwStatus = DR_BREAK_SET;
	switch ( BreakpointData->dwCondition )
	{
	case HW_ACCESS:
		strncpy( szBreakType, HW_ACCESS_STR, 20);
		break;
	case HW_EXECUTE:
		strncpy( szBreakType, HW_EXECUTE_STR, 20);
		break;
	case HW_WRITE:
		strncpy( szBreakType, HW_WRITE_STR, 20);
		break;
	}

	DEBUG_PRINTF(LDBG, NULL, "Breakpoint On | TID : %p - Dr%d - Len : %d - Condition : %s!\n", BreakpointData->dwThreadId , dwDebugRegister, BreakpointData->dwSize , szBreakType);
	
	/* Resume the thread if it was not in suspend state at creation time */
	if ( BreakpointData->dwThreadStatus != THREAD_ALREADY_SUSPEND )
		ResumeThread(hThread);
	return PWNYPOT_STATUS_SUCCESS;
}