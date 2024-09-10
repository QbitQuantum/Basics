int CreateGeneralBridge(void **BridgePointer, void *fn, unsigned char *fill, int fill_len, int alignment, int create_stackframe)
{
	HANDLE ProcessHeap;
	unsigned long OldProtection;
	unsigned char unused[5];
	int offset;
	unsigned char *c_bridge;
	int size_desired;
	int i;

	size_desired = 5;
	if(create_stackframe) {
		size_desired += 5;
	}
	if(fill != NULL) {
		size_desired += 5;
	}


	// Create the bridge
	ProcessHeap = GetProcessHeap();
	if (!ProcessHeap)
		return 0;

	*BridgePointer = HeapAlloc(ProcessHeap, HEAP_ZERO_MEMORY, size_desired);
	if (!*BridgePointer)
		return 0;

	// Make it executable
	if (!VirtualProtect(*BridgePointer, size_desired, PAGE_EXECUTE_READWRITE, &OldProtection)) {
		return 0;
	}
	
	offset = 0;

	// Restore the stackframe code
	if(create_stackframe && CREATE_FRAME_FIRST) {
		if (!CreateStackFrame(*BridgePointer, (alignment == WINDOWS_LIBRARY) )) {
			return 0;
		}
		offset += 5;
	}

	c_bridge = (unsigned char *)*BridgePointer;
	if(fill != NULL && alignment != WINDOWS_LIBRARY) {
		for(i=0; i < fill_len;i++) {
			c_bridge[offset+i] = fill[i];
		}
		offset += fill_len;
	}

	if(create_stackframe && !CREATE_FRAME_FIRST) {
		if (!CreateStackFrame(&(c_bridge[offset]), (alignment == WINDOWS_LIBRARY))) {
			return 0;
		}
		offset += 5;
	}

	if(alignment == WINDOWS_LIBRARY) {
		if (!make_jmp(  &(c_bridge[offset]) , ((unsigned char *) fn) + 5, unused, 5)) {
			return 0;
		}
	} 
	else {
	
		if (!make_jmp(  &(c_bridge[offset]) , ((unsigned char *) fn)  + alignment + 5, unused, 5)) {
			return 0;
		}
	}

	return 1;
}