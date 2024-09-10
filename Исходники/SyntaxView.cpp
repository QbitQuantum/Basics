void CSyntaxView::OnContextMenu(HWND /*phWnd*/, CPoint pPoint)
{
	WTL::CMenu m;
	m.LoadMenu(IDR_POPUP_SYNTAX);
	m.EnableMenuItem(ID_EDIT_COPY, m_list.GetSelectedCount() == 0);
	m.EnableMenuItem(ID_EDIT_COPYALL, m_list.GetItemCount() == 0);
	m.EnableMenuItem(ID_SYNTAX_LOCATEERROR, m_list.GetItemCount() == 0);
	unsigned int id = m.GetSubMenu(0).TrackPopupMenuEx(TPM_RETURNCMD, pPoint.x, pPoint.y, m_hWnd, NULL);
	switch (id)
	{
	case ID_EDIT_COPY:
		{
			int row = m_list.GetSelectedIndex();
			std::_tstring clip;
			FormatRow(m_list, row, clip);
			SetClipboard(clip);
		}
		break;
	case ID_EDIT_COPYALL:
		{
			std::_tstring clip;
			for (int i = 0; i < m_list.GetItemCount(); ++i)
			{
				if (!clip.empty())
					clip += _T("\r\n");
				FormatRow(m_list, i, clip);
			}
			SetClipboard(clip);
		}
		break;
	case ID_SYNTAX_LOCATEERROR:	
		{
			int row = m_list.GetSelectedIndex();
			if (row > -1)
			{
				CString code;
				m_list.GetItemText(row, 1, code);
				ShowHelp((const TCHAR *)code);
			}
		}
		break;
	}
}