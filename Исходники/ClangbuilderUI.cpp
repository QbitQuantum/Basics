int WindowMessageRunLoop()
{
	INITCOMMONCONTROLSEX info = { sizeof(INITCOMMONCONTROLSEX),
		ICC_TREEVIEW_CLASSES | ICC_COOL_CLASSES | ICC_LISTVIEW_CLASSES };
	InitCommonControlsEx(&info);
	MainWindow window;
	MSG msg;
	window.InitializeWindow();
	window.ShowWindow(SW_SHOW);
	window.UpdateWindow();
	while (GetMessage(&msg, nullptr, 0, 0)>0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}