UIOHOOK_API int hook_enable() {
	int status = UIOHOOK_FAILURE;

	// Make sure the native thread is not already running.
	if (hook_is_enabled() != true) {
		// Create event handles for the thread hook.
		hook_control_handle = CreateEvent(NULL, TRUE, FALSE, "hook_control_handle");

		LPTHREAD_START_ROUTINE lpStartAddress = &hook_thread_proc;
		hook_thread_handle = CreateThread(NULL, 0, lpStartAddress, NULL, 0, &hook_thread_id);
		if (hook_thread_handle != INVALID_HANDLE_VALUE) {
			logger(LOG_LEVEL_DEBUG,	"%s [%u]: Start successful\n",
							__FUNCTION__, __LINE__);

			// Attempt to set the thread priority to time critical.
			// TODO This maybe a little overkill, re-evaluate.
			BOOL status_priority =
					SetThreadPriority(hook_thread_handle, THREAD_PRIORITY_TIME_CRITICAL);
			if (!status_priority) {
				logger(LOG_LEVEL_WARN,
						"%s [%u]: Could not set thread priority %li for thread %#p! (%#lX)\n",
						__FUNCTION__, __LINE__,
						(long) THREAD_PRIORITY_TIME_CRITICAL,
						hook_thread_handle,
						(unsigned long) GetLastError());
			}

			// Wait for any possible thread exceptions to get thrown into
			// the queue
			WaitForSingleObject(hook_control_handle, INFINITE);

			// TODO Set the return status to the thread exit code.
			if (hook_is_enabled()) {
				logger(LOG_LEVEL_DEBUG,	"%s [%u]: Start successful\n",
						__FUNCTION__, __LINE__);

				status = UIOHOOK_SUCCESS;
			}
			else {
				logger(LOG_LEVEL_ERROR,	"%s [%u]: Initialization failure!\n",
						__FUNCTION__, __LINE__);

				// Wait for the thread to die.
				WaitForSingleObject(hook_thread_handle,  INFINITE);

				DWORD thread_status;
				GetExitCodeThread(hook_thread_handle, &thread_status);
				status = (int) thread_status;

				logger(LOG_LEVEL_ERROR,	"%s [%u]: Thread Result: %i!\n",
						__FUNCTION__, __LINE__, status);
			}
		}
		else {
			logger(LOG_LEVEL_ERROR,	"%s [%u]: Thread create failure!\n",
					__FUNCTION__, __LINE__);

			status = UIOHOOK_ERROR_THREAD_CREATE;
		}
	}

	return status;
}