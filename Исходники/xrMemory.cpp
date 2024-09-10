void	xrMemory::mem_compact	()
{
	RegFlushKey						( HKEY_CLASSES_ROOT );
	RegFlushKey						( HKEY_CURRENT_USER );
	if (g_allow_heap_min)
		_heapmin					( );
	HeapCompact					(GetProcessHeap(),0);
	if (g_pStringContainer)			g_pStringContainer->clean		();
	if (g_pSharedMemoryContainer)	g_pSharedMemoryContainer->clean	();
	if (strstr(Core.Params,"-swap_on_compact"))
		SetProcessWorkingSetSize	(GetCurrentProcess(),size_t(-1),size_t(-1));
}