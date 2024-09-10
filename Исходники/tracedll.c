static int dll_intercept(register void* addr)
{
	IMAGE_DOS_HEADER*	dosp = (IMAGE_DOS_HEADER*)addr;
	IMAGE_NT_HEADERS*	ntp;
	IMAGE_EXPORT_DIRECTORY*	exp;
	register int		i;
	register int		j;
	register int		base;
	DWORD*			names;
	WORD*			ordinals;
	DWORD*			functions;
	char*			name;
	void*			fun;

	if (IsBadReadPtr(addr, sizeof(*dosp)))
		return 0;
	if (dosp->e_magic != IMAGE_DOS_SIGNATURE)
		return 0;
	ntp = ptr(IMAGE_NT_HEADERS, dosp, dosp->e_lfanew);
	exp = ptr(IMAGE_EXPORT_DIRECTORY, addr, ntp->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	if ((void*)exp == (void*)ntp)
		return 1;
	base = exp->Base - 1;
	names = ptr(DWORD, addr, exp->AddressOfNames);
	ordinals = ptr(WORD, addr, exp->AddressOfNameOrdinals);
	functions = ptr(DWORD, addr, exp->AddressOfFunctions);
	for (i = j = 0; i < (int)exp->NumberOfNames; i++)
	{
		name = ptr(char, addr, names[i]);
		if (strcmp(name, sys_call[j].name) == 0)
		{
			fun = ptr(void, addr, functions[ordinals[i]-base]);
			sys_call[j].actual = (Syscall_f)fun;
			trace_error(-2, "%3d %3d %p %s", i, j, fun, name);
			if (++j >= elementsof(sys_call))
				return 1;
		}
	}