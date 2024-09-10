void CDemoDescriptionDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CWnd* pWnd = ChildWindowFromPoint(point);
	
	if (pWnd != NULL)
	{
		if (pWnd->GetDlgCtrlID() == IDC_DISCOUNT_CD_CATALOG)
		{
			// Start up the discount CD catalog!
			((CMainFrame*)(AfxGetMainWnd()))->DoProductCatalog();
			return;
		}
	}
	
	CPmwDialog::OnLButtonDblClk(nFlags, point);
}