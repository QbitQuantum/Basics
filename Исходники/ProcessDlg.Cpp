void CProcessDlg::OnTerminateProcess() 
{
	DWORD		     ProcessId;
	LPSTR serverName = g_pDoc->GetServerName();
	HANDLE serverHandle = WTSOpenServer(serverName);
	CString	tempName;
	int    temp;
	PWTS_PROCESS_INFO pProcess = pProcessInfo;

	temp = m_processList.GetCurSel();
	m_processList.GetText(temp, tempName);
	
	for (DWORD i=0; i < count; i++)
	{
		if (tempName == (pProcess->pProcessName))
		{
			ProcessId = pProcess->ProcessId;
			if (!WTSTerminateProcess(serverHandle,ProcessId,0x0))
				AfxMessageBox("Unable to terminate process");
			i = count;
		}
		pProcess++;
	}
	Refresh();
}