UINT CAboutDlg::OnNcHitTest(CPoint point) 
{
	CRect rectClient;
	CPoint ptClient(point);

	GetClientRect(rectClient);
	ScreenToClient(&ptClient);
	if(rectClient.PtInRect(ptClient))
	{
		return (HTCLIENT);
	}
	else 
	{
		return (CWnd::OnNcHitTest(point));
	}
//	return CDialog::OnNcHitTest(point);
}