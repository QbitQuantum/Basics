DttSP_EXP void
StopKeyer ()
{
	EnterCriticalSection(update_ok);
	if (timerid)
		timeKillEvent ((UINT) timerid);
	LeaveCriticalSection(update_ok);
	timerid = 0;
}