// The receiver has terminated. Remove from the Processor's Pending Terminations
// list. Answer whether the process was actually on that list.
void OverlappedCall::RemoveFromPendingTerminations()
{
	ProcessOTE* oteProc = pendingTerms()->remove(m_oteProcess);
	if (oteProc == m_oteProcess)
	{
		Process* myProc = oteProc->m_location;
		HARDASSERT(myProc->Thread() == this);
		myProc->ClearThread();

		// Return it to the scheduling queues - we resume it to cause a scheduling decision to be made. 
		Interpreter::resume(oteProc);
		// Remove the reference that was from the pending terminations list
		oteProc->countDown();
	}
	else
	{
		HARDASSERT(oteProc->isNil());
	}

	m_oteProcess->countDown();
	m_oteProcess = (ProcessOTE*)Pointers.Nil;

	// Remove the call from the active list as it is being destroyed - I don't think we need
	// the lock anymore
	{
		//CMonitorLock lock(s_listMonitor);
		Unlink();
	}
}