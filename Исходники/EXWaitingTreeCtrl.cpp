void EXWaitingTreeCtrl::PopulateRoot()
{
	PreExpandItem(TVI_ROOT);
	ExpandItem(TVI_ROOT);
	// force update, don't scroll
	SetRedraw(FALSE);
	SCROLLINFO si;
	GetScrollInfo(SB_HORZ, &si);
	EnsureVisible(GetChildItem(TVI_ROOT));
	SetScrollInfo(SB_HORZ, &si, FALSE);
	SetRedraw();
}