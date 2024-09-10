void GuideWindow::deleteGuide(BMessage *msg)
{
	BStringItem *item = modifyGuide(msg);
	BListView *view = getCurrentListView();
	view->RemoveItem(item);
	view->Select(0);
	view->ScrollToSelection();
}