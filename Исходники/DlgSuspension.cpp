void CDlgSuspension::OnNcLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CWnd *pParent = GetParent();
	ASSERT(pParent);
	
	if(!pParent->IsWindowVisible())
		pParent->ShowWindow(SW_SHOW);

	pParent->SetForegroundWindow();

	CDialog::OnNcLButtonDblClk(nFlags, point);
}