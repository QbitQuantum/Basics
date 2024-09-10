unsigned __stdcall gkThread::task(void* p)
{
	gkThread* pThread = static_cast<gkThread*>(p);

	pThread->run();

	_endthreadex(0);

	return 0;
}