void MemFreeReal( PTR ptr, const STR8 pcFile, INT32 iLine )
{
	UINT32 uiSize;

	if ( !fMemManagerInit )
	DbgMessage( TOPIC_MEMORY_MANAGER, DBG_LEVEL_0, String("MemFree: Warning -- Memory manager not initialized -- Line %d in %s", iLine, pcFile) );

	if (ptr != NULL)
	{
		uiSize = _msize(ptr);
		guiMemTotal -= uiSize;
		guiMemFreed += uiSize;
		_free_dbg( ptr, _NORMAL_BLOCK );

#ifdef DEBUG_MEM_LEAKS
	DbgMessage( TOPIC_MEMORY_MANAGER, DBG_LEVEL_1, String("MemFree	%p: %d bytes (line %d file %s)", ptr, uiSize, iLine, pcFile) );
#endif
	}
	else
	{
	DbgMessage( TOPIC_MEMORY_MANAGER, DBG_LEVEL_0, String("MemFree ERROR: NULL ptr received (line %d file %s)", iLine, pcFile) );
	}

	// count even a NULL ptr as a MemFree, not because it's really a memory leak, but because it is still an error of some
	// sort (nobody should ever be freeing NULL pointers), and this will help in tracking it down if the above DbgMessage
	// is not noticed.
	MemDebugCounter--;
}