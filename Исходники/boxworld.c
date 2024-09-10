void CheckUndoMenu(HWND hwnd, BOOL bEnable)
{
	bUndo = bEnable;
	EnableMenuItem(GetMenu(hwnd), IDM_UNDO, MF_BYCOMMAND | (bEnable ? MF_ENABLED : MF_GRAYED));
}