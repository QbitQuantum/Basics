void stack_walk(CString& strStack, PCONTEXT p_context)
{ 

	CONTEXT * pContext = p_context;

	HANDLE hCurrentProcess = ::GetCurrentProcess();
	HANDLE hCurrentThread  = ::GetCurrentThread();

	STACKFRAME64 sStackFrame;
	memset(&sStackFrame,0,sizeof(STACKFRAME64));

	sStackFrame.AddrPC.Offset	= pContext->Eip;
	sStackFrame.AddrPC.Mode		= AddrModeFlat;
	sStackFrame.AddrStack.Offset= pContext->Esp;
	sStackFrame.AddrStack.Mode	= AddrModeFlat;
	sStackFrame.AddrFrame.Offset= pContext->Ebp;
	sStackFrame.AddrFrame.Mode	= AddrModeFlat;

	USES_CONVERSION;

	//TCHAR atszCallbackBuffer[1024];
	//DWORD dwLen = 0;

	SymInitialize(GetCurrentProcess(),NULL,TRUE);

	while(StackWalk64(IMAGE_FILE_MACHINE_I386,hCurrentProcess,hCurrentThread,&sStackFrame,pContext,0,0,0,0))
	{
		if( sStackFrame.AddrFrame.Offset == 0 )
		{
			break;
		}

		strStack.Format(L"%s[%08X]", strStack,sStackFrame.AddrPC.Offset);

		BYTE sym_buffer[sizeof(IMAGEHLP_SYMBOL) + 512];
		PIMAGEHLP_SYMBOL p_symbol = (PIMAGEHLP_SYMBOL)sym_buffer;
		p_symbol->SizeOfStruct = sizeof(sym_buffer);
		p_symbol->MaxNameLength = 512;

		// Displacement of the input address, relative to the start of the symbol
		DWORD sym_displacement = 0;  
		if (!SymGetSymFromAddr(::GetCurrentProcess(), sStackFrame.AddrPC.Offset, &sym_displacement, p_symbol))
		{
			p_symbol->Name[0] = 0;
		}
		TCHAR sz_module[MAX_PATH] = {0};
		UINT_PTR section = 0, offset = 0;
		get_logical_address((PVOID)(UINT_PTR)sStackFrame.AddrPC.Offset, sz_module, sizeof(sz_module));

		strStack.Format(L"%s\t%s\t%s\r\n",strStack,A2T(p_symbol->Name),sz_module);

	}

	SymCleanup(GetCurrentProcess());
}