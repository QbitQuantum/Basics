/*
 * Creates memory close to the target function, used to force the actual hook
 * to use a 32bit jump instead of a 64bit jump, thus preventing the chance of
 * overwriting adjacent functions, which can cause a crash.  (by R1CH)
 */
static void setup_64bit_bounce(struct func_hook *hook, intptr_t *offset)
{
	MEMORY_BASIC_INFORMATION mbi;
	uintptr_t address;
	uintptr_t newdiff;
	SYSTEM_INFO si;
	bool success;
	int pagesize;
	int i;

	success = VirtualQueryEx(GetCurrentProcess(),
			(const void*)hook->func_addr, &mbi, sizeof(mbi));
	if (!success)
		return;

	GetSystemInfo(&si);
	pagesize = (int)si.dwAllocationGranularity;

	address = (uintptr_t)mbi.AllocationBase - pagesize;
	for (i = 0; i < 256; i++, address -= pagesize) {
		hook->bounce_addr = VirtualAlloc((LPVOID)address, pagesize,
				MEM_RESERVE | MEM_COMMIT,
				PAGE_EXECUTE_READWRITE);
		if (hook->bounce_addr)
			break;
	}

	if (!hook->bounce_addr) {
		address = (uintptr_t)mbi.AllocationBase + mbi.RegionSize +
			pagesize;
		for (i = 0; i < 256; i++, address += pagesize) {
			hook->bounce_addr = VirtualAlloc((LPVOID)address,
					pagesize, MEM_RESERVE | MEM_COMMIT,
					PAGE_EXECUTE_READWRITE);
			if (hook->bounce_addr)
				break;
		}
	}

	if (!hook->bounce_addr)
		return;

	if ((hook->func_addr + 5) > (uintptr_t)hook->bounce_addr)
		newdiff = hook->func_addr + 5 - (uintptr_t)hook->bounce_addr;
	else
		newdiff = (uintptr_t)hook->bounce_addr - hook->func_addr + 5;

	if (newdiff <= 0x7ffffff0) {
		uint8_t *addr = (uint8_t*)hook->bounce_addr;

		FillMemory(hook->bounce_addr, pagesize, 0xCC);

		*(addr++) = 0xFF;
		*(addr++) = 0x25;
		*((uint32_t*)addr) = 0;
		*((uint64_t*)(addr + 4)) = hook->hook_addr;

		hook->hook_addr = (uint64_t)hook->bounce_addr;
		*offset = hook->hook_addr - hook->func_addr - JMP_32_SIZE;
		hook->is_64bit_jump = false;
	}
}