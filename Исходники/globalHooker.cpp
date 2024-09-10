// Write hook
static bool writeHook(GHOOK *h) {
	if(h->active)
		return true; // Already hooked
	//dbg("Hooking %s/%s", h->dll, h->name);

	memset(h->stub, 0x90, STUBLEN+JMPDATALEN); // Fill stub function with NOP

	// Load library & get proc address
	HINSTANCE hLib = GetModuleHandle(h->dll);
	if(!hLib) {
		dbg("Module not loaded");
		return false;
	}

	//h->funcOrig = (ULONG_PTR*) GetProcAddress((HMODULE) hLib, h->name);
  h->funcOrig = (ULONG_PTR) GetProcAddress((HMODULE) hLib, h->name);
	if(!h->funcOrig) {
		dbg("Export not found in DLL!");
		return false;
	}

	// Walk instructions from beginning of function to find stub data size & stub jmp pos
	BYTE *sJmp = instructionCount((BYTE*) h->funcOrig, 5);
	DWORD slen = (DWORD) (sJmp - (BYTE*)h->funcOrig);// Stub length (without jmp)  
	h->stublen = slen;

	// Open handle to current process
	HANDLE hSelf = NULL; 
	hSelf = OpenProcess(PROCESS_VM_WRITE|PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
	if(!hSelf) {
		// Openprocess failed, attempt debug access
		HANDLE hToken;
		if(!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, FALSE, &hToken)) {
			ImpersonateSelf(SecurityImpersonation);
			OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, FALSE, &hToken);
		}
		if(!SetPrivilege(hToken, SE_DEBUG_NAME, TRUE)) {
			// Debug access failed, propably non-admin user
		 	dbg("writeHook: SetPrivilege failed - Check user permissions");
			return false; // This isn't going to work
		} else {
			// Hey, it worked! Try again...
			hSelf = OpenProcess(PROCESS_VM_WRITE|PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
			if(!hSelf) {
				dbg("OpenProcess failed");
				return false;
			}
		}
	}

	// Create stub code, copy data from function start & append jmp
	memcpy(h->stub, (void*)h->funcOrig, slen);
	writeJmpOpcode(hSelf, h->stub+slen, (void*) (h->funcOrig+slen));

	if(h->stub[0] == 0xE9) { // 0xE9 = jmp instruction
		// JMP at beginning of previous hook code, must change the offset or it will jump to wrong location
		// New correct position is: jump address + original function pointer - stub function pointer
		ULONG_PTR *jp = (ULONG_PTR*) (h->stub+1);
    ULONG_PTR newjp = *jp + ((BYTE*)h->funcOrig - (BYTE*)h->stub);
		dbg("Existing hook detected at %s/%s, redirecting JMP (0x%08X -> 0x%08X)", h->dll, h->name, *jp, newjp);

		*jp = newjp;
	}

	// Mark stub code executable
	DWORD oldprot = NULL;
	VirtualProtectEx(hSelf, h->stub, STUBLEN+JMPDATALEN, PAGE_EXECUTE_READWRITE, &oldprot);

	// Write jmp to beginning of original function
	writeJmpOpcode(hSelf, (void*)h->funcOrig, (void*) h->funcOver);

	CloseHandle(hSelf);
	//FreeLibrary(hLib);

  dbg("Hooked %s/%s", h->dll, h->name);

	h->active = true;
	return true;
}