//---------------------------------------------------------------------------
// KillProcessTreeWinHelper
//
//  Terminates all the processes started by the specified process and then
//  terminates the process itself. When determining which processes were
//  started by the specified process, the following criteria are taken into
//  consideration:
//  - The PPID of the process
//  - The creation time of the process
//
//  Because Windows processes do not reparent (changing their PPID when their
//  real parent process terminates before they do), the PPID of a process is
//  not enough to safely kill a hierarchy. PID reuse can result in a process
//  appearing to be the parent of processes it didn't actually start. To try
//  and guard against this, the creation time (start time) for the process to
//  terminate is compared to the creation time of any process that appears to
//  be in its hierarchy. If the creation time of the child is before that of
//  its parent, it is assumed that the parent "inherited" the child and did
//  not actually start it. Such "inherited" children are not killed.
//
//  Parameters:
//	  dwProcessId - identifier of the process to terminate
//
//  Returns:
//	  Win32 error code.
//
DWORD WINAPI KillProcessTreeWinHelper(DWORD dwProcessId) {
	// first, open a handle to the process with sufficient access to query for
	// its times. those are needed in order to filter "children" because Windows
	// processes, unlike Unix/Linux processes, do not reparent when the process
	// that created them exits. as a result, any process could reuse a PID and
	// end up looking like it spawned many processes it didn't actually spawn
	auto_handle hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
	if (!hProcess) {
		return GetLastError();
	}

	// note: processCreated will be retained as the creation time for the root
	// process. the other variables only exist because GetProcessTimes requires
	// all 4 pointers
	FILETIME processCreated;
	FILETIME exitTime;   // unused
	FILETIME kernelTime; // unused
	FILETIME userTime;   // unused
	if (!GetProcessTimes(hProcess, &processCreated, &exitTime, &kernelTime, &userTime)) {
		// if unable to check the creation time for the process, it is impossible
		// to safely kill any children processes; just kill the root process and
		// leave it at that
		return KillProcess(dwProcessId);
	}

	// next, create a snapshot of all the running processes. this will be used
	// build a graph of processes which:
	// 1. have a parent related to the root process
	// 2. were started after the root process
	auto_handle hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hSnapshot) {
		// if unable to open a snapshot of the currently-running processes, just
		// kill the root process and leave it at that
		return KillProcess(dwProcessId);
	}

	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hHeap = GetProcessHeap();
	if (!hHeap) {
		return KillProcess(dwProcessId);
	}

	PTREE_PROCESS root = (PTREE_PROCESS) HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(TREE_PROCESS));
	if (!root) {
		// couldn't allocate memory for the TREE_PROCESS, which means we won't be able
		// to build the list; just kill the root process and leave it at that
		return KillProcess(dwProcessId);
	}
	root->processId = dwProcessId;

	PTREE_PROCESS current = root;
	PTREE_PROCESS last = root;

	FILETIME creationTime; // used when getting a child's creation time
	DWORD processId;       // holds the ID of the process being processed
	while (current) {
		// extract the process ID for processing, but do not move the current pointer;
		// since children have not been processed yet, current->next may not have been
		// set at this time. move it after the loop instead
		processId = current->processId;

		if (!Process32First(hSnapshot, &pEntry)) {
			return FreeProcessList(hHeap, root);
		}

		// find the children for the current process
		do {
			DWORD pid = pEntry.th32ProcessID;
			DWORD ppid = pEntry.th32ParentProcessID;

			// first checks are the simplest; we can perform them with the data from
			// the PROCESSENTRY32 structure:
			// 1. does the process have a parent?
			// 2. is the process the one we're currently checking?
			// 3. does the process's parent match the one we're checking?
			if (ppid == 0 || processId == pid || ppid != processId) {
				// if any of the checks "fail", then this process is not a candidate
				// for being killed
				continue;
			}

			// next check: was this process, which supposedly is in our hierarchy,
			// created before our process was? to find this out, we must open the
			// process and check its creation time. if we cannot open the process,
			// or we cannot get its process times, or its creation time is before
			// its supposed parent, it is not a candidate for being killed
			auto_handle hChild = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
			if (hChild &&
					GetProcessTimes(hChild, &creationTime, &exitTime, &kernelTime, &userTime) &&
					CompareFileTime(&processCreated, &creationTime) < 1) {
				// if we make it here, it means we were able to open the process,
				// get its process times and its creation time is at or after the
				// root process, so this process should be killed too
				PTREE_PROCESS child = (PTREE_PROCESS) HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(TREE_PROCESS));
				if (!child) {
					return FreeProcessList(hHeap, root);
				}
				child->previous = last;
				child->processId = pid;

				last->next = child;
				last = child;
			}
		}
		while (Process32Next(hSnapshot, &pEntry));

		// after processing all potential children for the current process, move the
		// pointer forward and process children for the next process in the list
		current = current->next;
	}

	// after building the complete list, kill the processes in reverse order. the first
	// entry in the list, and therefore the last killed, will be the root process
	DWORD result;
	PTREE_PROCESS temp;
	while (last) {
		result = KillProcess(last->processId);

		temp = last;
		last = last->previous;

		HeapFree(hHeap, 0, temp);
	}

	return result;
}