void CDlgApplication::OnApplicationMax()
{
	// 最大化所选择窗口
	HWND hWnd=(HWND)m_wndListApp.GetItemData(m_nCurSelItem);

	// 在另外线程中最大化所选择窗口
	ShowWindowAsync(hWnd,SW_MAXIMIZE);
}