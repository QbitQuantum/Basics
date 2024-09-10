void CSampleDlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	__super::OnRButtonDown(nFlags,point);

	//构造菜单
	CSkinMenu MainMenu;
	MainMenu.CreatePopupMenu();

	MainMenu.AppendMenu(4000,TEXT("子节点"),0,0,MF_POPUP);
	MainMenu.AppendMenu(4001,TEXT("子节点"),TEXT("Res\\Button\\message.png"));

 	MainMenu.SetMenuBarImage(TEXT("Res\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
 	MainMenu.SetMenuBackImage(TEXT("Res\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
 	MainMenu.SetMenuHovenImage(TEXT("Res\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
 	MainMenu.SetSeparatorImage(TEXT("Res\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
 	MainMenu.SetCheckImage(TEXT("Res\\Menu\\menu_check.png"));
 	MainMenu.SetArrowImage(TEXT("Res\\Menu\\menu_arrow.png"));

	//MainMenu.SetFrameColor(RGB(255,0,0));
	//显示菜单
	MainMenu.TrackPopupMenu(this);
}