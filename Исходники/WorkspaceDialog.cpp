void CWorkspaceDialog::OnClose()
{
	// Is a modal dialog box is up (like the about box), don't destroy the window
	CWnd* pPopup = GetLastActivePopup();
	if (pPopup && (pPopup->m_hWnd != m_hWnd))
		return;

	CDHtmlDialog::OnClose();
	DestroyWindow();
}