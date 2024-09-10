	uintptr OSDep::startIntWriteTimer(uint32 millis, int *addr)
	{
		return (uintptr) timeSetEvent(millis, millis, (LPTIMECALLBACK)intWriteTimerProc, (DWORD_PTR)addr, 
			TIME_PERIODIC | TIME_CALLBACK_FUNCTION
#ifndef UNDER_CE
			| TIME_KILL_SYNCHRONOUS
#endif
			);
	}