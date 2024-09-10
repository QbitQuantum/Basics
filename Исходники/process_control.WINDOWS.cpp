bool
windows_continue(DWORD pid)
{
	// we should have a record from when we suspended this process
	//
	SuspendedProcess* sp;
	int ret = suspended_processes.lookup(pid, sp);

	// NOTE: In testing windows continuation the 
	// procd can at times pass invalid pid's to this function 
	// as a result, exit gracefully vs. assert.
	if (ret == -1)
	   return false;

	SuspendedThread* st;
	sp->startIterations();
	while (sp->iterate(st)) {

		// call ResumeThread as many times as we called SuspendThread
		// for this thread above
		//
		for (int i = 0; i < st->num_suspends; i++) {
			if (ResumeThread(st->handle) == (DWORD)-1) {
				dprintf(D_FULLDEBUG,
				        "windows_continue_process: ResumeThread error: %u\n",
				        GetLastError());
			}
		}

		// close our handle to this thread
		//
		if (CloseHandle(st->handle) == FALSE) {
			dprintf(D_FULLDEBUG,
			        "windows_continue_process: CloseHandle error: %u\n",
			        GetLastError());
		}

		// clean up this SuspendedThread object
		//
		delete st;
	}

	// clean up the SuspendedProcess object and remove it from the
	// hash table of processes
	//
	delete sp;
	ret = suspended_processes.remove(pid);
	ASSERT(ret != -1);

	return true;
}