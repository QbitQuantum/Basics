void WritePattern(LPVOID address, const signed short *data, SIZE_T size, MemorySegment *mem)
{
	DWORD oldProtect;

	// Allowing reading from and writing to this memory space.
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);

	// Backup memory.
	if(mem != NULL) {
		mem->address = address;
		mem->size = size;
		mem->data = (unsigned char*)malloc(size * sizeof(unsigned char));
		memcpy(mem->data, address, size);
	}

	unsigned char *a, *end = (unsigned char*)address + size;
	for(a = (unsigned char*)address; a < end; ++a, ++data) {
		// Ignore -1s.
		if(*data != -1) *a = (unsigned char)*data;
	}

	// Restore permissions to this memory space.
	VirtualProtect(address, size, oldProtect, &oldProtect);
	FlushInstructionCache(GetCurrentProcess(), address, size);
}