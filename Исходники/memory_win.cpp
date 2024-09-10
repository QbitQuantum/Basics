	bool EnableLowFragmentationHeap() {
		HMODULE kernel32 = GetModuleHandle(L"kernel32.dll");
		HeapSetFn heap_set = reinterpret_cast<HeapSetFn>(GetProcAddress(
			kernel32,
			"HeapSetInformation"));

		// On Windows 2000, the function is not exported. This is not a reason to
		// fail.
		if (!heap_set)
			return true;

		unsigned number_heaps = GetProcessHeaps(0, NULL);
		if (!number_heaps)
			return false;

		// Gives us some extra space in the array in case a thread is creating heaps
		// at the same time we're querying them.
		static const int MARGIN = 8;
		scoped_ptr<HANDLE[]> heaps(new HANDLE[number_heaps + MARGIN]);
		number_heaps = GetProcessHeaps(number_heaps + MARGIN, heaps.get());
		if (!number_heaps)
			return false;

		for (unsigned i = 0; i < number_heaps; ++i) {
			ULONG lfh_flag = 2;
			// Don't bother with the result code. It may fails on heaps that have the
			// HEAP_NO_SERIALIZE flag. This is expected and not a problem at all.
			heap_set(heaps[i],
				HeapCompatibilityInformation,
				&lfh_flag,
				sizeof(lfh_flag));
		}
		return true;
	}