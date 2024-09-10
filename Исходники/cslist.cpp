BOOL CSWindow::itemPassedFilter(ListItem< StatusItem >* li)
{
	wchar_t filter[MAX_PATH];
	GetDlgItemText(m_handle, IDC_FILTER_FIELD, filter, _countof(filter));

	if (mir_wstrlen(filter))
	{
		wchar_t title[EXTRASTATUS_TITLE_LIMIT], message[EXTRASTATUS_MESSAGE_LIMIT];
		mir_wstrcpy(title, li->m_item->m_tszTitle); mir_wstrcpy(message, li->m_item->m_tszMessage);
		if (strpos(wcslwr(title), wcslwr(filter)) == -1)
			if (strpos(wcslwr(message), wcslwr(filter)) == -1)
				return FALSE;
	}

	return TRUE;
}