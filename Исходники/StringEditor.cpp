bool StringEditorWindow::CreateThis(HWND hParent, u32 windowId)
{
	if ( getHandle() != NULL )
		return SetParent(hParent);

	if ( ClassWindow::RegisterWindowClass(0, NULL, NULL, NULL, NULL, "StringEditor", NULL, false) &&
		 ClassWindow::CreateClassWindow(0, "", WS_VISIBLE|WS_CHILD, 4, 22, 592, 524, hParent, (HMENU)windowId) )
	{
		CreateSubWindows(getHandle());
		RefreshWindow();
		return true;
	}
	else
		return false;
}