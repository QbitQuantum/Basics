void AFXAPI AfxDumpStack(DWORD dwTarget /* = AFX_STACK_DUMP_TARGET_DEFAULT */)
{
	CTraceClipboardData clipboardData(dwTarget);

	clipboardData.SendOut("=== begin AfxDumpStack output ===\r\n");

	CDWordArray adwAddress;
	HANDLE hProcess = ::GetCurrentProcess();
	if (SymInitialize(hProcess, NULL, FALSE))
	{
		// force undecorated names to get params
		DWORD dw = SymGetOptions();
		dw &= ~SYMOPT_UNDNAME;
		SymSetOptions(dw);

		HANDLE hThread = ::GetCurrentThread();
		CONTEXT threadContext;

		threadContext.ContextFlags = CONTEXT_FULL;

		if (::GetThreadContext(hThread, &threadContext))
		{
			STACKFRAME stackFrame;
			memset(&stackFrame, 0, sizeof(stackFrame));
			stackFrame.AddrPC.Mode = AddrModeFlat;

			DWORD dwMachType;

#if defined(_M_IX86)
			dwMachType                  = IMAGE_FILE_MACHINE_I386;

			// program counter, stack pointer, and frame pointer
			stackFrame.AddrPC.Offset    = threadContext.Eip;
			stackFrame.AddrStack.Offset = threadContext.Esp;
			stackFrame.AddrStack.Mode   = AddrModeFlat;
			stackFrame.AddrFrame.Offset = threadContext.Ebp;
			stackFrame.AddrFrame.Mode   = AddrModeFlat;
#elif defined(_M_MRX000)
			// only program counter
			dwMachType                  = IMAGE_FILE_MACHINE_R4000;
			stackFrame.AddrPC. Offset    = treadContext.Fir;
#elif defined(_M_ALPHA)
			// only program counter
			dwMachType                  = IMAGE_FILE_MACHINE_ALPHA;
			stackFrame.AddrPC.Offset    = (unsigned long) threadContext.Fir;
#elif defined(_M_PPC)
			// only program counter
			dwMachType                  = IMAGE_FILE_MACHINE_POWERPC;
			stackFrame.AddrPC.Offset    = threadContext.Iar;
#elif
#error("Unknown Target Machine");
#endif

			adwAddress.SetSize(0, 16);

			int nFrame;
			for (nFrame = 0; nFrame < 1024; nFrame++)
			{
				if (!StackWalk(dwMachType, hProcess, hProcess,
					&stackFrame, &threadContext, NULL,
					FunctionTableAccess, GetModuleBase, NULL))
				{
					break;
				}

				adwAddress.SetAtGrow(nFrame, stackFrame.AddrPC.Offset);
			}
		}
	}
	else
	{
		DWORD dw = GetLastError();
		char sz[100];
		wsprintfA(sz,
			"AfxDumpStack Error: IMAGEHLP.DLL wasn't found. "
			"GetLastError() returned 0x%8.8X\r\n", dw);
		clipboardData.SendOut(sz);
	}

	// dump it out now
	int nAddress;
	int cAddresses = adwAddress.GetSize();
	for (nAddress = 0; nAddress < cAddresses; nAddress++)
	{
		SYMBOL_INFO info;
		DWORD dwAddress = adwAddress[nAddress];

		char sz[20];
		wsprintfA(sz, "%8.8X: ", dwAddress);
		clipboardData.SendOut(sz);

		if (ResolveSymbol(hProcess, dwAddress, info))
		{
			clipboardData.SendOut(info.szModule);
			clipboardData.SendOut(info.szSymbol);
		}
		else
			clipboardData.SendOut("symbol not found");
		clipboardData.SendOut("\r\n");
	}

	clipboardData.SendOut("=== end AfxDumpStack() output ===\r\n");
}