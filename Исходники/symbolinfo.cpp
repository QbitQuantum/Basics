const std::wstring SymbolInfo::getProcForAddr(PROFILER_ADDR addr, 
											  std::wstring& procfilepath_out, int& proclinenum_out)
{
	procfilepath_out = L"";
	proclinenum_out = 0;

	Module *mod = getModuleForAddr(addr);
	DbgHelp *dbgHelp = mod ? mod->dbghelp : &dbgHelpMs;

	unsigned char buffer[1024];

	//blame MS for this abomination of a coding technique
	SYMBOL_INFOW* symbol_info = (SYMBOL_INFOW*)buffer;
	symbol_info->SizeOfStruct = sizeof(SYMBOL_INFOW);
	symbol_info->MaxNameLen = ((sizeof(buffer) - sizeof(SYMBOL_INFOW)) / sizeof(WCHAR)) - 1;

	DWORD64 displacement = 0;
	BOOL result = dbgHelp->SymFromAddrW(process_handle, (DWORD64)addr, &displacement, symbol_info);

	if(!result)
	{
		DWORD err = GetLastError();
		wchar_t buf[256];
#if defined(_WIN64)
		if(is64BitProcess)
			swprintf(buf, 256, L"[%016llX]", addr);
		else 
			swprintf(buf, 256, L"[%08X]", unsigned __int32(addr));
#else
		swprintf(buf, 256, L"[%08X]", addr);
#endif
		return buf;
	}