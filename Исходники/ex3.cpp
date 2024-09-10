DWORD WINAPI compare(LPVOID arg) {
	while (1) {
		WaitForSingleObject(eventComparator, INFINITE);
		for (DWORD i = 0; i < nbThreads - 1; i++) {
			if (_tcscmp(entries[i], entries[i + 1])) {
				//If entries are different
				ExitThread(1);
			}
		}

		/*Check if all entries are "", which means that all the reading
		 threads have terminated*/
		DWORD i = 0;
		while (i < nbThreads && !_tcscmp(entries[i], _T(""))) {
			i++;
		}

		if (i == nbThreads) {
			//All the reading threads have terminated -->directories are equals
			ExitThread(0);
		}

		EnterCriticalSection(&criticalSection);
		counter = 0;
		LeaveCriticalSection(&criticalSection);
		
		//Release the reading threads
		PulseEvent(eventReaders);
	}
}