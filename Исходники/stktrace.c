BOOLEAN
MspAcquireContext(
	IN PMSP_STACKTRACE_OBJECT Object,
	IN ULONG ProcessId
	)
{
	PMSP_STACKTRACE_CONTEXT Old;
	PMSP_STACKTRACE_CONTEXT New;
	WCHAR SymbolPath[MAX_PATH * 2];

	Old = Object->Context;
	if (Old != NULL) {
		if (Old->ProcessId == ProcessId) {
			return TRUE;
		}
		else {
			SymCleanup(Old->ProcessHandle);
		}
	}
	
	New = MspLookupStackTraceContext(Object, ProcessId, TRUE);
	if (!New) {
		__debugbreak();
		return FALSE;
	}
	
	ASSERT(New->ProcessHandle != NULL);

	MdbGetSymbolPath(SymbolPath, MAX_PATH * 2);
	SymInitializeW(New->ProcessHandle, SymbolPath, TRUE);
	SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | 
		          SYMOPT_INCLUDE_32BIT_MODULES | SYMOPT_LOAD_LINES | 
				  SYMOPT_OMAP_FIND_NEAREST);

	Object->Context = New;
	return TRUE;
}