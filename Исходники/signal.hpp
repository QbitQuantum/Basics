void kul_real_se_handler(EXCEPTION_POINTERS* pExceptionInfo){
	const std::string& tid(kul::this_thread::id());
	uint sig = pExceptionInfo->ExceptionRecord->ExceptionCode;
	if(pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
    	for(auto& f : kul::SignalStatic::INSTANCE().se) f(sig = 11);

    if(!kul::SignalStatic::INSTANCE().q){
	    HANDLE process = GetCurrentProcess();
	    SymInitialize(process, NULL, TRUE);

	    CONTEXT context_record = *pExceptionInfo->ContextRecord;

	    STACKFRAME64 stack_frame;
	    memset(&stack_frame, 0, sizeof(stack_frame));
	    #if defined(_WIN64)
	    int machine_type = IMAGE_FILE_MACHINE_AMD64;
	    stack_frame.AddrPC.Offset = context_record.Rip;
	    stack_frame.AddrFrame.Offset = context_record.Rbp;
	    stack_frame.AddrStack.Offset = context_record.Rsp;
	    #else
	    int machine_type = IMAGE_FILE_MACHINE_I386;
	    stack_frame.AddrPC.Offset = context_record.Eip;
	    stack_frame.AddrFrame.Offset = context_record.Ebp;
	    stack_frame.AddrStack.Offset = context_record.Esp;
	    #endif
	    stack_frame.AddrPC.Mode = AddrModeFlat;
	    stack_frame.AddrFrame.Mode = AddrModeFlat;
	    stack_frame.AddrStack.Mode = AddrModeFlat;

	    SYMBOL_INFO* symbol;
	    symbol               = ( SYMBOL_INFO * )calloc( sizeof( SYMBOL_INFO ) + 256 * sizeof( char ), 1 );
	    symbol->MaxNameLen   = 255;
	    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	    std::cout << "[bt] Stacktrace:" << std::endl;
	    while (StackWalk64(machine_type,
	        GetCurrentProcess(),
	        GetCurrentThread(),
	        &stack_frame,
	        &context_record,
	        NULL,
	        &SymFunctionTableAccess64,
	        &SymGetModuleBase64,
	        NULL)) {

	        DWORD64 displacement = 0;
	        if (SymFromAddr(process, (DWORD64)stack_frame.AddrPC.Offset, &displacement, symbol)){
	        	DWORD  dwDisplacement;
				IMAGEHLP_LINE64 line;
				IMAGEHLP_MODULE64 moduleInfo;
	            ZeroMemory(&moduleInfo, sizeof(IMAGEHLP_MODULE64));
	            moduleInfo.SizeOfStruct = sizeof(moduleInfo);

	            std::cout << "[bt] ";
	            if (::SymGetModuleInfo64(process, symbol->ModBase, &moduleInfo))
	            	std::cout << moduleInfo.ModuleName << " ";

	            std::cout << symbol->Name << " + [0x" << std::hex << displacement << "]"; 

				if (SymGetLineFromAddr64(process, (DWORD64)stack_frame.AddrPC.Offset, &dwDisplacement, &line))
					std::cout << " - " << line.FileName << ": " << std::to_string(line.LineNumber);
				else
					std::cout << " - ??:";
				std::cout << std::endl;
	        }
	    }
    }
	exit(sig);
}