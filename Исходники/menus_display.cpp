void mDisplayOpen()
{
	setMenuInfo(OPTION_COUNT, PSTR("    < DISPLAY >"), MENU_TYPE_ICON, mSelect, upOption, downOption);

	setMenuOptions();
	setMenuOption_P(OPTION_EXIT, menuBack, menu_exit, back);
	
	setPrevMenuOpen(&prevMenuData, mDisplayOpen);

	beginAnimation2(NULL);
}