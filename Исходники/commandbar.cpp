void wxGISMenu::MoveCommandLeft(size_t nIndex)
{
	wxMenuItem *pMenuItem = Remove(FindItemByPosition(nIndex));
	Insert(nIndex - 1, pMenuItem);
	wxGISCommandBar::MoveCommandLeft(nIndex);
}