void Func5() 
{ 
	void *stack[1024];
	unsigned short frames;
	SYMBOL_INFO  * symbol;
	HANDLE         process;

	process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	frames = CaptureStackBackTrace(0, 100, stack, NULL);
	symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	std::string result;
	char tempStr[255];

	for (int i = 0; i < frames; i++)
	{
		SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);

		sprintf(tempStr, "%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address);
		result += tempStr;
	}

	free(symbol);
	std::cout << result << std::endl;
}