void *
LocalReAllocPtr(void * ptr, UINT flags, UINT size)
{
HLOCAL hlocal;
	hlocal = LocalHandle(ptr);
	LocalUnlock(hlocal);
	hlocal = LocalReAlloc(hlocal, size+1, flags);
	return (char *)LocalLock(hlocal);
}