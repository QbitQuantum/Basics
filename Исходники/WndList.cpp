void CWndList::AddItem(HWND hwnd)
{
			CString strName;
			LONG lval;
			wchar_t	szClassName[MAX_PATH];
			GetClassName(hwnd, szClassName, MAX_PATH);

			CWnd* wnd = CWnd::FromHandle(hwnd);
			wnd->GetWindowTextW(strName);

			
		//	if (strName.Trim().GetLength() > 0)
			{
				int iCount = m_List.GetItemCount();
				
				m_List.InsertItem(iCount, strName);

				LVITEM item;
				item.iItem = iCount;
				item.mask = LVIF_TEXT;
				item.iSubItem = 1;
				item.pszText = _tcsdup(szClassName);
				m_List.SetItem(&item);

				// hwnd
				_stprintf_s(szClassName, _T("%x"), (int)hwnd);
				item.iSubItem = 2;
				item.pszText = _tcsdup(szClassName);
				m_List.SetItem(&item);
				
				// Style
				lval = ::GetWindowLongPtr(hwnd, GWL_STYLE);
				_stprintf_s(szClassName, _T("0x%.8x"), (int)lval);
				item.iSubItem = 3;
				item.pszText = _tcsdup(szClassName);
				m_List.SetItem(&item);

				// ex style
				lval = ::GetWindowLongPtr(hwnd, GWL_EXSTYLE);
				_stprintf_s(szClassName, _T("0x%.8x"), (int)lval);
				item.iSubItem = 4;
				item.pszText = _tcsdup(szClassName);
				m_List.SetItem(&item);

			}

}