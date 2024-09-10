//********************************************************************
Handle MyReAlloc(Handle hMem,
				uint32_t dwSize,
				uint32_t dwFlag)
{
	return CFIO_ReAlloc?
		CFIO_ReAlloc(hMem, dwSize, dwFlag):
		GlobalReAlloc(hMem, dwSize, dwFlag);
}