VOID FireCommandAux(LPCTSTR Command, BOOL WaitForResponse, BOOL startThread, BOOL StopStdoutPrinterThread, BOOL WantPreprocess, FireCommandThreadArgs *pArgs) 
{

	#define MAXLEN    (3*1024)

	TCHAR NewCommand[MAXLEN];

	if(StopStdoutPrinterThread)
		//stop StdoutPrinterThread
		SignalObjectAndWait( hSigSuspendStdoutPrinterThread
			                ,hSigStdoutPrinterThreadSuspended, INFINITE, FALSE);


	RtfWindowSetCommand(Command);
	RtfWindowStartNextOutput();
	AddHistory(Command);

	if(WantPreprocess) {
		PreprocessCommand(Command, NewCommand);
		SendToGHCiStdinLn(NewCommand);
	}
	else
		SendToGHCiStdinLn(Command);


	if(WaitForResponse) {
		Running = TRUE;
		EnableButtons();
		
		PrintGHCiOutput(hChildStdoutRd, ForegroundColor);
		
		Running = FALSE;
		EnableButtons();

	}

	// resume StdoutPrinterThread
	if(StopStdoutPrinterThread)
		SetEvent(hSigResumeStdoutPrinterThread);

	if(startThread) {
		// free arguments
		free((LPTSTR)Command);
		free(pArgs);
	}
}