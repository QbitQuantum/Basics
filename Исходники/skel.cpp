int get_menu(HMENU hMenu, int ctrlID)
{
	if (GetMenuState(hMenu,ctrlID,MF_BYCOMMAND)&MF_CHECKED) {
		CheckMenuItem(hMenu,ctrlID,MF_UNCHECKED|MF_BYCOMMAND);
		return 0;
	}
	else {
		CheckMenuItem(hMenu,ctrlID,MF_CHECKED|MF_BYCOMMAND);
		return 1;
	}
}