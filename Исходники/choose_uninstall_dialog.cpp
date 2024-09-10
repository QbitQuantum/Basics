//用于拖动
LRESULT CChooseUninstallDialog::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
	ReleaseCapture();
	SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
	return 0;
}