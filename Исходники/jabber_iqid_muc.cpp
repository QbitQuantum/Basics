static void sttFillJidList(HWND hwndDlg)
{
	JABBER_MUC_JIDLIST_INFO *jidListInfo;
	HXML iqNode, queryNode;
	const TCHAR* from, *jid, *reason, *nick;
	LVITEM lvi;
	HWND hwndList;
	int count, i;

	TCHAR *filter = NULL;
	if (GetWindowLongPtr(GetDlgItem(hwndDlg, IDC_FILTER), GWLP_USERDATA))
	{
		int filterLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_FILTER)) + 1;
		filter = (TCHAR *)_alloca(filterLength * sizeof(TCHAR));
		GetDlgItemText(hwndDlg, IDC_FILTER, filter, filterLength);
	}

	jidListInfo = ( JABBER_MUC_JIDLIST_INFO * ) GetWindowLongPtr( hwndDlg, GWLP_USERDATA );
	if ( !jidListInfo )
		return;

	hwndList = GetDlgItem( hwndDlg, IDC_LIST );
	SendMessage(hwndList, WM_SETREDRAW, FALSE, 0);

	count = ListView_GetItemCount( hwndList );
	lvi.mask = LVIF_PARAM;
	lvi.iSubItem = 0;
	for ( i=0; i<count; i++ ) {
		lvi.iItem = i;
		if ( ListView_GetItem( hwndList, &lvi ) == TRUE ) {
			if ( lvi.lParam!=( LPARAM )( -1 ) && lvi.lParam!=( LPARAM )( NULL )) {
				mir_free(( void * ) lvi.lParam );
			}
		}
	}
	ListView_DeleteAllItems( hwndList );

	// Populate displayed list from iqNode
	if (( iqNode = jidListInfo->iqNode ) != NULL ) {
		if (( from = xmlGetAttrValue( iqNode, _T("from"))) != NULL ) {
			if (( queryNode = xmlGetChild( iqNode , "query" )) != NULL ) {
				lvi.mask = LVIF_TEXT | LVIF_PARAM;
				lvi.iSubItem = 0;
				lvi.iItem = 0;
				for ( i=0; ; i++ ) {
					HXML itemNode = xmlGetChild( queryNode ,i);
					if ( !itemNode )
						break;

					if (( jid = xmlGetAttrValue( itemNode, _T("jid"))) != NULL ) {
						lvi.pszText = ( TCHAR* )jid;
						if ( jidListInfo->type == MUC_BANLIST ) {
							if (( reason = xmlGetText(xmlGetChild( itemNode , "reason" ))) != NULL ) {
								TCHAR jidreason[ JABBER_MAX_JID_LEN + 256 ];
								mir_sntprintf( jidreason, SIZEOF( jidreason ), _T("%s (%s)") , jid, reason );
								lvi.pszText = jidreason;
						}	}

						if ( jidListInfo->type == MUC_VOICELIST || jidListInfo->type == MUC_MODERATORLIST ) {
							if (( nick = xmlGetAttrValue( itemNode, _T("nick"))) != NULL ) {
								TCHAR nickjid[ JABBER_MAX_JID_LEN + 256 ];
								mir_sntprintf( nickjid, SIZEOF( nickjid ), _T("%s (%s)") , nick, jid );
								lvi.pszText = nickjid;
						}	}

						if (filter && *filter && !JabberStrIStr(lvi.pszText, filter))
							continue;

						lvi.lParam = ( LPARAM )mir_tstrdup( jid );

						ListView_InsertItem( hwndList, &lvi );
						lvi.iItem++;
	}	}	}	}	}

	lvi.mask = LVIF_PARAM;
	lvi.lParam = ( LPARAM )( -1 );
	ListView_InsertItem( hwndList, &lvi );

	SendMessage(hwndList, WM_SETREDRAW, TRUE, 0);
	RedrawWindow(hwndList, NULL, NULL, RDW_INVALIDATE);
}