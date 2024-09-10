BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam)
{
	CWnd* pWnd = CWnd::FromHandle(hwnd);
	CSize* pTranslate = (CSize*) lParam;
	CAddNewItem* pDlg = (CAddNewItem*) pWnd->GetParent();
	if (!pDlg) return FALSE;
	CRect rect;
	pWnd->GetWindowRect(rect);
	pDlg->ScreenToClient(rect);
	if (hwnd == pDlg->m_GridCtrl.GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
							 rect.Width()+pTranslate->cx, 
							 rect.Height()+pTranslate->cy, FALSE);
	}else if(pWnd->GetDlgCtrlID()==IDC_ADDORDER_PROG_BAR){
		pWnd->MoveWindow(rect.left+pTranslate->cx/2, rect.top+pTranslate->cy/2, 
							 rect.Width(), rect.Height(), FALSE);
	}else if(pWnd->GetDlgCtrlID()==IDC_DIAG_PRINT)
		pWnd->MoveWindow(rect.left+pTranslate->cx, rect.top+pTranslate->cy, rect.Width(), rect.Height(), FALSE);
	else
		pDlg->UpdateControlPostion(pWnd,rect,lParam);
	pDlg->Invalidate();
	return TRUE;
}