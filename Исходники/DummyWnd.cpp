void CDummyWnd::OnStopserver() 
{
	CMenu Menu;
	CMenu *pSub;

	Menu.LoadMenu(IDR_MENU);
	pSub = Menu.GetSubMenu(0);

	pSub->EnableMenuItem(ID_STARTSERVER, MF_BYCOMMAND | MF_ENABLED);
	pSub->EnableMenuItem(ID_STOPSERVER, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	KillTimer(0);
}