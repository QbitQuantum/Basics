static void OutputStackTrace(DWORD exceptionCode, const PVOID* addrOffsets)
{
	WCHAR path[MAX_PATH + 4];
	path[GetModuleFileName(NULL, path, MAX_PATH)] = L'\0';
	lstrcat(path, L".err");
	HANDLE hFile = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if( hFile != INVALID_HANDLE_VALUE ){
		char buff[384];
		DWORD written;
		int len = wsprintfA(buff, "ExceptionCode = 0x%08X\r\n", exceptionCode);
		WriteFile(hFile, buff, len, &written, NULL);
		for( int i = 0; addrOffsets[i]; i++ ){
			SYMBOL_INFO symbol[1 + (256 + sizeof(SYMBOL_INFO)) / sizeof(SYMBOL_INFO)];
			symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
			symbol->MaxNameLen = 256;
			DWORD64 displacement;
			if( SymFromAddr(GetCurrentProcess(), (DWORD64)addrOffsets[i], &displacement, symbol) ){
				len = wsprintfA(buff, "Trace%02d 0x%p = 0x%p(%s) + 0x%X\r\n", i, addrOffsets[i], (PVOID)symbol->Address, symbol->Name, (DWORD)displacement);
			}else{
				len = wsprintfA(buff, "Trace%02d 0x%p = ?\r\n", i, addrOffsets[i]);
			}
			WriteFile(hFile, buff, len, &written, NULL);
		}
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
		if( hSnapshot != INVALID_HANDLE_VALUE ){
			MODULEENTRY32W modent;
			modent.dwSize = sizeof(modent);
			if( Module32FirstW(hSnapshot, &modent) ){
				do{
					len = wsprintfA(buff, "0x%p - 0x%p = %S\r\n", modent.modBaseAddr, modent.modBaseAddr + modent.modBaseSize - 1, modent.szModule);
					WriteFile(hFile, buff, len, &written, NULL);
				}while( Module32NextW(hSnapshot, &modent) );
			}
			CloseHandle(hSnapshot);
		}
		CloseHandle(hFile);
	}
}