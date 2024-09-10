void RankSystem::updatePos_init(RankStats* rr, Stats* s, bool sync)
{
	if(rr == NULL)	// Verify Pointer to RankStats
		return;

	if(s != NULL)	// NULL Stats Update (Only for Synchronization)
		rr->addStats(s);

	if(sync == true)
		updatePos_exec(rr);
	else
	{
		// Prevent Waiting on MAIN Thread
		HANDLE h_temp = CreateThread(NULL, 0, updatePos_thread, rr, CREATE_SUSPENDED, NULL);
		if(h_temp == NULL)
		{
			MF_SyncLog("updatePos_init: Couldn't create thread for updating Ranks");
		}
		else
		{
#ifdef _DEBUG
			MF_SyncLog("updatePos_init: Creating Thread #%d", GetThreadId(h_temp));
#endif
			SetThreadPriority(h_temp, THREAD_PRIORITY_LOWEST);
			ResumeThread(h_temp);
			CloseHandle(h_temp);
		}
	}
}