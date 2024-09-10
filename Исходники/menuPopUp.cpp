MenuPopUp::MenuPopUp(std::string text) : Label(text, 0, 0, 0, 0)
{
	hwnd = (HWND)CreatePopupMenu();
}