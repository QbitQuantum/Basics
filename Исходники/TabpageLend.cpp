BOOL CTabpageLend::PreTranslateMessage(MSG* pMsg)
{
	CEdit* pEditId = (CEdit*)GetDlgItem(IDC_EDIT_ID);
	CEdit* pEditGunId = (CEdit*)GetDlgItem(IDC_EDIT_GUN);
	if (pEditId != NULL && pMsg->hwnd == pEditId->GetSafeHwnd()
		&& VK_RETURN == pMsg->wParam)
	{
		CString id;
		pEditId->GetWindowTextW(id);
		DoIDInput(id);
		return TRUE;
	}
	else if (pEditGunId != NULL && pMsg->hwnd == pEditGunId->GetSafeHwnd()
		&& VK_RETURN == pMsg->wParam)
	{
		CString gunId;
		pEditGunId->GetWindowTextW(gunId);
		DoGunIDInput(gunId);
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}