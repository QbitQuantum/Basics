void dm_HeapCompact()
{
	HANDLE hHeap;

	if(hHeap = GetProcessHeap())
	{
		HeapCompact(hHeap, 0);
	}
}