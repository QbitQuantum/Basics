PVOID JMPHook::hook(PVOID tgt, PVOID rep){
	this->target = tgt;
	this->replacer = rep;
	PVOID orig_fn = tgt;
	PVOID dest_fn = rep;
	
	
	newregion = (byte*) VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(newregion, orig_fn, size);
	int p = memcmp(newregion, orig_fn, size);
	//printf("%d\n", p);

	
	unsigned long oldprotect = 0;
	VirtualProtect(orig_fn, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	__asm{
		mov eax, dword ptr [orig_fn];	//	eax = orig_fn address
		mov ecx, 0xe9;	// ecx = jmp relative
		mov [eax], ecx; // *orig_fn = jmp relative
		mov ecx, dword ptr [dest_fn];	// ecx = dest_fn address
		sub ecx, dword ptr [orig_fn];	// ecx = address(dest_fn) - address(orig_fn)
		sub ecx, 5;
		inc eax;	// eax = orig_fn address + 1
		mov dword ptr [eax], ecx;	// *orig_fn = jmp relative to [dest_fn]
	}
	VirtualProtect(orig_fn, size, oldprotect, &oldprotect);
	VirtualProtect(newregion, size, PAGE_EXECUTE_READ, 0);
	
	FlushInstructionCache(0, orig_fn, size);
	FlushInstructionCache(0, newregion, size);
	
	return (PVOID) newregion;	// address of the copied function

}