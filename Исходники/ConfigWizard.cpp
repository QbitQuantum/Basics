void CConfigWizard::AddBoard(LPRECT lpRect, LPCTSTR desc)
{
	CDialog *pDlg = new T;
	pDlg->Create(T::IDD, &m_bnBoardPlace);
	pDlg->MoveWindow(lpRect);
	pDlg->SetWindowText(desc);
	m_wizards.push_back(pDlg);
	m_lbStep.AddItem(0, desc);
}