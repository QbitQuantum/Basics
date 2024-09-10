/**
	Renders all visible items.
*/
void AlbumView::DrawOffscreen(BView *view, BRect update)
{
	view->SetScale(fZoom);
	AlbumItem *item;
	for (int i = 0; (item = ItemAt(i)); i++) {
 			if (IsItemVisible(item) && update.Intersects(Adjust(item->Frame()))) {
				item->DrawItem(view);
 			}
	}
}