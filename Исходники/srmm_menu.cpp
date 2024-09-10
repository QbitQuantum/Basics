static int SrmmMenu_ProcessIconClick(WPARAM hContact, LPARAM lParam)
{
	StatusIconClickData *sicd = (StatusIconClickData *)lParam;
	if (lstrcmpA(sicd->szModule, MODULNAME))
		return 0;

	if (!hContact)
		return 0;

	int mode = db_get_b(hContact, MODULNAME, "ShowMode", PU_SHOWMODE_AUTO);

	if (sicd->flags & MBCF_RIGHTBUTTON) {
		HMENU hMenu = CreatePopupMenu();

		AppendMenu(hMenu, MF_STRING, 1+PU_SHOWMODE_AUTO,       TranslateT("Auto"));
		AppendMenu(hMenu, MF_STRING, 1+PU_SHOWMODE_FAVORITE,   TranslateT("Favorite"));
		AppendMenu(hMenu, MF_STRING, 1+PU_SHOWMODE_FULLSCREEN, TranslateT("Ignore fullscreen"));
		AppendMenu(hMenu, MF_STRING, 1+PU_SHOWMODE_BLOCK,      TranslateT("Block"));

		CheckMenuItem(hMenu, 1+mode, MF_BYCOMMAND|MF_CHECKED);

		mode = TrackPopupMenu(hMenu, TPM_RETURNCMD, sicd->clickLocation.x, sicd->clickLocation.y, 0, WindowList_Find(hDialogsList, hContact), NULL);
		if (mode) {
			db_set_b(hContact, MODULNAME, "ShowMode", mode-1);
			SrmmMenu_UpdateIcon(hContact);
		}
	}
	else {
		db_set_b(hContact, MODULNAME, "ShowMode", (mode == PU_SHOWMODE_AUTO) ? PU_SHOWMODE_BLOCK : PU_SHOWMODE_AUTO);
		SrmmMenu_UpdateIcon(hContact);
	}

	return 0;
}