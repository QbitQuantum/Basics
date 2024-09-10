bool raise(unsigned long int pid) {
	bool ok = false;
    HANDLE inferior = NULL;
    do {
        const DWORD rights = PROCESS_QUERY_INFORMATION|PROCESS_SET_INFORMATION
                |PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ
                |PROCESS_DUP_HANDLE|PROCESS_TERMINATE|PROCESS_CREATE_THREAD|PROCESS_SUSPEND_RESUME ;
        inferior = OpenProcess(rights, FALSE, pid);
        if (inferior == NULL) {
            printf("Inferior is NULL\n");
            break;
        }
        if (!DebugBreakProcess(inferior)) {
			printf("DebugBreakProcess failed: %s\n", GetLastError());
            break;
        }
        ok = true;
    } while (false);
    if (inferior != NULL)
        CloseHandle(inferior);
    return ok;
}