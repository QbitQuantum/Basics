void MenuWindow::MessageReceived(BMessage* message)
{
	switch (message->what) {
	case MSG_WIN_ADD_MENU:
		AddMenu(message);
		break;
	case MSG_WIN_DELETE_MENU:
		DeleteMenu(message);
		break;
	case MSG_TEST_ITEM:
		TestMenu(message);
		break;
	case MSG_USER_ITEM:
		UserMenu(message);
		break;
	case MSG_WIN_HIDE_USER_MENUS:
		ToggleUserMenus(message);
		break;
	case MSG_WIN_LARGE_TEST_ICONS:
		ToggleTestIcons(message);
		break;
	default:
		BWindow::MessageReceived(message);
		break;
	}
}