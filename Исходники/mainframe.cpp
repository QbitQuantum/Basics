void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 1)
	{
		DWORD dwFlags;
		if(InternetGetConnectedState(&dwFlags, 0))
		{
			theApp.m_DownloadCommand.InitNetCommand();
			KillTimer(nIDEvent);
		}
	}
	else if(nIDEvent == 2)
	{
		if(theApp.m_DownloadCommand.PreUpload())
			KillTimer(nIDEvent);
	}
	
	CFrameWnd::OnTimer(nIDEvent);
}