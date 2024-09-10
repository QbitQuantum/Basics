DesktopWindow* OpWindowList::GetDesktopWindowByPosition(INT32 pos)
{
	DesktopWindowCollectionItem* item =
			static_cast<DesktopWindowCollectionItem*>(GetItemByPosition(pos));
	return item ? item->GetDesktopWindow() : 0;
}