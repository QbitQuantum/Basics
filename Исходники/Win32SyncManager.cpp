bool Win32SyncManager::QueuePeriodicTimer(int period, void (*timerFn)()){
#ifndef UNDER_CE
	if(timerHandle != NULL)
		return false; // can only have one timer right now

	BOOL ret = CreateTimerQueueTimer(&timerHandle, NULL, Win32ChessWaitOrTimerCallback, timerFn, period, period, WT_EXECUTELONGFUNCTION);
	if(!ret){
		return false;
	}
	//timerDisabled = false;
	//timerPauseCount = 0;
#endif
	return true;
}