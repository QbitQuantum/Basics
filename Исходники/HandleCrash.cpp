void dumpBacktrace(int dumpFile, CrashData crash)
{
#ifdef Q_OS_UNIX
	// Variables for storing crash info.
	void* trace[BT_SIZE]; 	// Backtrace frames
	size_t size; 			// The backtrace size

	// Get the backtrace.
	size = backtrace(trace, BT_SIZE);

	// Dump the backtrace
	dprintf(dumpFile, "---- BEGIN BACKTRACE ----\n");
	backtrace_symbols_fd(trace, size, dumpFile);
	dprintf(dumpFile, "---- END BACKTRACE ----\n");
#elif defined Q_OS_WIN32
	dprintf(dumpFile, "---- BEGIN BACKTRACE ----\n");

	StackFrame stack[BT_SIZE];
	size_t size;

	SYMBOL_INFO *symbol;
	HANDLE process;

	size = getBacktrace(stack, BT_SIZE, *crash.context);

	// FIXME: Accessing heap memory is supposedly "dangerous",
	// but I can't find another way of doing this.

	// Initialize
	process = GetCurrentProcess();
	if (!SymInitialize(process, NULL, true))
	{
		dprintf(dumpFile, "Failed to initialize symbol handler. Can't print stack trace.\n");
		dprintf(dumpFile, "Here's a list of addresses in the call stack instead:\n");
		for(int i = 0; i < size; i++)
		{
			dprintf(dumpFile, "0x%0X\n", (DWORD64)stack[i].address);
		}
	} else {
		// Allocate memory... ._.
		symbol = (SYMBOL_INFO *) calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
		symbol->MaxNameLen = 255;
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

		// Dump stacktrace
		for(int i = 0; i < size; i++)
		{
			DWORD64 addr = (DWORD64)stack[i].address;
			if (!SymFromAddr(process, (DWORD64)(addr), 0, symbol))
				dprintf(dumpFile, "?? - 0x%0X\n", addr);
			else
				dprintf(dumpFile, "%s - 0x%0X\n", symbol->Name, symbol->Address);
		}

		free(symbol);
	}

	dprintf(dumpFile, "---- END BACKTRACE ----\n");
#endif
}