int munlock(const void *addr, size_t len)
{
    if (VirtualUnlock((LPVOID)addr, len)) 
		return 0;
	else
	{
		errno =  windowsErrorToErrno(GetLastError());
		return -1;
	}
}