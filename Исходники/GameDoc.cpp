void CGameDoc::ResizeWindow(void)
{
	CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();

	CREATESTRUCT st;
	CREATESTRUCT& rst = st;

	pMain->PreCreateWindow(rst);

	rst.lpszName = _T("Game");
	rst.cx = (m_nRow + 1) * m_bmCell.cx + 180;
	rst.cy = (m_nCol + 1) * m_bmCell.cy + 100;

	CRect rect;
	pMain->GetClientRect(rect);
	pMain->MoveWindow(rect.left, rect.top, rst.cx, rst.cy);
}