static bool windows_init_clock(struct libusb_context *ctx)
{
	DWORD_PTR affinity, dummy;
	HANDLE event;
	LARGE_INTEGER li_frequency;
	int i;

	if (QueryPerformanceFrequency(&li_frequency)) {
		// The hires frequency can go as high as 4 GHz, so we'll use a conversion
		// to picoseconds to compute the tv_nsecs part in clock_gettime
		hires_frequency = li_frequency.QuadPart;
		hires_ticks_to_ps = UINT64_C(1000000000000) / hires_frequency;
		usbi_dbg("hires timer available (Frequency: %"PRIu64" Hz)", hires_frequency);

		// Because QueryPerformanceCounter might report different values when
		// running on different cores, we create a separate thread for the timer
		// calls, which we glue to the first available core always to prevent timing discrepancies.
		if (!GetProcessAffinityMask(GetCurrentProcess(), &affinity, &dummy) || (affinity == 0)) {
			usbi_err(ctx, "could not get process affinity: %s", windows_error_str(0));
			return false;
		}

		// The process affinity mask is a bitmask where each set bit represents a core on
		// which this process is allowed to run, so we find the first set bit
		for (i = 0; !(affinity & (DWORD_PTR)(1 << i)); i++);
		affinity = (DWORD_PTR)(1 << i);

		usbi_dbg("timer thread will run on core #%d", i);

		event = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (event == NULL) {
			usbi_err(ctx, "could not create event: %s", windows_error_str(0));
			return false;
		}

		timer_thread = (HANDLE)_beginthreadex(NULL, 0, windows_clock_gettime_threaded, (void *)event,
				0, (unsigned int *)&timer_thread_id);
		if (timer_thread == NULL) {
			usbi_err(ctx, "unable to create timer thread - aborting");
			CloseHandle(event);
			return false;
		}

		if (!SetThreadAffinityMask(timer_thread, affinity))
			usbi_warn(ctx, "unable to set timer thread affinity, timer discrepancies may arise");

		// Wait for timer thread to init before continuing.
		if (WaitForSingleObject(event, INFINITE) != WAIT_OBJECT_0) {
			usbi_err(ctx, "failed to wait for timer thread to become ready - aborting");
			CloseHandle(event);
			return false;
		}

		CloseHandle(event);
	} else {
		usbi_dbg("no hires timer available on this platform");
		hires_frequency = 0;
		hires_ticks_to_ps = UINT64_C(0);
	}

	return true;
}