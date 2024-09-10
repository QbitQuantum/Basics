void InitSymbols(void)
{
	if (!symbolsinit)
	{
		DWORD dwOptions = SymGetOptions();

		SymSetOptions(dwOptions | SYMOPT_LOAD_LINES);

		BOOL blah = SymInitialize(GetCurrentProcess(), NULL, TRUE);
		assert(blah);

		symbolsinit = true;
	}
}