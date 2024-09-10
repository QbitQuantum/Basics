void CEditorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	m_start = point;
	m_isDown = true;
	
	CEditorWindowDlg *pDlgVirtualWindow;
	pDlgVirtualWindow = new CEditorWindowDlg();
	pDlgVirtualWindow->Create(IDD_EDITOR_WINDOW_DIALOG, (CWnd *)this);
	pDlgVirtualWindow->MoveWindow(point.x, point.y, 0, 0);
	pDlgVirtualWindow->ShowWindow(SW_SHOW);

	m_arrPVirtualWindow.Add(pDlgVirtualWindow);

	SetCapture();

	CDialogEx::OnLButtonDown(nFlags, point);
}