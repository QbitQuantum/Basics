CRunQueue::~CRunQueue()
{
	if (mh_Thread)
	{
		Terminate();
		SafeCloseHandle(mh_Thread);
	}

	SafeDelete(mpcs_QueueLock);
}