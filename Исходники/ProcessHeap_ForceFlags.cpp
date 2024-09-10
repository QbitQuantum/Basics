PUINT32 GetForceFlags_x64()
{
	PINT64 pProcessHeap = NULL;
	PUINT32 pHeapForceFlags = NULL;
	if (IsWindowsVistaOrGreater()){
		pProcessHeap = (PINT64)(__readgsqword(0x60) + 0x30);
		pHeapForceFlags = (PUINT32)(*pProcessHeap + 0x74);
	}

	else {
		pProcessHeap = (PINT64)(__readgsqword(0x60) + 0x30);
		pHeapForceFlags = (PUINT32)(*pProcessHeap + 0x18);
	}

	return pHeapForceFlags;
}