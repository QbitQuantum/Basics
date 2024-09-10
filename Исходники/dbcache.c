void DBFlush(int setting)
{
	if(!setting) {
		log0("nflush1");
		if(safetyMode && pDbCache) {
			if (FlushViewOfFile(pDbCache, 0) == 0) {
				if (flushFailTick == 0)
					flushFailTick = GetTickCount();
				else if (GetTickCount() - flushFailTick > 5000) 
					DatabaseCorruption(NULL);
			}
			else
				flushFailTick = 0;
		}
		log0("nflush2");
		return;
	}
	KillTimer(NULL,flushBuffersTimerId);
	flushBuffersTimerId=SetTimer(NULL,flushBuffersTimerId,50,DoBufferFlushTimerProc);
}