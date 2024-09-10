static void
on_right_click(NMITEMACTIVATE *note)
{
	enum MenuOption {
		PRIVATE_CHAT = 1,
		IGNORE_USER,
		ALIAS
	};

	HMENU menu;
	LVITEM item;
	User *user;
	enum MenuOption menu_option;

	if (note->iItem < 0)
		return;

	item.mask = LVIF_PARAM;
	item.iItem = note->iItem;
	SendMessage(note->hdr.hwndFrom, LVM_GETITEM, 0, (intptr_t)&item);
	user = (User *)item.lParam;

	menu = CreatePopupMenu();
	AppendMenu(menu, 0, PRIVATE_CHAT, L"Private chat");
	AppendMenu(menu, user->ignore ? MF_CHECKED : 0, IGNORE_USER, L"Ignore");
	AppendMenu(menu, 0, ALIAS, L"Set alias");
	SetMenuDefaultItem(menu, 1, 0);
	ClientToScreen(note->hdr.hwndFrom, &note->ptAction);
	menu_option = TrackPopupMenuEx(menu, TPM_RETURNCMD, note->ptAction.x,
	    note->ptAction.y, GetParent(note->hdr.hwndFrom), NULL);
	DestroyMenu(menu);

	switch (menu_option) {

	case PRIVATE_CHAT:
		ChatTab_focus_private(user);
		return;

	case IGNORE_USER:
		user->ignore = !user->ignore;
		return;

	case ALIAS: {
		char title[128];
		char buf[MAX_NAME_LENGTH_NUL];

		sprintf(title, "Set alias for %s", user->name);
		if (!GetTextDialog_create(title, strcpy(buf, UNTAGGED_NAME(user->name)), MAX_NAME_LENGTH_NUL))
			strcpy(user->alias, buf);
		return;
	}
	}
}