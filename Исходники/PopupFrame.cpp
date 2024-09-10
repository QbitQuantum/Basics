LRESULT CPopupFrame::OnThemeChanged(WPARAM, LPARAM)
{
	if (m_hThemeDLL != NULL)
	{
		CloseThemeData();
		OpenThemeData();
	}

	return 0;
}