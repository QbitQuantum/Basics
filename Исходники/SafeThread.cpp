CSafeThread* CSafeThread::BeginThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
		int nPriority, UINT nStackSize, DWORD dwCreateFlags,
		LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	ASSERT(pfnThreadProc != NULL);

	CSafeThread* pThread = new CSafeThread(pfnThreadProc, pParam);
	ASSERT_VALID(pThread);

	if (!pThread->CreateThread(dwCreateFlags|CREATE_SUSPENDED, nStackSize,
		lpSecurityAttrs))
	{
		pThread->Delete();
		return NULL;
	}
	VERIFY(pThread->SetThreadPriority(nPriority));
	if (!(dwCreateFlags & CREATE_SUSPENDED))
		VERIFY(pThread->ResumeThread() != (DWORD)-1);

	return pThread;
}