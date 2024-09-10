bool Profiler::sampleTarget(SAMPLE_TYPE timeSpent, SymbolInfo *syminfo)
{
	// DE: 20090325: Moved declaration of stack variables to reduce size of code inside Suspend/Resume thread

	CallStack stack;
	stack.depth = 0;

	STACKFRAME64 frame;
	PROFILER_ADDR ip, sp, bp;
	void *context;
	DWORD machine;

#if defined(_WIN64)
	CONTEXT64 threadcontext64;
	CONTEXT32 threadcontext32;
	if (is64BitProcess)
	{
		context = &threadcontext64;
		threadcontext64.ContextFlags = CONTEXT64_FLAGS;
		machine = IMAGE_FILE_MACHINE_AMD64;

		// Can fail occasionally, for example if you have a debugger attached to the process.
		HRESULT result = SuspendThread(target_thread);
		if(result == 0xffffffff)
			return false;

		int prev_priority = GetThreadPriority(target_thread);
		SetThreadPriority(target_thread, THREAD_PRIORITY_TIME_CRITICAL);
		result = GetThreadContext(target_thread, &threadcontext64);
		SetThreadPriority(target_thread, prev_priority);

		if(!result){
			// DE: 20090325: If GetThreadContext fails we must be sure to resume thread again
			ResumeThread(target_thread);
			return false;
		}

		ip = threadcontext64.Rip;
		sp = threadcontext64.Rsp;
		bp = threadcontext64.Rbp;
	} else {
		context = &threadcontext32;
		threadcontext32.ContextFlags = CONTEXT32_FLAGS;
		machine = IMAGE_FILE_MACHINE_I386;

		// Can fail occasionally, for example if you have a debugger attached to the process.
		HRESULT result = fn_Wow64SuspendThread(target_thread);
		if(result == 0xffffffff)
			return false;

		int prev_priority = GetThreadPriority(target_thread);
		SetThreadPriority(target_thread, THREAD_PRIORITY_TIME_CRITICAL);
		result = fn_Wow64GetThreadContext(target_thread, &threadcontext32);
		SetThreadPriority(target_thread, prev_priority);

		if(!result){
			// DE: 20090325: If GetThreadContext fails we must be sure to resume thread again
			ResumeThread(target_thread);
			return false;
		}

		ip = threadcontext32.Eip;
		sp = threadcontext32.Esp;
		bp = threadcontext32.Ebp;
	}
#else
	CONTEXT32 threadcontext32;
	context = &threadcontext32;
	threadcontext32.ContextFlags = CONTEXT32_FLAGS;
	machine = IMAGE_FILE_MACHINE_I386;

	// Can fail occasionally, for example if you have a debugger attached to the process.
	HRESULT result = SuspendThread(target_thread);
	if(result == 0xffffffff)
		return false;

	int prev_priority = GetThreadPriority(target_thread);
	SetThreadPriority(target_thread, THREAD_PRIORITY_TIME_CRITICAL);
	result = GetThreadContext(target_thread, &threadcontext32);
	SetThreadPriority(target_thread, prev_priority);

	if(!result){
		// DE: 20090325: If GetThreadContext fails we must be sure to resume thread again
		ResumeThread(target_thread);
		return false;
	}

	applyHacks(target_process, threadcontext32);

	ip = threadcontext32.Eip;
	sp = threadcontext32.Esp;
	bp = threadcontext32.Ebp;
#endif

	DbgHelp *prevDbgHelp = NULL;
	bool first = true;

	while(true)
	{
		// See which module this IP is in.
		Module *mod = syminfo->getModuleForAddr(ip);
		DbgHelp *dbgHelp = mod ? mod->dbghelp : &dbgHelpMs;

		// Use whichever dbghelp stack walker is best for this module type.
		// If we're switching between types, restart the stack walk from 
		// the current place.
		if (dbgHelp != prevDbgHelp)
		{
			prevDbgHelp = dbgHelp;
			memset(&frame, 0, sizeof(frame));
			frame.AddrStack.Offset = sp;
			frame.AddrPC.Offset = ip;
			frame.AddrFrame.Offset = bp;
			frame.AddrStack.Mode = frame.AddrPC.Mode = frame.AddrFrame.Mode = AddrModeFlat;
			frame.AddrReturn.Offset = ip;
			first = true;
		}

		// Add this IP to the stack trace.
		// We skip the first one, as the first call to StackWalk64
		// simply fills in more registers for the current frame,
		// rather than walking down to the next one.
		if (!first)
			stack.addr[stack.depth++] = ip;
		first = false;

		BOOL result = dbgHelp->StackWalk64(
			machine,
			target_process,
			target_thread,
			&frame,
			context,
			NULL,
			dbgHelp->SymFunctionTableAccess64,
			dbgHelp->SymGetModuleBase64,
			NULL
		);

		if (!result || stack.depth >= MAX_CALLSTACK_LEVELS)
			break;

		ip = (PROFILER_ADDR)frame.AddrPC.Offset;
		sp = (PROFILER_ADDR)frame.AddrStack.Offset;
		bp = (PROFILER_ADDR)frame.AddrFrame.Offset;

		// Stop once we hit the end of the stack.
		if (frame.AddrReturn.Offset == 0)
		{
			stack.addr[stack.depth++] = ip;
			break;
		}
	}

	if (!ResumeThread(target_thread))
		throw ProfilerExcep(L"ResumeThread failed.");

	//NOTE: this has to go after ResumeThread.  Otherwise mem allocation needed by std::map
	//may hit a lock held by the suspended thread.
	if (stack.depth > 0)
	{
		flatcounts[stack.addr[0]]+=timeSpent;
		callstacks[stack]+=timeSpent;
	}
	return true;
}