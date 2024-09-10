void CLiveChatClient::HearbeatProc()
{
	FileLog("LiveChatClient", "CLiveChatClient::HearbeatProc() begin");

	const unsigned long nSleepStep = 200;	// ms
	const unsigned long nSendStep = 30 * 1000; // ms

	long long preTime = getCurrentTime();
	long long curTime = getCurrentTime();
	do {
		curTime = getCurrentTime();
		if (DiffTime(preTime, curTime) >= nSendStep) {
			HearbeatTask* task = new HearbeatTask();
			if (NULL != task) {
				task->Init(m_listener);
				int seq = m_seqCounter.GetAndIncrement();
				task->SetSeq(seq);
				m_taskManager->HandleRequestTask(task);
			}
			preTime = curTime;
		}
		Sleep(nSleepStep);
	} while (m_isHearbeatThreadRun);

	FileLog("LiveChatClient", "CLiveChatClient::HearbeatProc() end");
}