void CApaParentProcessMonitor::RunL()
	{
	// Do something that will kill the child when the parent process terminates
	if(iStatus==KErrNone)
		{
		RProcess proc;
		proc.Terminate(KErrNone);
		}
	}