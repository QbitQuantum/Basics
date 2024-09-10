LRESULT COptionsPage::OnWizardNext(void)
{
	CWnd* pWnd;

	pWnd = GetDlgItem(IDC_EDIT_SOURCE);
	ASSERT(pWnd != NULL);
	if (pWnd->GetWindowTextLength() == 0)
	{
		AfxMessageBox(IDS_NO_SOURCE, MB_ICONSTOP | MB_OK);
		pWnd->SetFocus();
		return (-1);
	}
	pWnd = GetDlgItem(IDC_EDIT_TARGET);
	ASSERT(pWnd != NULL);
	if (pWnd->GetWindowTextLength() == 0)
	{
		AfxMessageBox(IDS_NO_TARGET, MB_ICONSTOP | MB_OK);
		pWnd->SetFocus();
		return (-1);
	}
	m_dtpWrite.GetTime(m_timeWrite);
	return (__super::OnWizardNext());
}