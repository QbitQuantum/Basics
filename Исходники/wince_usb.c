// Internal API functions
static int wince_init(struct libusb_context *ctx)
{
	int i, r = LIBUSB_ERROR_OTHER;
	HANDLE semaphore;
	TCHAR sem_name[11+1+8]; // strlen(libusb_init)+'\0'+(32-bit hex PID)

	_stprintf(sem_name, _T("libusb_init%08X"), (unsigned int)GetCurrentProcessId()&0xFFFFFFFF);
	semaphore = CreateSemaphore(NULL, 1, 1, sem_name);
	if (semaphore == NULL) {
		usbi_err(ctx, "could not create semaphore: %s", windows_error_str(0));
		return LIBUSB_ERROR_NO_MEM;
	}

	// A successful wait brings our semaphore count to 0 (unsignaled)
	// => any concurent wait stalls until the semaphore's release
	if (WaitForSingleObject(semaphore, INFINITE) != WAIT_OBJECT_0) {
		usbi_err(ctx, "failure to access semaphore: %s", windows_error_str(0));
		CloseHandle(semaphore);
		return LIBUSB_ERROR_NO_MEM;
	}

	// NB: concurrent usage supposes that init calls are equally balanced with
	// exit calls. If init is called more than exit, we will not exit properly
	if ( ++concurrent_usage == 0 ) {	// First init?
		// Initialize pollable file descriptors
		init_polling();

		// Load DLL imports
		if (init_dllimports() != LIBUSB_SUCCESS) {
			usbi_err(ctx, "could not resolve DLL functions");
			r = LIBUSB_ERROR_NOT_SUPPORTED;
			goto init_exit;
		}

		// try to open a handle to the driver
		driver_handle = UkwOpenDriver();
		if (driver_handle == INVALID_HANDLE_VALUE) {
			usbi_err(ctx, "could not connect to driver");
			r = LIBUSB_ERROR_NOT_SUPPORTED;
			goto init_exit;
		}

		// Windows CE doesn't have a way of specifying thread affinity, so this code
		// just has  to hope QueryPerformanceCounter doesn't report different values when
		// running on different cores.
		r = LIBUSB_ERROR_NO_MEM;
		for (i = 0; i < 2; i++) {
			timer_request[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
			if (timer_request[i] == NULL) {
				usbi_err(ctx, "could not create timer request event %d - aborting", i);
				goto init_exit;
			}
		}
		timer_response = CreateSemaphore(NULL, 0, MAX_TIMER_SEMAPHORES, NULL);
		if (timer_response == NULL) {
			usbi_err(ctx, "could not create timer response semaphore - aborting");
			goto init_exit;
		}
		timer_mutex = CreateMutex(NULL, FALSE, NULL);
		if (timer_mutex == NULL) {
			usbi_err(ctx, "could not create timer mutex - aborting");
			goto init_exit;
		}
		timer_thread = CreateThread(NULL, 0, wince_clock_gettime_threaded, NULL, 0, NULL);
		if (timer_thread == NULL) {
			usbi_err(ctx, "Unable to create timer thread - aborting");
			goto init_exit;
		}

		// Wait for timer thread to init before continuing.
		if (WaitForSingleObject(timer_response, INFINITE) != WAIT_OBJECT_0) {
			usbi_err(ctx, "Failed to wait for timer thread to become ready - aborting");
			goto init_exit;
		}
	}
	// At this stage, either we went through full init successfully, or didn't need to
	r = LIBUSB_SUCCESS;

init_exit: // Holds semaphore here.
	if (!concurrent_usage && r != LIBUSB_SUCCESS) { // First init failed?
		if (driver_handle != INVALID_HANDLE_VALUE) {
			UkwCloseDriver(driver_handle);
			driver_handle = INVALID_HANDLE_VALUE;
		}
		if (timer_thread) {
			SetEvent(timer_request[1]); // actually the signal to quit the thread.
			if (WAIT_OBJECT_0 != WaitForSingleObject(timer_thread, INFINITE)) {
				usbi_warn(ctx, "could not wait for timer thread to quit");
				TerminateThread(timer_thread, 1); // shouldn't happen, but we're destroying
												  // all objects it might have held anyway.
			}
			CloseHandle(timer_thread);
			timer_thread = NULL;
		}
		for (i = 0; i < 2; i++) {
			if (timer_request[i]) {
				CloseHandle(timer_request[i]);
				timer_request[i] = NULL;
			}
		}
		if (timer_response) {
			CloseHandle(timer_response);
			timer_response = NULL;
		}
		if (timer_mutex) {
			CloseHandle(timer_mutex);
			timer_mutex = NULL;
		}
	}

	if (r != LIBUSB_SUCCESS)
		--concurrent_usage; // Not expected to call libusb_exit if we failed.

	ReleaseSemaphore(semaphore, 1, NULL);	// increase count back to 1
	CloseHandle(semaphore);
	return r;
}