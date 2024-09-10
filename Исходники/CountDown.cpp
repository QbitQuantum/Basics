void CCountDown::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
		if (m_combo_hr.GetWindowTextLengthW() == 0 ||
		m_combo_min.GetWindowTextLengthW() == 0 ||
		m_combo_sec.GetWindowTextLengthW() == 0)
		MessageBox(_T("時間欄位不可留白"), _T("錯誤"),  MB_ICONERROR | MB_OK);
	else if (m_edit_path.GetWindowTextLengthW() == 0)
		MessageBox(_T("請選擇音樂檔案"), _T("錯誤"),  MB_ICONERROR | MB_OK);
	else {
		m_combo_hr.GetWindowText(send[0]);
		m_combo_min.GetWindowText(send[1]);
		m_combo_sec.GetWindowText(send[2]);
		m_edit_path.GetWindowText(send[3]);
		if (m_but_cycle.GetCheck() == BST_CHECKED)
			send[4] = L"是";
		else
			send[4] = L"否";

		CWnd* pWnd = CWnd::GetParent();
		pWnd->SendMessageW(WM_MYMESSAGE_SENDCOUNTDOWNDATA, (WPARAM)&send);

		CDialogEx::OnOK();
	}
}