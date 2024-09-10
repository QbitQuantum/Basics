void ADM_backTrack(const char *info,int lineno,const char *file)
{	
	fflush(stderr);
	fflush(stdout);

	if (mysaveFunction)
		mysaveFunction();

	if (myFatalFunction)
		myFatalFunction("Crash", "Press OK to build crash info");

	void* currentProcessId = GetCurrentProcess();

	SymInitialize(currentProcessId, NULL, TRUE);
	dumpBackTrace(currentProcessId);
	SymCleanup(currentProcessId);

	printf("Assert failed at file %s, line %d\n\n",file,lineno);

	exit(-1);
}