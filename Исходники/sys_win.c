static void stack_trace( PEXCEPTION_POINTERS pInfo )
{
	char message[1024];
	int len = 0;
	size_t i;
	HANDLE process = GetCurrentProcess();
	HANDLE thread = GetCurrentThread();
	IMAGEHLP_LINE64 line;
	DWORD dline = 0;
	DWORD options;
	CONTEXT context;
	STACKFRAME64 stackframe;
	DWORD image;

	memcpy( &context, pInfo->ContextRecord, sizeof(CONTEXT) );
	options = SymGetOptions(); 
	options |= SYMOPT_DEBUG;
	options |= SYMOPT_LOAD_LINES;
	SymSetOptions( options ); 

	SymInitialize( process, NULL, TRUE );

	

	ZeroMemory( &stackframe, sizeof(STACKFRAME64) );

#ifdef _M_IX86
	image = IMAGE_FILE_MACHINE_I386;
	stackframe.AddrPC.Offset = context.Eip;
	stackframe.AddrPC.Mode = AddrModeFlat;
	stackframe.AddrFrame.Offset = context.Ebp;
	stackframe.AddrFrame.Mode = AddrModeFlat;
	stackframe.AddrStack.Offset = context.Esp;
	stackframe.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
	image = IMAGE_FILE_MACHINE_AMD64;
	stackframe.AddrPC.Offset = context.Rip;
	stackframe.AddrPC.Mode = AddrModeFlat;
	stackframe.AddrFrame.Offset = context.Rsp;
	stackframe.AddrFrame.Mode = AddrModeFlat;
	stackframe.AddrStack.Offset = context.Rsp;
	stackframe.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
	image = IMAGE_FILE_MACHINE_IA64;
	stackframe.AddrPC.Offset = context.StIIP;
	stackframe.AddrPC.Mode = AddrModeFlat;
	stackframe.AddrFrame.Offset = context.IntSp;
	stackframe.AddrFrame.Mode = AddrModeFlat;
	stackframe.AddrBStore.Offset = context.RsBSP;
	stackframe.AddrBStore.Mode = AddrModeFlat;
	stackframe.AddrStack.Offset = context.IntSp;
	stackframe.AddrStack.Mode = AddrModeFlat;
#endif
	len += snprintf( message + len, 1024 - len, "Sys_Crash: address %p, code %p\n", pInfo->ExceptionRecord->ExceptionAddress, pInfo->ExceptionRecord->ExceptionCode );
	if( SymGetLineFromAddr64( process, (DWORD64)pInfo->ExceptionRecord->ExceptionAddress, &dline, &line ) )
	{
		len += snprintf(message + len, 1024 - len,"Exception: %s:%d:%d\n", (char*)line.FileName, (int)line.LineNumber, (int)dline);
	}
	if( SymGetLineFromAddr64( process, stackframe.AddrPC.Offset, &dline, &line ) )
	{
		len += snprintf(message + len, 1024 - len,"PC: %s:%d:%d\n", (char*)line.FileName, (int)line.LineNumber, (int)dline);
	}
	if( SymGetLineFromAddr64( process, stackframe.AddrFrame.Offset, &dline, &line ) )
	{
		len += snprintf(message + len, 1024 - len,"Frame: %s:%d:%d\n", (char*)line.FileName, (int)line.LineNumber, (int)dline);
	}
	for( i = 0; i < 25; i++ )
	{
		char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
		PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
		BOOL result = StackWalk64(
			image, process, thread,
			&stackframe, &context, NULL,
			SymFunctionTableAccess64, SymGetModuleBase64, NULL);

		DWORD64 displacement = 0;
		if( !result )
			break;

		
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = MAX_SYM_NAME;

		len += snprintf( message + len, 1024 - len, "% 2d %p", i, (void*)stackframe.AddrPC.Offset );
		if( SymFromAddr( process, stackframe.AddrPC.Offset, &displacement, symbol ) )
		{
			len += snprintf( message + len, 1024 - len, " %s ", symbol->Name );
		}
		if( SymGetLineFromAddr64( process, stackframe.AddrPC.Offset, &dline, &line ) )
		{
			len += snprintf(message + len, 1024 - len,"(%s:%d:%d) ", (char*)line.FileName, (int)line.LineNumber, (int)dline);
		}
		len += snprintf( message + len, 1024 - len, "(");
		len += ModuleName( process, message + len, (void*)stackframe.AddrPC.Offset, 1024 - len );
		len += snprintf( message + len, 1024 - len, ")\n");
	}
#ifdef XASH_SDL
	if( host.type != HOST_DEDICATED ) // let system to restart server automaticly
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Sys_Crash", message, host.hWnd );
#endif
	Sys_PrintLog(message);

	SymCleanup(process);
}