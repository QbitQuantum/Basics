HeapProfiler::HeapProfiler() 
{
	char fileName[MAX_PATH];
	wchar_t processName[MAX_PATH];
	wchar_t baseName[MAX_PATH];
	GetModuleFileName(NULL, processName, sizeof(processName));
	_wsplitpath(processName, NULL, NULL, baseName, NULL);
	sprintf(fileName, "winheaptrack.%S.%d", baseName, GetCurrentProcessId());
	printf("Saving data to %s...\n", fileName);
	data.output = fopen(fileName, "w+b");
	fprintf(data.output, "X %s\n", processName);
}