VOID CMainWnd::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	DestroyMenu(hCurMenu);//销毁菜单资源
	PostQuitMessage(0);//如果破坏窗体，则退出主线程
	return;
}