bool CMyTaskThread::IsSelfThread()
{
	return GetCurrentThreadId()==GetThreadID();
}