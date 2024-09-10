void CFriendListCtrl::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CTitleMenu ClientMenu;
	ClientMenu.CreatePopupMenu();
	ClientMenu.AddMenuTitle(GetResString(IDS_FRIENDLIST), true);

	const CFriend* cur_friend = NULL;
	int iSel = GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED);
	if (iSel != -1) {
		cur_friend = (CFriend*)GetItemData(iSel);
		ClientMenu.AppendMenu(MF_STRING,MP_DETAIL, GetResString(IDS_SHOWDETAILS), _T("CLIENTDETAILS"));
		ClientMenu.SetDefaultItem(MP_DETAIL);
	}

	ClientMenu.AppendMenu(MF_STRING, MP_ADDFRIEND, GetResString(IDS_ADDAFRIEND), _T("ADDFRIEND"));
	ClientMenu.AppendMenu(MF_STRING | (cur_friend ? MF_ENABLED : MF_GRAYED), MP_REMOVEFRIEND, GetResString(IDS_REMOVEFRIEND), _T("DELETEFRIEND"));
	ClientMenu.AppendMenu(MF_STRING | (cur_friend ? MF_ENABLED : MF_GRAYED), MP_MESSAGE, GetResString(IDS_SEND_MSG), _T("SENDMESSAGE"));
	ClientMenu.AppendMenu(MF_STRING | ((cur_friend==NULL || (cur_friend && cur_friend->GetLinkedClient(true) && !cur_friend->GetLinkedClient(true)->GetViewSharedFilesSupport())) ? MF_GRAYED : MF_ENABLED), MP_SHOWLIST, GetResString(IDS_VIEWFILES) , _T("VIEWFILES"));
	ClientMenu.AppendMenu(MF_STRING, MP_FRIENDSLOT, GetResString(IDS_FRIENDSLOT), _T("FRIENDSLOT"));
	ClientMenu.AppendMenu(MF_STRING | (GetItemCount() > 0 ? MF_ENABLED : MF_GRAYED), MP_FIND, GetResString(IDS_FIND), _T("Search"));

    ClientMenu.EnableMenuItem(MP_FRIENDSLOT, (cur_friend)?MF_ENABLED : MF_GRAYED);
	ClientMenu.CheckMenuItem(MP_FRIENDSLOT, (cur_friend && cur_friend->GetFriendSlot()) ? MF_CHECKED : MF_UNCHECKED);
	// MORPH START - Modified by Commander, Friendlinks [emulEspaa] - added by zz_fly
	ClientMenu.AppendMenu(MF_SEPARATOR);
    ClientMenu.AppendMenu(MF_STRING | (theApp.IsEd2kFriendLinkInClipboard() ? MF_ENABLED : MF_GRAYED), MP_PASTE, GetResString(IDS_PASTE), _T("PASTELINK"));
	ClientMenu.AppendMenu(MF_STRING | (cur_friend ? MF_ENABLED : MF_GRAYED), MP_GETFRIENDED2KLINK, GetResString(IDS_GETFRIENDED2KLINK), _T("ED2KLINK"));
	ClientMenu.AppendMenu(MF_STRING | (cur_friend ? MF_ENABLED : MF_GRAYED), MP_GETHTMLFRIENDED2KLINK, GetResString(IDS_GETHTMLFRIENDED2KLINK), _T("ED2KLINK"));
	// MORPH END - Modified by Commander, Friendlinks [emulEspaa]

	// - show requested files (sivka/Xman)
	ClientMenu.AppendMenu(MF_SEPARATOR); 
	ClientMenu.AppendMenu(MF_STRING | (cur_friend && cur_friend->GetLinkedClient() ? MF_ENABLED : MF_GRAYED),MP_LIST_REQUESTED_FILES, GetResString(IDS_LISTREQUESTED), _T("FILEREQUESTED")); 
	//Xman end

	GetPopupMenuPos(*this, point);
	ClientMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	VERIFY( ClientMenu.DestroyMenu() ); // XP Style Menu [Xanatos] - Stulle
}