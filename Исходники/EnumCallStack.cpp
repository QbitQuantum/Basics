__inline void PrintStackFrame(DebugHelper& dbghelp, STACKFRAME64& frame, int nStackFrame, PRINTSTACKFRAMECALLBACK pfn, LPVOID lpData)
{   
	if (frame.AddrPC.Offset == 0)
		return;	
	const int maxNameLen = 512;
	IMAGEHLP_SYMBOL64* symbol = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64) + maxNameLen);
	ZeroMemory(symbol, sizeof(IMAGEHLP_SYMBOL64) + maxNameLen);
	symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
	symbol->MaxNameLength = maxNameLen;

	IMAGEHLP_LINE64 line;//No UNICODE version found for the Structure or Function
	ZeroMemory(&line, sizeof(line));
	line.SizeOfStruct = sizeof(line);
	DWORD displacement = 0;
	
	DWORD64 offset = 0;
   bool result = (FALSE != dbghelp.SymGetSymFromAddr64(frame.AddrPC.Offset, &offset, symbol ));
	if (result)	
	{
      USES_CONVERSION;
      const TCHAR* lpszSymbolName = Workshare::Conversions::A22T(symbol->Name).c_str();
		const TCHAR* lpszFileName = 0;
		int nLineNumber = 0;
		if (dbghelp.SymGetLineFromAddr64(frame.AddrPC.Offset, &displacement, &line))		
		{

			lpszFileName = Workshare::Conversions::A22T(line.FileName).c_str();
			nLineNumber = line.LineNumber;
		}		
		pfn(lpszSymbolName, lpszFileName, nLineNumber, nStackFrame, lpData);
	}
	free(symbol);   
}