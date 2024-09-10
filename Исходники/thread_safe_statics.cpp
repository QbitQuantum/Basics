// Wait on the condition variable.  In the XP implementation using only a Windows event
// we can't guarantee that we'll ever actually receive the notification signal, so we
// must use a non-infinite timeout.  This is not optimal: we may wake up early if the
// initializer is long-running, or we may miss the signal and not wake up until the
// timeout expires.  The signal may be missed because the sleeping threads may be
// stolen by the kernel to service an APC, or due to the race condition between the
// unlock call and the WaitForSingleObject call.
extern "C" bool __cdecl _Init_thread_wait(DWORD const timeout)
{
#if _CRT_NTDDI_MIN < NTDDI_VISTA
    if (!__scrt_is_event_api_used(_Tss_event))
    {
        return __crt_fast_decode_pointer(encoded_sleep_condition_variable_cs)(&_Tss_cv, &_Tss_mutex, timeout) != FALSE;
    }
    else
    {
        _ASSERT(timeout != INFINITE);
        _Init_thread_unlock();
        HRESULT res = WaitForSingleObjectEx(_Tss_event, timeout, FALSE);
        _Init_thread_lock();
        return (res == WAIT_OBJECT_0);
    }
#else
	return SleepConditionVariableCS(&_Tss_cv, &_Tss_mutex, timeout) != FALSE;
#endif
}