void ControlEvent::ShowCMenu(CWnd *pcwnd)
{
	LPPOINT lpoint=new tagPOINT;
	::GetCursorPos(lpoint);//得到鼠标位置
	CMenu menu;
	menu.CreatePopupMenu();//声明一个弹出式菜单
	//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已
	//隐藏），将程序结束。
	menu.AppendMenu(MF_STRING,IDR_MYSETTING_MESSAGE,CString("软件设置"));
	menu.AppendMenu(MF_STRING,IDR_MYWEBSITE_MESSAGE,CString("官方网站"));
	menu.AppendMenu(MF_STRING,IDR_MYCLOSE_MESSAGE,CString("关闭退出"));
	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,pcwnd);
	//资源回收
	HMENU hmenu=menu.Detach();
	menu.DestroyMenu();
	delete lpoint;
}