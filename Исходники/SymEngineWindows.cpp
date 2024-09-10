const Symbol * const SymEngine::GetSymbol(DWORD64 dwAddress)
{
	if (dwAddress == 0)
		return nullptr;

	Symbol& symbol = cache[dwAddress];

	if (symbol.address != 0)
		return &symbol;

	if (!isInitialized)
		return nullptr;

	symbol.address = dwAddress;

	// Module Name
	IMAGEHLP_MODULEW64 moduleInfo;
	memset(&moduleInfo, 0, sizeof(IMAGEHLP_MODULEW64));
	moduleInfo.SizeOfStruct = sizeof(moduleInfo);
	if (SymGetModuleInfoW64(hProcess, dwAddress, &moduleInfo))
	{
		symbol.module = moduleInfo.ImageName;
	}


	// FileName and Line
	IMAGEHLP_LINEW64 lineInfo;
	memset(&lineInfo, 0, sizeof(IMAGEHLP_LINEW64));
	lineInfo.SizeOfStruct = sizeof(lineInfo);
	DWORD dwDisp;
	if (SymGetLineFromAddrW64(hProcess, dwAddress, &dwDisp, &lineInfo))
	{
		symbol.file = lineInfo.FileName;
		symbol.line = lineInfo.LineNumber;
	}

	const size_t length = (sizeof(SYMBOL_INFOW) + MAX_SYM_NAME*sizeof(WCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64) + 1;

	// Function Name
	ULONG64 buffer[length];
	PSYMBOL_INFOW dbgSymbol = (PSYMBOL_INFOW)buffer;
	memset(dbgSymbol, 0, sizeof(buffer));
	dbgSymbol->SizeOfStruct = sizeof(SYMBOL_INFOW);
	dbgSymbol->MaxNameLen = MAX_SYM_NAME;
	if (SymFromAddrW(hProcess, dwAddress, &symbol.offset, dbgSymbol))
	{
		symbol.function.resize(dbgSymbol->NameLen);
		memcpy(&symbol.function[0], &dbgSymbol->Name[0], sizeof(WCHAR) * dbgSymbol->NameLen);
	}

	return &symbol;
}