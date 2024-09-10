static VOID CALLBACK MsgTimer(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	LIST<TMsgQueue> arTimedOut(1);
	{
		mir_cslock lck(csMsgQueue);
		for (int i = msgQueue.getCount() - 1; i >= 0; i--) {
			TMsgQueue *item = msgQueue[i];
			if (dwTime - item->ts > g_dat.msgTimeout) {
				arTimedOut.insert(item);
				msgQueue.remove(i);
			}
		}
	}

	for (int i = 0; i < arTimedOut.getCount(); ++i)
		MessageFailureProcess(arTimedOut[i], LPGEN("The message send timed out."));
}