char *GetProgramName(char *programName, int size)
{
	char name[512];
	GetModuleFileName(GetModuleHandle(NULL), name, sizeof(name));
	char *p = strrchr(name, '\\');
	if (p)
	{
		STRNCPY(programName, p + 1, size);
	}
	else{
		STRNCPY(programName, name, size);
	}

	return programName;
}