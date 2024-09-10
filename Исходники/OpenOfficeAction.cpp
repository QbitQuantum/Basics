void OpenOfficeAction::FinishExecution(ExecutionProcess process)
{
	HWND hwndTray; 
		
	hwndTray = FindWindow( LISTENER_WINDOWCLASS, NULL);

    if (hwndTray)
	{
		SendMessage(hwndTray, RegisterWindowMessage(KILLTRAY_MESSAGE), 0, 0);
	}

	Runner runner;
	vector <DWORD> processIDs = runner.GetProcessID(wstring(SOFFICE_PROCESSNAME));

	for (unsigned int i = 0; i < processIDs.size(); i++)
	{
		runner.TerminateProcessID(processIDs.at(i));
	}
}