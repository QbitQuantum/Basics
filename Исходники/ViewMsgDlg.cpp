void CViewMsgDlg::OnMenuQuickReply() 
{
#define IDM_QUICK_REPLY	1000
	
	CMenu menu;
	menu.CreatePopupMenu();

	IcqOption &options = icqLink->options;
	StrList l;
	IcqDB::loadQuickReply(l);
	StrList::iterator it;
	UINT id = IDM_QUICK_REPLY;

	CString str;
	for (it = l.begin(); it != l.end(); ++it) {
		CString str = (*it).c_str();
		if (str.GetLength() > 20)
			str = str.Left(20) + "...";
		menu.AppendMenu(
			str == options.quickReplyText.c_str() ? MF_CHECKED : MF_UNCHECKED,
			id++, str);
	}
	str.LoadString(IDS_QUICK_REPLY_SETTING);
	menu.AppendMenu(MF_STRING, id++, str);

	CRect rc;
	GetDlgItem(IDC_MENU_QUICK_REPLY)->GetWindowRect(rc);
	id = menu.TrackPopupMenu(TPM_RETURNCMD, rc.left, rc.bottom, this);
	if (id == 0)
		return;

	id -= IDM_QUICK_REPLY;
	if (id == menu.GetMenuItemCount() - 1)
		((CIcqDlg *) AfxGetMainWnd())->showOptions(1);
	else {
		int i = 0;
		for (it = l.begin(); it != l.end() && i < id; ++it, ++i)
			;
		if (it != l.end()) {
			options.quickReplyText = *it;
			IcqDB::saveOptions(options);
			OnQuickReply();
		}
	}
}