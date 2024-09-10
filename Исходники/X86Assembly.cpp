CompiledProgram::CompiledProgram(Program in_program)
{
	mProgSize=0;

	for (Program::iterator i=in_program.begin(); i!=in_program.end(); i++)
	{
		mProgSize+=i->size();
	}

	mpProg=VirtualAlloc(
		NULL,
		mProgSize,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE
		);

	if (mpProg == NULL )
		exit(0);

	size_t progPos=0;

	for (Program::iterator i=in_program.begin(); i!=in_program.end(); i++)
	{
		memcpy((unsigned char*) mpProg+progPos, &(*i)[0], i->size());
		progPos+=i->size();
	}

	DWORD flOldProtect;

	if (!VirtualProtect(mpProg, size(), PAGE_EXECUTE, &flOldProtect))
		exit(0);

	if (!FlushInstructionCache(GetCurrentProcess(), mpProg, size()))
		exit(0);
}