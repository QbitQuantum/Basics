void freeFrame(MEM_LOC frame) {

	//If paging isn't enabled we are not going to be able to free a frame of virtual memory
	//and the stacks location is virtual (Cannot be accessed without paging)
	if (paging_enabled == 0) {
		return;
	}

	//Anything under used_mem_end is identity mapped (Physical Address == Virtual Address)
	//never remap it.
	if (frame < used_mem_end + PAGE_SIZE) {
		return;
	}

	if (getCurrentProcess() != 0) {
		usedListRemove(getCurrentProcess(), frame);
	}

	//Run out of stack space *Shock Horror* Allocate this frame to the end
	//of the stack (Giving another 4kb (4096 bytes) of stack space)
	if (phys_mm_smax <= phys_mm_slock) {
		map((POINTER) phys_mm_smax, (POINTER) frame, MEMORY_RESTRICTED_ACCESS);
		phys_mm_smax += PAGE_SIZE;
	} else {
		//Add the frame to the end of the frame stack
		MEM_LOC* stack = (MEM_LOC*) phys_mm_slock;
		*stack = frame;
		phys_mm_slock += sizeof(uint32_t);
	}
}