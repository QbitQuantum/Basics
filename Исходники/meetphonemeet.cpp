HWND Cmeetphonemeet::AddMeetMember(CString &memberName)
{
	int memberCount = m_ListMember.GetCount();
	Cmeetphonemember *memberDlg = new Cmeetphonemember(this);
	RECT rect;
	GetClientRect(&rect);
	rect.left = rect.right - rect.left - 241;
	rect.top = memberCount * 197;
	rect.bottom = rect.top + 197;
	memberDlg->m_sMemberName = memberName;
	memberDlg->Create(IDD_MEETPHONE_MEMBER,this);
	memberDlg->MoveWindow(&rect);
	memberDlg->ShowWindow(SW_SHOW);
	m_ListMember.AddTail(memberDlg);
	return memberDlg->m_hWnd;
}