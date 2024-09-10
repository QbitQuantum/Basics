void CTaskSwitcher32Dlg::FilterList()
{
	m_windowList2.DeleteAllItems();

	window_list *list = window_item::get_window_list();
	CImageList *pImageList = new CImageList(); pImageList->Create( 16, 16, ILC_COLOR32 | ILC_MASK | ILC_PERITEMMIRROR, 0, 10);

	m_windowList2.SetImageList( pImageList, LVSIL_SMALL);
	int default_idx = pImageList->Add( m_hIcon );
		
	for ( unsigned int i = 0; i < list->size(); i++ )
	{
		window_item *item = (*list)[i];
		bool ok = true;
		if ( this->search.length() > 0 )
		{
			int pos = item->get_lower_title().find( this->search ) ; 
			int pos2 = item->get_process_name().find( this->search );
			if ( pos == std::string::npos && pos2 == std::string::npos ) 
				ok = false;
		}
		if ( ok )
		{
			HWND hwnd = item->get_handle();
			HICON hIcon = NULL;
 
			SendMessageTimeout(hwnd, WM_GETICON, ICON_BIG, 0, SMTO_ABORTIFHUNG, 1000, (LPDWORD)&hIcon);
			if (!hIcon) SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL2, 0, SMTO_ABORTIFHUNG, 1000, (LPDWORD)&hIcon);
 			if (!hIcon) SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL, 0, SMTO_ABORTIFHUNG, 1000, (LPDWORD)&hIcon);
            if (!hIcon) hIcon = (HICON)GetClassLong(hwnd, GCL_HICON);
            if (!hIcon) hIcon = (HICON)GetClassLong(hwnd, GCL_HICONSM);
        
		
			int imageidx = -1;
			if ( hIcon != NULL )
			{
				HICON iconCopy = CopyIcon( hIcon );				
				imageidx = pImageList->Add( iconCopy );
				DestroyIcon( iconCopy );
			}
			else
			{
				imageidx = 1;
			}
			int idx = m_windowList2.InsertItem( 0, item->get_title().c_str(), imageidx );
			m_windowList2.SetItem(  idx, 1, LVIF_TEXT | LVIF_IMAGE, item->get_process_name().c_str(), imageidx, 0, 0, 0 );
			m_windowList2.SetItemData( idx, (DWORD_PTR) item );
			
		}
	}
	m_windowList2.SetItemState( 0, LVIS_SELECTED, LVIS_SELECTED );
	m_windowList2.SetSelectionMark( 0 );

}