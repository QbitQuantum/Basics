int PropertyWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	propList.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER, rectDummy, this, 0);
	propList.EnableHeaderCtrl(FALSE);
	propList.SetVSDotNetLook();

	return 0;
}