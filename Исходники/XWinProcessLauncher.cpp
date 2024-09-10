bool XWinProcessLauncher::IsRunning()
{
	if(!fWaitClosingChildProcess)
	{
		if(fProcessID!= 0 && fIsRunning) {
			fIsRunning = GetProcessVersion(fProcessID) != 0;// Does this work *every* time?
			if (!fIsRunning) {

				if (fCanGetExitStatus) {

					GetExitCodeProcess(fProcInfo.hProcess, &fExitStatus);

					CloseHandle(fProcInfo.hProcess);
					CloseHandle(fProcInfo.hThread);

				}

			}
				
		}
	}
	
	return fIsRunning;
}