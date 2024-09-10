void toggleHexEdit(void)
{
    GetShortCuts(nppData._nppHandle);
	pCurHexEdit->doDialog(TRUE);
	DialogUpdate();
	setMenu();
}