LOCAL TCALLBACK void
hal_close(struct THALBase *hal, struct TTask *task)
{
	struct HALSpecific *hws = hal->hmb_Specific;

	EnterCriticalSection(&hws->hsp_DevLock);

	if (hws->hsp_Timer)
	{
		if (--hws->hsp_RefCount == 0)
		{
			timeKillEvent(hws->hsp_Timer);
			timeEndPeriod(1);
			hws->hsp_Timer = TNULL;
		}
	}

	LeaveCriticalSection(&hws->hsp_DevLock);
}