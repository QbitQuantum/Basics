bool
RecentItemsMenu::StartBuildingItemList()
{
	// remove any preexisting items
	int32 itemCount = CountItems();
	while (itemCount--)
		delete RemoveItem((int32)0);

	fCount = 0;
	fSanityCount = 0;
	fIterator->Rewind();

	return true;
}