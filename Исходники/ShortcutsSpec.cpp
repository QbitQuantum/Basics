static BBitmap*
MakeActuatorBitmap(bool lit)
{
	BBitmap* map = new BBitmap(ICON_BITMAP_RECT, ICON_BITMAP_SPACE, true);
	const rgb_color yellow = {255, 255, 0};
	const rgb_color red = {200, 200, 200};
	const rgb_color black = {0, 0, 0};
	const BPoint points[10] = {
		BPoint(8, 0), BPoint(9.8, 5.8), BPoint(16, 5.8),
		BPoint(11, 9.0), BPoint(13, 16), BPoint(8, 11),
		BPoint(3, 16), BPoint(5, 9.0), BPoint(0, 5.8),
		BPoint(6.2, 5.8) };

	BView* view = new BView(BRect(0, 0, 16, 16), NULL, B_FOLLOW_ALL_SIDES, 0L);
	map->AddChild(view);
	map->Lock();
	view->SetHighColor(B_TRANSPARENT_32_BIT);
	view->FillRect(ICON_BITMAP_RECT);
	view->SetHighColor(lit ? yellow : red);
	view->FillPolygon(points, 10);
	view->SetHighColor(black);
	view->StrokePolygon(points, 10);
	map->Unlock();
	map->RemoveChild(view);
	delete view;
	return map;
}