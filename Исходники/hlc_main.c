static uchar *hlc_resolve_symbol( void *addr, uchar *out, int *outSize ) {
#ifdef _WIN32
	static HANDLE stack_process_handle = NULL;
	DWORD64 index;
	IMAGEHLP_LINEW64 line;
	struct {
		SYMBOL_INFOW sym;
		uchar buffer[256];
	} data;
	data.sym.SizeOfStruct = sizeof(data.sym);
	data.sym.MaxNameLen = 255;
	if( !stack_process_handle ) {
		stack_process_handle = GetCurrentProcess();
		SymSetOptions(SYMOPT_LOAD_LINES);
		SymInitialize(stack_process_handle,NULL,TRUE);
	}
	if( SymFromAddrW(stack_process_handle,(DWORD64)(int_val)addr,&index,&data.sym) ) {
		DWORD offset = 0;
		line.SizeOfStruct = sizeof(line);
		line.FileName = USTR("\\?");
		line.LineNumber = 0;
		SymGetLineFromAddrW64(stack_process_handle, (DWORD64)(int_val)addr, &offset, &line);
		*outSize = usprintf(out,*outSize,USTR("%s(%s:%d)"),data.sym.Name,wcsrchr(line.FileName,'\\')+1,(int)line.LineNumber);
		return out;
	}
#endif
	return NULL;
}