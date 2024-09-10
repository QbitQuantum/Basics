BOOL WINAPI Win32_WTSFreeMemoryExA(WTS_TYPE_CLASS WTSTypeClass, PVOID pMemory, ULONG NumberOfEntries)
{
	return WTSFreeMemoryExW(WTSTypeClass, pMemory, NumberOfEntries);
}