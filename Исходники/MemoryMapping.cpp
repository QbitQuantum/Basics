char* MemoryMapping::map(char* buffer, 
						 int buffersize, 
						 FILE* file, 
						 int offset) 
{
#ifdef _MSC_VER

	HANDLE filehandle = (HANDLE) _get_osfhandle(FILENO(file));

	HANDLE filemapping = ::CreateFileMappingA(
		filehandle, 
		&MMAP_SECURITY_ATTRIBUTES,
		PAGE_READONLY | SEC_COMMIT, 
		0, 
		0,
		0);

	if (0 == filemapping) return MAP_FAILED;

	DWORD alignedoffset = (offset / getPageSize()) * getPageSize();
	DWORD alignment = offset - alignedoffset;

	LPVOID mappedmemory = ::MapViewOfFile(
		filemapping,
		FILE_MAP_READ,
		0, 
		alignedoffset, 
		0);

	::CloseHandle(filemapping);

	if (0 != mappedmemory)
	{
		return ((char*) mappedmemory) + alignment;
	}
	else	
	{
		return 0;
	}

#else

	int filehandle = FILENO(file);

	int protection = PROT_READ;
	int flags = MAP_PRIVATE;

	int alignedoffset = (offset / getpagesize()) * getpagesize();
	int alignment = offset - alignedoffset;
	int alignedlength = ((buffersize / getpagesize()) + 1) * getpagesize();

	char* result = (char*) ::mmap(
		(void*) buffer, 
		alignedlength, 
		protection,
		flags, 
		filehandle, 
		alignedoffset);

	return ((char*) -1) == result ? 0 : result + alignment;

#endif
}