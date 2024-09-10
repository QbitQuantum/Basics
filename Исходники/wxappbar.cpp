void WXAppBar::UnSetDockedModeStep2()
{
	// Unregister app bar
	APPBARDATA abd;	
	abd.cbSize= sizeof(APPBARDATA);
	abd.hWnd= (HWND) GetHandle();	
	SHAppBarMessage (ABM_REMOVE, &abd);
}