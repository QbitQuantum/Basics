//-------------------------------------------------------------------------------------
thread::TPThread* DBThreadPool::createThread(int threadWaitSecond)
{
	DBThread* tptd = new DBThread(this, threadWaitSecond);
	tptd->createThread();
	return tptd;
}	