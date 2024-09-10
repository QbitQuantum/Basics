static void	print_backtrace(CONTEXT *pctx)
{
	SymGetLineFromAddrW64_func_t	zbx_SymGetLineFromAddrW64 = NULL;
	SymFromAddr_func_t		zbx_SymFromAddr	= NULL;

	CONTEXT			ctx, ctxcount;
	STACKFRAME64		s, scount;
	PSYMBOL_INFO		pSym = NULL;
	HMODULE			hModule;
	HANDLE			hProcess, hThread;
	DWORD64			offset;
	wchar_t			szProcessName[MAX_PATH];
	char			*process_name = NULL, *process_path = NULL, *frame = NULL;
	size_t			frame_alloc = 0, frame_offset;
	int			nframes = 0;

	ctx = *pctx;

	zabbix_log(LOG_LEVEL_CRIT, "=== Backtrace: ===");

	memset(&s, 0, sizeof(s));

	s.AddrPC.Mode = AddrModeFlat;
	s.AddrFrame.Mode = AddrModeFlat;
	s.AddrStack.Mode = AddrModeFlat;

#ifdef _M_X64
	s.AddrPC.Offset = ctx.Rip;
	s.AddrFrame.Offset = ctx.Rbp;
	s.AddrStack.Offset = ctx.Rsp;
#else
	s.AddrPC.Offset = ctx.Eip;
	s.AddrFrame.Offset = ctx.Ebp;
	s.AddrStack.Offset = ctx.Esp;
#endif
	hProcess = GetCurrentProcess();
	hThread = GetCurrentThread();

	if (0 != GetModuleFileNameEx(hProcess, NULL, szProcessName, ARRSIZE(szProcessName)))
	{
		char	*ptr;
		int	path_alloc = 0, path_offset = 0;

		process_name = zbx_unicode_to_utf8(szProcessName);

		if (NULL != (ptr = strstr(process_name, progname)))
			zbx_strncpy_alloc(&process_path, &path_alloc, &path_offset, process_name, ptr - process_name);
	}

	if (NULL != (hModule = GetModuleHandle(TEXT("DbgHelp.DLL"))))
	{
		zbx_SymGetLineFromAddrW64 = (SymGetLineFromAddrW64_func_t)GetProcAddress(hModule,
				"SymGetLineFromAddr64");
		zbx_SymFromAddr = (SymFromAddr_func_t)GetProcAddress(hModule, "SymFromAddr");
	}

	if (NULL != zbx_SymFromAddr || NULL != zbx_SymGetLineFromAddrW64)
	{
		SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);

		if (FALSE != SymInitialize(hProcess, process_path, TRUE))
		{
			pSym = (PSYMBOL_INFO) zbx_malloc(NULL, sizeof(SYMBOL_INFO) + MAX_SYM_NAME);
			memset(pSym, 0, sizeof(SYMBOL_INFO) + MAX_SYM_NAME);
			pSym->SizeOfStruct = sizeof(SYMBOL_INFO);
			pSym->MaxNameLen = MAX_SYM_NAME;
		}
	}

	scount = s;
	ctxcount = ctx;

	/* get number of frames, ctxcount may be modified during StackWalk64() calls */
	while (TRUE == StackWalk64(ZBX_IMAGE_FILE_MACHINE, hProcess, hThread, &scount, &ctxcount, NULL, NULL, NULL,
			NULL))
	{
		if (0 == scount.AddrReturn.Offset)
			break;
		nframes++;
	}

	while (TRUE == StackWalk64(ZBX_IMAGE_FILE_MACHINE, hProcess, hThread, &s, &ctx, NULL, NULL, NULL, NULL))
	{
		frame_offset = 0;
		zbx_snprintf_alloc(&frame, &frame_alloc, &frame_offset, "%d: %s", nframes--,
				NULL == process_name ? "(unknown)" : process_name);

		if (NULL != pSym)
		{
			DWORD		dwDisplacement;
			IMAGEHLP_LINE64	line = {sizeof(IMAGEHLP_LINE64)};

			zbx_chrcpy_alloc(&frame, &frame_alloc, &frame_offset, '(');
			if (NULL != zbx_SymFromAddr &&
					TRUE == zbx_SymFromAddr(hProcess, s.AddrPC.Offset, &offset, pSym))
			{
				zbx_snprintf_alloc(&frame, &frame_alloc, &frame_offset, "%s+0x%lx", pSym->Name, offset);
			}

			if (NULL != zbx_SymGetLineFromAddrW64 && TRUE == zbx_SymGetLineFromAddrW64(hProcess,
					s.AddrPC.Offset, &dwDisplacement, &line))
			{
				zbx_snprintf_alloc(&frame, &frame_alloc, &frame_offset, " %s:%d", line.FileName,
						line.LineNumber);
			}
			zbx_chrcpy_alloc(&frame, &frame_alloc, &frame_offset, ')');
		}

		zabbix_log(LOG_LEVEL_CRIT, "%s [0x%lx]", frame, s.AddrPC.Offset);

		if (0 == s.AddrReturn.Offset)
			break;
	}

	SymCleanup(hProcess);

	zbx_free(frame);
	zbx_free(process_path);
	zbx_free(process_name);
	zbx_free(pSym);
}