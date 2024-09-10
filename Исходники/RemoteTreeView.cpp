void CRemoteTreeView::CreateImageList()
{
	wxSize s = CThemeProvider::GetIconSize(iconSizeSmall);
	m_pImageList = new wxImageList(s.x, s.y, true, 4);

	// Normal directory
	int index = GetIconIndex(iconType::dir, _T("{78013B9C-3532-4fe1-A418-5CD1955127CC}"), false);
	m_pImageList->Add(CreateIcon(index));
	m_pImageList->Add(CreateIcon(index, _T("ART_UNKNOWN")));

	// Opened directory
	index = GetIconIndex(iconType::opened_dir, _T("{78013B9C-3532-4fe1-A418-5CD1955127CC}"), false);
	m_pImageList->Add(CreateIcon(index));
	m_pImageList->Add(CreateIcon(index, _T("ART_UNKNOWN")));

	SetImageList(m_pImageList);
}