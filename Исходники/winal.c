void _CancelThread(pthread_t tid, int exitcode) {
	#ifdef _WIN32
		/*
		 * IMPORTANT TODO:
		 * TerminateThread() should NOT be used!!
		 * Termination with this function is abrupt and could severely damage the application
		 * (it could hold a critical section within a system library, for instance)
		 * Under Windows 2000, XP, and Server 2003, the stack isn't freed resulting in a leak.
		 *
		 *   GET PROPER EXITING EVENT CODE IN HERE ASAP!
		 *
		 */
		HANDLE hThread;
		hThread = OpenThread(THREAD_TERMINATE, 0, tid);
		if (hThread) {
			TerminateThread(hThread, exitcode);
			CloseHandle(hThread);
		}
	#else
		pthread_cancel(tid);
	#endif
}