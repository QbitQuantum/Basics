void CClipboardListBox::OnRButtonUp(UINT nFlags, CPoint point)
{
	const UINT_PTR IDM_SELECTALL = 0x80fb;
	const UINT_PTR IDM_COPY = 0x80fc;
	const UINT_PTR IDM_CLEAR = 0x80fd;
	CMenu menu;
	menu.CreatePopupMenu();
	menu.InsertMenu(0, MF_BYPOSITION|MF_STRING, IDM_SELECTALL, "Select All");
	menu.InsertMenu(1, MF_BYPOSITION|MF_STRING, IDM_COPY, "Copy");
	menu.InsertMenu(2, MF_BYPOSITION|MF_STRING, IDM_CLEAR, "Clear");

	this->ClientToScreen(&point);
	UINT_PTR cmd = menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN|TPM_RETURNCMD, point.x, point.y, this);

	if(IDM_COPY==cmd)
	{
		DoCopy();
	}
	else if(IDM_CLEAR==cmd)
	{
		ResetContent();
	}	
	else if(IDM_SELECTALL==cmd)
	{
		SelectAll();	
	}	
	return;
	//CListBox::OnRButtonUp(nFlags, point);
}