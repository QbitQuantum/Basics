BOOL CModelerDoc::CreateModelFromScriptFile( CTFileName fnScrFileName, char *strError)
{
  CMainFrame* pMainFrame = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
  try
  {
    CWaitCursor StartWaitCursor;
   	
    CRect rectMainFrameSize;
    CRect rectProgress, rectProgressNew;
    
    pMainFrame->GetWindowRect( &rectMainFrameSize);
    pMainFrame->m_NewProgress.Create( IDD_NEW_PROGRESS, pMainFrame);
    pMainFrame->m_NewProgress.GetWindowRect( &rectProgress);
    
    rectProgressNew.left = rectMainFrameSize.Width()/2 - rectProgress.Width()/2;
    rectProgressNew.top = rectMainFrameSize.Height()/2 - rectProgress.Height()/2;
    rectProgressNew.right = rectProgressNew.left + rectProgress.Width();
    rectProgressNew.bottom = rectProgressNew.top + rectProgress.Height();

    pMainFrame->m_NewProgress.MoveWindow( rectProgressNew);
    pMainFrame->m_NewProgress.ShowWindow(SW_SHOW);

    m_emEditModel.LoadFromScript_t( fnScrFileName);
  }
  catch( char *err_str)
  {
    strcpy( strError, err_str);
    pMainFrame->m_NewProgress.DestroyWindow();
    return FALSE;
  }
  pMainFrame->m_NewProgress.DestroyWindow();
	m_bDocLoadedOk = TRUE;
	return TRUE;
}