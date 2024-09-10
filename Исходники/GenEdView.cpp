void CGenEdView::OnActivateEditor (LPARAM, WPARAM)
{
	CWnd *pWnd;

	assert (m_pServer != NULL);
	if (m_pServer == NULL)
		return;

	pWnd = m_pServer->GetInPlaceWindow ();
	if (pWnd == NULL)
		return;

	pWnd->SetFocus ();
}