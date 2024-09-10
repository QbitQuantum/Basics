/**
 * @brief
 *		Perform the given operation <op> on process tree by using given parent process id <process_ID>
 *
 * @param[in]
 *		process_ID - parent process id on which <op> will performed
 *		op		 - operation to perform, one of SUSPEND, RESUME or TERMINATE
 *		exitcode - exit code for processes, this is used only if <op> = TERMINATE, otherwise 0
 *
 * @return
 *		int
 *
 * @retval
 *		>= 0 - No. of processes that were operated on
 *		-1   - Invalid parameter or Error
 *
 */
int
processtree_op_by_id(DWORD processId, enum operation op, int exitcode)
{
	HANDLE hProcessSnap = INVALID_HANDLE_VALUE;
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	HANDLE hThread = INVALID_HANDLE_VALUE;
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32 = { sizeof(te32) };
	PROCESSENTRY32 pe32 = { sizeof(pe32) };
	int process_count = 0;
	int ret = -1;

	if (processId <= 0)
		return -1;

	if (op >= UNKNOWN)
		return -1;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, processId);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return -1;

	if (!Process32First(hProcessSnap, &pe32)) {
		CloseHandle(hProcessSnap);
		return -1;
	}

	do {
		if (processId == pe32.th32ParentProcessID) {
			ret = processtree_op_by_id(pe32.th32ProcessID, op, exitcode);
			if (ret != -1) {
				process_count += ret;
			} else {
				CloseHandle(hProcessSnap);
				return -1;
			}
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);

	/*
	 * if op == TERMINATE then terminate process at process level instead
	 * of thread level because TerminateThread call is not safe as per MSDN
	 *
	 * if op = SUSPEND or RESUME then suspend or resume process at thread level
	 * by using SuspendThread or ResumeThread
	 */
	if (op == TERMINATE) {
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processId);
		/*
		 * OpenProcess() may return a handle to next lower process Id
		 * if given process id doesn't exist. It will be disastorous
		 * if we kill this arbitrary process, thus always make sure that the handle returned
		 * belongs to intended process id by calling GetProcessId() on returned handle.
		 */
		if ((hProcess != NULL) && (hProcess != INVALID_HANDLE_VALUE) &&(GetProcessId(hProcess) == processId)) {
			ret = TerminateProcess(hProcess, exitcode);
			CloseHandle(hProcess);
			if (ret) {
				return (++process_count);
			} else {
				return -1;
			}
		} else {
			return -1;
		}
	}

	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processId);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return -1;

	if (!Thread32First(hThreadSnap, &te32)) {
		CloseHandle(hThreadSnap);
		return -1;
	}

	do {
		if (te32.th32OwnerProcessID == processId) {
			hThread = OpenThread(THREAD_SUSPEND_RESUME, TRUE, te32.th32ThreadID);
			if ((hThread != NULL) && (hThread != INVALID_HANDLE_VALUE)) {
				if (op == SUSPEND) { /* Suspend Thread */
					ret = SuspendThread(hThread);
				} else if (op == RESUME) { /* Resume Thread */
					ret = ResumeThread(hThread);
				}
				CloseHandle(hThread);
				if (ret == -1) {
					CloseHandle(hThreadSnap);
					return -1;
				}
			} else {
				CloseHandle(hThreadSnap);
				return -1;
			}
		}
	} while (Thread32Next(hThreadSnap, &te32));

	CloseHandle(hThreadSnap);

	process_count++;
	return process_count;
}