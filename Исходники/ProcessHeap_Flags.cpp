PUINT32 GetHeapFlags_x86()
{
	PUINT32 pProcessHeap, pHeapFlags = NULL;

	if (IsWindowsVistaOrGreater()){
		pProcessHeap = (PUINT32)(__readfsdword(0x30) + 0x18);
		pHeapFlags = (PUINT32)(*pProcessHeap + 0x40);
	}

	else {
		pProcessHeap = (PUINT32)(__readfsdword(0x30) + 0x18);
		pHeapFlags = (PUINT32)(*pProcessHeap + 0x0C);
	}

	return pHeapFlags;
}