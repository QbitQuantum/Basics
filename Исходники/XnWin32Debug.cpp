XN_C_API XnStatus xnOSGetCurrentCallStack(XnInt32 nFramesToSkip, XnChar** astrFrames, XnUInt32 nMaxNameLength, XnInt32* pnFrames)
{
	if (*pnFrames == 0 || nMaxNameLength == 0)
	{
		return XN_STATUS_OK;
	}

	// Init
	if (!g_bInitialized)
	{
		Init();
		g_bInitialized = TRUE;
	}

	if (!g_bAvailable)
	{
		xnOSStrNCopy(astrFrames[0], "dbghelp.dll unavailable!", nMaxNameLength-1, nMaxNameLength);
		return XN_STATUS_ERROR;
	}

	// Get context
	CONTEXT context;
	RtlCaptureContext(&context);

	// init STACKFRAME for first call - Fill data according to processor (see WalkTrace64 and STACKFRAME64 documentation)
	STACKFRAME64 stackFrame;
	memset(&stackFrame, 0, sizeof(stackFrame));

	DWORD MachineType;
#ifdef _M_IX86
	MachineType = IMAGE_FILE_MACHINE_I386;
	stackFrame.AddrPC.Offset = context.Eip;
	stackFrame.AddrPC.Mode = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Ebp;
	stackFrame.AddrFrame.Mode = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Esp;
	stackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
	MachineType = IMAGE_FILE_MACHINE_AMD64;
	stackFrame.AddrPC.Offset = context.Rip;
	stackFrame.AddrPC.Mode = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Rsp;
	stackFrame.AddrFrame.Mode = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Rsp;
	stackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
	MachineType = IMAGE_FILE_MACHINE_IA64;
	stackFrame.AddrPC.Offset = context.StIIP;
	stackFrame.AddrPC.Mode = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.IntSp;
	stackFrame.AddrFrame.Mode = AddrModeFlat;
	stackFrame.AddrBStore.Offset = context.RsBSP;
	stackFrame.AddrBStore.Mode = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.IntSp;
	stackFrame.AddrStack.Mode = AddrModeFlat;
#else
#error "Platform not supported!"
#endif

	XnInt32 nFrames = 0;
	XnInt32 iFrame = 0;
	const XnUInt32 BUFFER_SIZE = 1024;
	XnChar symbolBuffer[BUFFER_SIZE];
	SYMBOL_INFO* pSymbolInfo = (SYMBOL_INFO*)symbolBuffer;
	pSymbolInfo->SizeOfStruct = sizeof(SYMBOL_INFO);
	pSymbolInfo->MaxNameLen = BUFFER_SIZE - sizeof(SYMBOL_INFO) - 1;

	HANDLE currentProcess = GetCurrentProcess();
	HANDLE currentThread = GetCurrentThread();
	while (iFrame < *pnFrames)
	{
		// walk the stack
		if (!g_pStackWalk64(MachineType, currentProcess, currentThread, &stackFrame, &context, NULL, g_pSymFunctionTableAccess64, g_pSymGetModuleBase64, NULL))
		{
			// probably reached end
			break;
		}

		if (nFrames >= nFramesToSkip)
		{
			// resolve function name
			BOOL found = g_pSymFromAddr(currentProcess, stackFrame.AddrPC.Offset, NULL, pSymbolInfo);

			UINT32 lineNum = 0;
			XnChar* strFileName = NULL;
			if (g_pSymGetLineFromAddr64 != NULL)
			{
				IMAGEHLP_LINE64 line;
				DWORD displacement;
				if (g_pSymGetLineFromAddr64(currentProcess, stackFrame.AddrPC.Offset, &displacement, &line))
				{
					lineNum = line.LineNumber;
					strFileName = line.FileName;
				}
			}

			XnUInt32 nWritten;
			if (found)
			{
				if (lineNum != 0)
				{
					xnOSStrFormat(astrFrames[iFrame], nMaxNameLength, &nWritten, "%s() Line %lu", pSymbolInfo->Name, lineNum);
				}
				else
				{
					xnOSStrFormat(astrFrames[iFrame], nMaxNameLength, &nWritten, "%s()", pSymbolInfo->Name);
				}
			}
			else
			{
				if ((strFileName != NULL) && (lineNum != 0))
				{
					xnOSStrFormat(astrFrames[iFrame], nMaxNameLength, &nWritten, "%s Line %lu", strFileName, lineNum);
				}
				else if (strFileName != NULL)
				{
					xnOSStrFormat(astrFrames[iFrame], nMaxNameLength, &nWritten, "0x%x %s", stackFrame.AddrPC.Offset, strFileName);
				}
				else
				{
					xnOSStrFormat(astrFrames[iFrame], nMaxNameLength, &nWritten, "0x%x", stackFrame.AddrPC.Offset);
				}
			}

			++iFrame;
		}

		++nFrames;
	}

	*pnFrames = iFrame;

	return XN_STATUS_OK;
}