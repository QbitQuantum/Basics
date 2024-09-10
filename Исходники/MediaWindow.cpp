void
MediaWindow::UpdateOutputListItem(MediaListItem::media_type type,
	const dormant_node_info* node)
{
	NodeListItem compareTo(node, type);
	NodeListItemUpdater updater(&compareTo, &NodeListItem::SetDefaultOutput);
	for (int32 i = 0; i < fListView->CountItems(); i++) {
		MediaListItem* item = static_cast<MediaListItem*>(fListView->ItemAt(i));
		item->Accept(updater);
	}
	fListView->Invalidate();
}