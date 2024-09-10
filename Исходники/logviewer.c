static void create_menu(void) {
	HMENU menu = CreateMenu();
	HMENU file_menu = CreatePopupMenu();
	MENUITEMINFO menu_item_info;

	_view_menu = CreatePopupMenu();

	AppendMenu(menu, MF_STRING | MF_POPUP, (UINT)file_menu, "&File");
	AppendMenu(file_menu, MF_STRING, ID_FILE_SAVE, "&Save...");
	AppendMenu(file_menu, MF_STRING, ID_FILE_EXIT, "&Exit");

	AppendMenu(menu, MF_STRING | MF_POPUP, (UINT)_view_menu, "&View");
	AppendMenu(_view_menu, MF_STRING, ID_VIEW_EVENT, "Windows &Event Log");
	AppendMenu(_view_menu, MF_STRING, ID_VIEW_DEBUG, "Live &Debug Log");

	memset(&menu_item_info, 0, sizeof(menu_item_info));

	menu_item_info.cbSize = sizeof(menu_item_info);
	menu_item_info.fMask = MIIM_FTYPE;
	menu_item_info.fType = MFT_STRING | MFT_RADIOCHECK;

	SetMenuItemInfo(_view_menu, ID_VIEW_EVENT, FALSE, &menu_item_info);

	memset(&menu_item_info, 0, sizeof(menu_item_info));

	menu_item_info.cbSize = sizeof(menu_item_info);
	menu_item_info.fMask = MIIM_FTYPE;
	menu_item_info.fType = MFT_STRING | MFT_RADIOCHECK;

	SetMenuItemInfo(_view_menu, ID_VIEW_DEBUG, FALSE, &menu_item_info);

	SetMenu(_hwnd, menu);
}