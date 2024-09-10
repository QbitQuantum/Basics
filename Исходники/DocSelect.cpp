LRESULT CDocSelector::OnSelChange(WPARAM wParam, LPARAM)
{
	// Killing the timer, because timer can change the
	// selection in between the procedure...
	KillTimer( DS_TIMER_ID ); // Yogesh Jagota

	// sent when a button gets clicked
	CSwitcherButton* newsel = (CSwitcherButton*)wParam;

	// Yogesh Jagota
	CMDIFrameWnd *pFrame = (CMDIFrameWnd *)AfxGetMainWnd();
	//CWnd* Window = (CWnd*)newsel->m_FrameWnd;//Y.Ivanov
	CWnd* Window = (CWnd*)newsel->m_AttachedView->GetParentFrame();//Yuriy Ivanov
	pFrame->MDIActivate( Window );
	if(Window->IsIconic())
		Window->ShowWindow(SW_SHOWNORMAL);
	pFrame->Invalidate();

	// End Yogesh Jagota

	if (m_iSelectedButton > -1)
		GetButtonFromID(m_iSelectedButton)->Unselect();

	m_iSelectedButton = newsel->m_iID;

	// Reactivate the timer...
	SetTimer( DS_TIMER_ID, 10, NULL ); // Yogesh Jagota


	return 1;
}