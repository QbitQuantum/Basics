BOOL CPageLangDisplay::OnInitDialog()
{
	// if we're not in a wizard, we want the abrev box uneditable
	// However, I can't get it to display correctly, even with this
	// code; it always looks editable.  I've also tried doing this
	// at ddx time, no difference, and tried with WS_DISABLED.
	//
	// Also tried putting this in OnCreate, but I couldn't get a
	// handle to the CEDit at that time

	CPropertyPage::OnInitDialog();

	if(m_bAbrevIsReadOnly)
	{
			CWnd *pWnd = GetDlgItem(IDC_EDITAbrev);
			::SendMessage(pWnd->m_hWnd, EM_SETREADONLY, (WPARAM)TRUE, 0);

	//		pWnd->ModifyStyle(NULL ,  ES_READONLY);
			pWnd->Invalidate();
			pWnd->GetParent()->Invalidate();
			Invalidate();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}