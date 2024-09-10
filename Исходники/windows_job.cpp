/*! Iterates over all the threads associated with this job (as determined by
 * mJobHandle), and runs the given callback function on them. The callback
 * function need not close the handle to the thread.
 *
 * \param callback The callback function to run on each thread.
 *
 * \par A few notes on the necessity and implementation of IterateThreads:
 * Before going to far into this function, you must realize that as much as one
 * may hope to the contrary, windows has no concept of mass process management.
 * If you want to do something to multiple processes or threads, windows
 * provides a few mediocre iteration methods, but beyond that, you're on your
 * own to find the processes and/or threads and work with them one at a time.
 * The following function was written for that exact purpose, it searches
 * through the list of all threads present in the entire system, finds the ones
 * whose parent process is part of the job object and runs the given callback
 * function on the thread.
 *
 * \par
 * The reason this is written on the thread level as opposed to the process
 * level (which would have been much easier), is because windows has no concept
 * of suspending a process, it can only suspend threads. Since the ability to
 * suspend and resume jobs was something that I wanted in GamessQ, it has to be
 * done on the tread level. When it comes to terminating processes, simply
 * terminating all their threads works just as well as terminating the process
 * via windows TerminatProcess function.
 *
 * \note
 * As clumsy as this method may seem, and as much as you may think and hope
 * that there MUST be a better way to do it, there really isn't. So far as I
 * have been able to find (and I searched for a while) this is the cleanest,
 * most efficient way to handle windows processes and threads in mass.
 *
 * \sa mJobHandle
 */
bool WindowsJob::IterateThreads(bool (*callback)(HANDLE))
{
	// We'll need this for later
	bool retVal = true;

	// get all the process ids for the job object
	JOBOBJECT_BASIC_PROCESS_ID_LIST *info;
	int num = mNumProcessors + 15; // make sure there's enough space
	int size = sizeof(JOBOBJECT_BASIC_PROCESS_ID_LIST) + num * sizeof(DWORD);
	info = (JOBOBJECT_BASIC_PROCESS_ID_LIST *)malloc(size);
	ZeroMemory(info, size);
	info->NumberOfAssignedProcesses = num;
	if (! QueryInformationJobObject(mJobHandle, JobObjectBasicProcessIdList,
			info, size, NULL)) {
		LOG_ERROR("QueryInformationJobObject");
		return false;
	}
	num = info->NumberOfProcessIdsInList;

	// get a thread snapshot
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	THREADENTRY32 entry;
	ZeroMemory(&entry, sizeof(entry));
	entry.dwSize = sizeof(entry);
	if (! Thread32First(snapshot, &entry)) {
		LOG_ERROR("Thread32First");
		CloseHandle(snapshot);
		return false;
	}

	// iterate through all the threads in the system.
	bool more = true;
	while (more) {
		// search through the job ids
		for (int i = 0; i < num; i ++) {
			// if this thread's parent is in the list, run the callback on it
			if (entry.th32OwnerProcessID == info->ProcessIdList[i]) {
				HANDLE threadHandle = OpenThread(THREAD_TERMINATE |
						THREAD_SUSPEND_RESUME , false, entry.th32ThreadID);
				if (! threadHandle) {
					LOG_ERROR("OpenThread");
				} else {
					retVal = retVal && callback(threadHandle);
				}
				CloseHandle(threadHandle);
				break;
			}
		}

		// get the next thread, and make sure it's valid
		ZeroMemory(&entry, sizeof(entry));
		entry.dwSize = sizeof(entry);
		if (! Thread32Next(snapshot, &entry)) {
			if (GetLastError() == ERROR_NO_MORE_FILES) {
				more = false;
			} else {
				LOG_ERROR("Thread32Next");
				free(info);
				CloseHandle(snapshot);
				return false;
			}
		}
	}

	// clean up
	free(info);
	CloseHandle(snapshot);
	return retVal;
}