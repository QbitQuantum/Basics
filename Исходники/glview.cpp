// Idle Processing
BOOL CMyglApp::OnIdle(LONG lcount)
{
	CWnd* pMainWnd = m_pMainWnd;

	if (pMainWnd != NULL && pMainWnd->m_hWnd != NULL && pMainWnd->IsWindowVisible() && !pMainWnd->IsIconic())
	{
		if (lcount==0) {
		   CWinApp::OnIdle(lcount); // this does an WM_UPDATEIDLE ...
		}
		if (m_ActiveView) return(m_ActiveView->OnIdle(lcount));
	} 
	
	return FALSE;

		
#if 0
  if (!CWinApp::OnIdle(lcount)) {
		// if lcount == 0, there was a message before
		// pass up message to view
		if (m_ActiveView) return(m_ActiveView->OnIdle(lcount));

  }
  return TRUE; // send more messages
#endif

}