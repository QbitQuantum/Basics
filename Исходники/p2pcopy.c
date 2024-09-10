void cpyFromProcess(DWORD pid, void *dst, void *src, size_t size) {
	SIZE_T numBytesRead;
	HANDLE procHandle = OpenProcess(PROCESS_VM_READ, FALSE, pid);
	if (procHandle == NULL) {
		dbgPrint(DBGLVL_ERROR, "cpyFromProcess: could not open process %u\n", procHandle);
		exit(1);
	}
	if (ReadProcessMemory(procHandle, src, dst, size, &numBytesRead) == 0) {
		dbgPrint(DBGLVL_ERROR, "cpyFromProcess: copying failed: %u\n", GetLastError());
		CloseHandle(procHandle);
		exit(1);
	}
	if (numBytesRead != size) {
		dbgPrint(DBGLVL_ERROR, "cpyFromProcess: could copy only %u out of %u bytes.\n", numBytesRead, size);
		CloseHandle(procHandle);
		exit(1);
	}
	CloseHandle(procHandle);
}