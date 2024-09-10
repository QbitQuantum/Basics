		jz		no_cpuid		; make sure it's now on
	}

	//
	// make ourselves high priority just for the time between
	// when we measure the time and the CPU ticks
	//
	DWORD dwPriorityClass = GetPriorityClass(GetCurrentProcess());
	int dwThreadPriority = GetThreadPriority(GetCurrentThread());
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	//
	// start timing
	//
	s_milliseconds0 = (int)timeGetTime();

	__asm
	{
		lea		ecx, s_ticks0		; get the offset
		mov		dword ptr [ecx], 0	; zero the memory
		mov		dword ptr [ecx+4], 0	;
		rdtsc						; read time-stamp counter
		mov		[ecx], eax			; store the negative
		mov		[ecx+4], edx		; in the variable
	}

	//
	// restore thread priority
	//
	SetThreadPriority(GetCurrentThread(), dwThreadPriority);