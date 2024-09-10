bool ProtectMemoryPages(const void* ptr, size_t size, uint32_t memProtFlags) {
	VERBOSE_LOG(JIT, "ProtectMemoryPages: %p (%d) : r%d w%d x%d", ptr, (int)size,
			(memProtFlags & MEM_PROT_READ) != 0, (memProtFlags & MEM_PROT_WRITE) != 0, (memProtFlags & MEM_PROT_EXEC) != 0);

	if (PlatformIsWXExclusive()) {
		if ((memProtFlags & (MEM_PROT_WRITE | MEM_PROT_EXEC)) == (MEM_PROT_WRITE | MEM_PROT_EXEC)) {
			ERROR_LOG(MEMMAP, "Bad memory protection %d!", memProtFlags);
			PanicAlert("Bad memory protect : W^X is in effect, can't both write and exec");
		}
	}
	// Note - VirtualProtect will affect the full pages containing the requested range.
	// mprotect does not seem to, at least not on Android unless I made a mistake somewhere, so we manually round.
#ifdef _WIN32
	uint32_t protect = ConvertProtFlagsWin32(memProtFlags);

#if PPSSPP_PLATFORM(UWP)
	DWORD oldValue;
	if (!VirtualProtectFromApp((void *)ptr, size, protect, &oldValue)) {
		PanicAlert("WriteProtectMemory failed!\n%s", GetLastErrorMsg());
		return false;
	}
#else
	DWORD oldValue;
	if (!VirtualProtect((void *)ptr, size, protect, &oldValue)) {
		PanicAlert("WriteProtectMemory failed!\n%s", GetLastErrorMsg());
		return false;
	}
#endif
	return true;
#else
	uint32_t protect = ConvertProtFlagsUnix(memProtFlags);
	uintptr_t page_size = GetMemoryProtectPageSize();

	uintptr_t start = (uintptr_t)ptr;
	uintptr_t end = (uintptr_t)ptr + size;
	start &= ~(page_size - 1);
	end = (end + page_size - 1) & ~(page_size - 1);
	int retval = mprotect((void *)start, end - start, protect);
	if (retval != 0) {
		ERROR_LOG(MEMMAP, "mprotect failed (%p)! errno=%d (%s)", (void *)start, errno, strerror(errno));
		return false;
	}
	return true;
#endif
}