static ETHR_INLINE int
wait(ethr_event *e, int spincount)
{
    LONG state;
    DWORD code;
    int sc, res, until_yield = ETHR_YIELD_AFTER_BUSY_LOOPS;

    if (spincount < 0)
	ETHR_FATAL_ERROR__(EINVAL);

    sc = spincount;

    while (1) {
	long on;
	while (1) {
#if ETHR_READ_AND_SET_WITHOUT_INTERLOCKED_OP__
	    state = e->state;
#else
	    state = _InterlockedExchangeAdd(&e->state, (LONG) 0);
#endif
	    if (state == ETHR_EVENT_ON__)
		return 0;
	    if (sc == 0)
		break;
	    sc--;
	    ETHR_SPIN_BODY;
	    if (--until_yield == 0) {
		until_yield = ETHR_YIELD_AFTER_BUSY_LOOPS;
		res = ETHR_YIELD();
		if (res != 0)
		    ETHR_FATAL_ERROR__(res);
	    }
	}

	if (state != ETHR_EVENT_OFF_WAITER__) {
	    state = _InterlockedCompareExchange(&e->state,
						ETHR_EVENT_OFF_WAITER__,
						ETHR_EVENT_OFF__);
	    if (state == ETHR_EVENT_ON__)
		return 0;
	    ETHR_ASSERT(state == ETHR_EVENT_OFF__);
	}

	code = WaitForSingleObject(e->handle, INFINITE);
	if (code != WAIT_OBJECT_0)
	    ETHR_FATAL_ERROR__(ethr_win_get_errno__());
    }

}