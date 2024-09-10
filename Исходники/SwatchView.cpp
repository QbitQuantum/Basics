BBitmap* SwatchView::make_bitmap(void)
{
	BRect rect(0.0, 0.0, 12.0, 12.0);
	
	BBitmap *bitmap = new BBitmap(rect, B_RGB32, true);
	BView *view = new BView(rect, "", B_FOLLOW_NONE, B_WILL_DRAW);

	bitmap->Lock();

	bitmap->AddChild(view);

	view->SetDrawingMode(B_OP_ALPHA);
	view->SetHighColor(m_color);
	view->FillRect(rect);
	
	view->SetDrawingMode(B_OP_COPY);
	view->SetHighColor(0, 0, 0, 255);
	view->StrokeRect(rect);
	view->Sync();

	bitmap->RemoveChild(view);
	delete view;

	bitmap->Unlock();
	
	return bitmap;
}