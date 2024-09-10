// Spawn a thread to a test
void ActiveTest::run(TestResult* result)
{
	CWinThread* thread;

	setTestResult(result);
	_runCompleted.ResetEvent();

	thread = AfxBeginThread(threadFunction, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	DuplicateHandle(GetCurrentProcess(), thread->m_hThread, GetCurrentProcess(), &_threadHandle, 0, FALSE, DUPLICATE_SAME_ACCESS);

	thread->ResumeThread();
}