/*
 * NB: see also: _set_wait_mask()
 */
static BOOL _wait_on_mask(WINPR_COMM *pComm, ULONG *pOutputMask)
{
	assert(*pOutputMask == 0);

	EnterCriticalSection(&pComm->EventsLock);
	pComm->PendingEvents |= SERIAL_EV_FREERDP_WAITING;
	LeaveCriticalSection(&pComm->EventsLock);


	while (TRUE)
	{
		/* NB: EventsLock also used by _refresh_PendingEvents() */
		if (!_refresh_PendingEvents(pComm))
		{
			EnterCriticalSection(&pComm->EventsLock);
			pComm->PendingEvents &= ~SERIAL_EV_FREERDP_WAITING;
			LeaveCriticalSection(&pComm->EventsLock);
			return FALSE;
		}

		/* NB: ensure to leave the critical section before to return */
		EnterCriticalSection(&pComm->EventsLock);

		if (pComm->PendingEvents & SERIAL_EV_FREERDP_STOP)
		{
			pComm->PendingEvents &= ~SERIAL_EV_FREERDP_STOP;

			/* pOutputMask must remain empty but should
			 * not have been modified.
			 *
			 * http://msdn.microsoft.com/en-us/library/ff546805%28v=vs.85%29.aspx
			 */
			assert(*pOutputMask == 0);

			pComm->PendingEvents &= ~SERIAL_EV_FREERDP_WAITING;
			LeaveCriticalSection(&pComm->EventsLock);
			return TRUE;
		}

		_consume_event(pComm, pOutputMask, SERIAL_EV_RXCHAR);
		_consume_event(pComm, pOutputMask, SERIAL_EV_RXFLAG);
		_consume_event(pComm, pOutputMask, SERIAL_EV_TXEMPTY);
		_consume_event(pComm, pOutputMask, SERIAL_EV_CTS);
		_consume_event(pComm, pOutputMask, SERIAL_EV_DSR);
		_consume_event(pComm, pOutputMask, SERIAL_EV_RLSD);
		_consume_event(pComm, pOutputMask, SERIAL_EV_BREAK);
		_consume_event(pComm, pOutputMask, SERIAL_EV_ERR);
		_consume_event(pComm, pOutputMask, SERIAL_EV_RING );
		_consume_event(pComm, pOutputMask, SERIAL_EV_RX80FULL);

		LeaveCriticalSection(&pComm->EventsLock);

		/* NOTE: PendingEvents can be modified from now on but
		 * not pOutputMask */

		if (*pOutputMask != 0)
		{
			/* at least an event occurred */

			EnterCriticalSection(&pComm->EventsLock);
			pComm->PendingEvents &= ~SERIAL_EV_FREERDP_WAITING;
			LeaveCriticalSection(&pComm->EventsLock);
			return TRUE;
		}


		/* waiting for a modification of PendingEvents.
		 *
		 * NOTE: previously used a semaphore but used
		 * sem_timedwait() anyway. Finally preferred a simpler
		 * solution with Sleep() whithout the burden of the
		 * semaphore initialization and destroying.
		 */

		Sleep(100); /* 100 ms */
	}

	CommLog_Print(WLOG_WARN, "_wait_on_mask, unexpected return, WaitEventMask=0X%lX", pComm->WaitEventMask);
	EnterCriticalSection(&pComm->EventsLock);
	pComm->PendingEvents &= ~SERIAL_EV_FREERDP_WAITING;
	LeaveCriticalSection(&pComm->EventsLock);
	assert(FALSE);
	return FALSE;
}