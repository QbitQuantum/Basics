int CMyFrameWnd::OnCreate( LPCREATESTRUCT lpCreateStruct)
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	SetMenu(&menu);
	return CFrameWnd::OnCreate(lpCreateStruct);
}