static void
dump_thread(void *arg)
{
    HANDLE dbghelp;
    BOOL (WINAPI *pSymInitialize)(HANDLE, const char *, BOOL);
    BOOL (WINAPI *pSymCleanup)(HANDLE);
    BOOL (WINAPI *pStackWalk64)(DWORD, HANDLE, HANDLE, STACKFRAME64 *, void *, PREAD_PROCESS_MEMORY_ROUTINE64, PFUNCTION_TABLE_ACCESS_ROUTINE64, PGET_MODULE_BASE_ROUTINE64, PTRANSLATE_ADDRESS_ROUTINE64);
    DWORD64 (WINAPI *pSymGetModuleBase64)(HANDLE, DWORD64);
    BOOL (WINAPI *pSymFromAddr)(HANDLE, DWORD64, DWORD64 *, SYMBOL_INFO *);
    BOOL (WINAPI *pSymGetLineFromAddr64)(HANDLE, DWORD64, DWORD *, IMAGEHLP_LINE64 *);
    HANDLE (WINAPI *pOpenThread)(DWORD, BOOL, DWORD);
    DWORD tid = *(DWORD *)arg;
    HANDLE ph;
    HANDLE th;

    dbghelp = LoadLibrary("dbghelp.dll");
    if (!dbghelp) return;
    pSymInitialize = (BOOL (WINAPI *)(HANDLE, const char *, BOOL))GetProcAddress(dbghelp, "SymInitialize");
    pSymCleanup = (BOOL (WINAPI *)(HANDLE))GetProcAddress(dbghelp, "SymCleanup");
    pStackWalk64 = (BOOL (WINAPI *)(DWORD, HANDLE, HANDLE, STACKFRAME64 *, void *, PREAD_PROCESS_MEMORY_ROUTINE64, PFUNCTION_TABLE_ACCESS_ROUTINE64, PGET_MODULE_BASE_ROUTINE64, PTRANSLATE_ADDRESS_ROUTINE64))GetProcAddress(dbghelp, "StackWalk64");
    pSymGetModuleBase64 = (DWORD64 (WINAPI *)(HANDLE, DWORD64))GetProcAddress(dbghelp, "SymGetModuleBase64");
    pSymFromAddr = (BOOL (WINAPI *)(HANDLE, DWORD64, DWORD64 *, SYMBOL_INFO *))GetProcAddress(dbghelp, "SymFromAddr");
    pSymGetLineFromAddr64 = (BOOL (WINAPI *)(HANDLE, DWORD64, DWORD *, IMAGEHLP_LINE64 *))GetProcAddress(dbghelp, "SymGetLineFromAddr64");
    pOpenThread = (HANDLE (WINAPI *)(DWORD, BOOL, DWORD))GetProcAddress(GetModuleHandle("kernel32.dll"), "OpenThread");
    if (pSymInitialize && pSymCleanup && pStackWalk64 && pSymGetModuleBase64 &&
	pSymFromAddr && pSymGetLineFromAddr64 && pOpenThread) {
	SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_DEBUG | SYMOPT_LOAD_LINES);
	ph = GetCurrentProcess();
	pSymInitialize(ph, NULL, TRUE);
	th = pOpenThread(THREAD_SUSPEND_RESUME|THREAD_GET_CONTEXT, FALSE, tid);
	if (th) {
	    if (SuspendThread(th) != (DWORD)-1) {
		CONTEXT context;
		memset(&context, 0, sizeof(context));
		context.ContextFlags = CONTEXT_FULL;
		if (GetThreadContext(th, &context)) {
		    char libpath[MAX_PATH];
		    char buf[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
		    SYMBOL_INFO *info = (SYMBOL_INFO *)buf;
		    DWORD mac;
		    STACKFRAME64 frame;
		    memset(&frame, 0, sizeof(frame));
#if defined(_M_AMD64) || defined(__x86_64__)
		    mac = IMAGE_FILE_MACHINE_AMD64;
		    frame.AddrPC.Mode = AddrModeFlat;
		    frame.AddrPC.Offset = context.Rip;
		    frame.AddrFrame.Mode = AddrModeFlat;
		    frame.AddrFrame.Offset = context.Rbp;
		    frame.AddrStack.Mode = AddrModeFlat;
		    frame.AddrStack.Offset = context.Rsp;
#elif defined(_M_IA64) || defined(__ia64__)
		    mac = IMAGE_FILE_MACHINE_IA64;
		    frame.AddrPC.Mode = AddrModeFlat;
		    frame.AddrPC.Offset = context.StIIP;
		    frame.AddrBStore.Mode = AddrModeFlat;
		    frame.AddrBStore.Offset = context.RsBSP;
		    frame.AddrStack.Mode = AddrModeFlat;
		    frame.AddrStack.Offset = context.IntSp;
#else	/* i386 */
		    mac = IMAGE_FILE_MACHINE_I386;
		    frame.AddrPC.Mode = AddrModeFlat;
		    frame.AddrPC.Offset = context.Eip;
		    frame.AddrFrame.Mode = AddrModeFlat;
		    frame.AddrFrame.Offset = context.Ebp;
		    frame.AddrStack.Mode = AddrModeFlat;
		    frame.AddrStack.Offset = context.Esp;
#endif

		    while (pStackWalk64(mac, ph, th, &frame, &context, NULL,
					NULL, NULL, NULL)) {
			DWORD64 addr = frame.AddrPC.Offset;
			IMAGEHLP_LINE64 line;
			DWORD64 displacement;
			DWORD tmp;

			if (addr == frame.AddrReturn.Offset || addr == 0 ||
			    frame.AddrReturn.Offset == 0)
			    break;

			memset(buf, 0, sizeof(buf));
			info->SizeOfStruct = sizeof(SYMBOL_INFO);
			info->MaxNameLen = MAX_SYM_NAME;
			if (pSymFromAddr(ph, addr, &displacement, info)) {
			    if (GetModuleFileName((HANDLE)(uintptr_t)pSymGetModuleBase64(ph, addr), libpath, sizeof(libpath)))
				fprintf(stderr, "%s", libpath);
			    fprintf(stderr, "(%s+0x%I64x)",
				    info->Name, displacement);
			}
			fprintf(stderr, " [0x%p]", (void *)(VALUE)addr);
			memset(&line, 0, sizeof(line));
			line.SizeOfStruct = sizeof(line);
			if (pSymGetLineFromAddr64(ph, addr, &tmp, &line))
			    fprintf(stderr, " %s:%lu", line.FileName, line.LineNumber);
			fprintf(stderr, "\n");
		    }
		}

		ResumeThread(th);
	    }
	    CloseHandle(th);
	}
	pSymCleanup(ph);
    }
    FreeLibrary(dbghelp);
}