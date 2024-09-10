void FF13Plugin::initialize(unsigned rw, unsigned rh, D3DFORMAT bbformat, D3DFORMAT dssformat) {
	GenericPlugin::initialize(rw, rh, bbformat, dssformat);

	// Force low fragmentation heap
	HANDLE heaps[128];
	DWORD numHeaps = GetProcessHeaps(128, heaps);
	for(DWORD i = 0; i < numHeaps; ++i) {
		ULONG HeapInformation = HEAP_LFH;
		BOOL res = HeapSetInformation(heaps[i],	HeapCompatibilityInformation, &HeapInformation, sizeof(HeapInformation));
		if(res != FALSE) {
			SDLOG(1, "Low-fragmentation heap enabled for heap #%d.\n", i);
		} else {
			SDLOG(1, "Failed to enable low-fragmentation for heap #%d; LastError %d.\n", i, GetLastError());
		}
	}
}