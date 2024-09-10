bool MemoryMap_Setup(u32 flags) {
#if PPSSPP_PLATFORM(UWP)
	// We reserve the memory, then simply commit in TryBase.
	base = (u8*)VirtualAllocFromApp(0, 0x10000000, MEM_RESERVE, PAGE_READWRITE);
#else

	// Figure out how much memory we need to allocate in total.
	size_t total_mem = 0;
	for (int i = 0; i < num_views; i++) {
		if (views[i].size == 0)
			continue;
		SKIP(flags, views[i].flags);
		if (!CanIgnoreView(views[i]))
			total_mem += g_arena.roundup(views[i].size);
	}

	// Grab some pagefile backed memory out of the void ...
	g_arena.GrabLowMemSpace(total_mem);
#endif

#if !PPSSPP_PLATFORM(ANDROID)
	if (g_arena.NeedsProbing()) {
		int base_attempts = 0;
#if defined(_WIN32) && PPSSPP_ARCH(32BIT)
		// Try a whole range of possible bases. Return once we got a valid one.
		uintptr_t max_base_addr = 0x7FFF0000 - 0x10000000;
		uintptr_t min_base_addr = 0x01000000;
		uintptr_t stride = 0x400000;
#else
		// iOS
		uintptr_t max_base_addr = 0x1FFFF0000ULL - 0x80000000ULL;
		uintptr_t min_base_addr = 0x100000000ULL;
		uintptr_t stride = 0x800000;
#endif
		for (uintptr_t base_addr = min_base_addr; base_addr < max_base_addr; base_addr += stride) {
			base_attempts++;
			base = (u8 *)base_addr;
			if (Memory_TryBase(flags)) {
				INFO_LOG(MEMMAP, "Found valid memory base at %p after %i tries.", base, base_attempts);
				return true;
			}
		}
		ERROR_LOG(MEMMAP, "MemoryMap_Setup: Failed finding a memory base.");
		PanicAlert("MemoryMap_Setup: Failed finding a memory base.");
		return false;
	}
	else
#endif
	{
#if !PPSSPP_PLATFORM(UWP)
		base = g_arena.Find4GBBase();
#endif
	}

	// Should return true...
	return Memory_TryBase(flags);
}