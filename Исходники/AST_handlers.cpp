void SetTaskbarState(int option)
{
	APPBARDATA tbData = APPBARDATA();
	tbData.cbSize = sizeof(tbData);
	tbData.hWnd = FindWindow(TEXT("System_TrayWnd"), 0);
	tbData.lParam = option;
	SHAppBarMessage(ABM_SETSTATE, &tbData);
}