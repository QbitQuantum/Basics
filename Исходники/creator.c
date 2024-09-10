static void blender_crash_handler_backtrace(FILE *fp)
{
	(void)fp;

#if 0
#define MAXSYMBOL 256
	unsigned short	i;
	void *stack[SIZE];
	unsigned short nframes;
	SYMBOL_INFO	*symbolinfo;
	HANDLE process;

	process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	nframes = CaptureStackBackTrace(0, SIZE, stack, NULL);
	symbolinfo = MEM_callocN(sizeof(SYMBOL_INFO) + MAXSYMBOL * sizeof( char ), "crash Symbol table");
	symbolinfo->MaxNameLen = MAXSYMBOL - 1;
	symbolinfo->SizeOfStruct = sizeof(SYMBOL_INFO);

	for (i = 0; i < nframes; i++) {
		SymFromAddr(process, ( DWORD64 )( stack[ i ] ), 0, symbolinfo);

		fprintf(fp, "%u: %s - 0x%0X\n", nframes - i - 1, symbolinfo->Name, symbolinfo->Address);
	}

	MEM_freeN(symbolinfo);
#endif
}