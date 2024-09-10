/**
 *	@brief	Makes specified item selected.
 *	@param[in]	index	item index. if this is -1, no item is selected.
 */
void BeListViewAdapter::SetSelectedItem(SInt32 index)
{
	BListView* listView = getListView();
	int32 current = listView->CurrentSelection(0);
	if (current != index)
	{
		listView->DeselectAll();
		listView->Select(index);
	}
}