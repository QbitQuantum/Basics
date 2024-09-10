U NCodeHook<ArchT>::createHook(U originalFunc, U hookFunc) {
	// check if this function is already hooked
	std::map<uintptr_t, NCodeHookItem>::const_iterator cit = hookedFunctions_.begin();
	while(cit != hookedFunctions_.end()) {
		if ((uintptr_t)cit->second.OriginalFunc == (uintptr_t)originalFunc) return (U)cit->second.Trampoline;
		++cit;
	}

	bool useAbsJump = forceAbsJmp_;
	int offset = 0;
	if (useAbsJump || architecture_.requiresAbsJump((uintptr_t)originalFunc, (uintptr_t)hookFunc)) {
		offset = getMinOffset((const unsigned char*)originalFunc, ArchT::AbsJumpPatchSize);
		useAbsJump = true;
	}		
	else offset = getMinOffset((const unsigned char*)originalFunc, ArchT::NearJumpPatchSize);
	if (offset == -1) return false;

	DWORD oldProtect = 0;
	BOOL retVal = VirtualProtect((LPVOID)originalFunc, ArchT::MaxTrampolineSize, PAGE_EXECUTE_READWRITE, &oldProtect);
	if (!retVal) return false;

	// Get trampoline memory and copy instructions to trampoline.
	uintptr_t trampolineAddr = getFreeTrampoline();
	memcpy((void*)trampolineAddr, (void*)originalFunc, offset);
	if (useAbsJump)	{
		architecture_.writeAbsJump((uintptr_t)originalFunc, (uintptr_t)hookFunc);
		architecture_.writeAbsJump(trampolineAddr + offset, (uintptr_t)originalFunc + offset);
	}
	else {
		architecture_.writeNearJump((uintptr_t)originalFunc, (uintptr_t)hookFunc);
		architecture_.writeNearJump(trampolineAddr + offset, (uintptr_t)originalFunc + offset);
	}

	DWORD dummy;
	VirtualProtect((LPVOID)originalFunc, ArchT::MaxTrampolineSize, oldProtect, &dummy);

	FlushInstructionCache(GetCurrentProcess(), (LPCVOID)trampolineAddr, MaxTotalTrampolineSize);
	FlushInstructionCache(GetCurrentProcess(), (LPCVOID)originalFunc, useAbsJump ? ArchT::AbsJumpPatchSize : ArchT::NearJumpPatchSize);
	
	NCodeHookItem item((uintptr_t)originalFunc, (uintptr_t)hookFunc, trampolineAddr, offset);
	hookedFunctions_.insert(std::make_pair((uintptr_t)hookFunc, item));

	return (U)trampolineAddr;
}