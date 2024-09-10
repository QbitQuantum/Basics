void 
BTitleView::Draw(BRect /*updateRect*/, bool useOffscreen, bool updateOnly,
	const BColumnTitle *pressedColumn,
	void (*trackRectBlitter)(BView *, BRect), BRect passThru)
{
	BRect bounds(Bounds());
	BView *view;

	if (useOffscreen) {
		ASSERT(sOffscreen);
		BRect frame(bounds);
		frame.right += frame.left;
			// this is kind of messy way of avoiding being clipped by the ammount the
			// title is scrolled to the left
			// ToDo: fix this
		view = sOffscreen->BeginUsing(frame);
		view->SetOrigin(-bounds.left, 0);
		view->SetLowColor(LowColor());
		view->SetHighColor(HighColor());
		BFont font(be_plain_font);
		font.SetSize(9);
		view->SetFont(&font);
	} else
		view = this;

	if (be_control_look != NULL) {
		rgb_color base = ui_color(B_PANEL_BACKGROUND_COLOR);
		view->SetHighColor(tint_color(base, B_DARKEN_2_TINT));
		view->StrokeLine(bounds.LeftBottom(), bounds.RightBottom());
		bounds.bottom--;

		be_control_look->DrawButtonBackground(view, bounds, bounds, base, 0,
			BControlLook::B_TOP_BORDER | BControlLook::B_BOTTOM_BORDER);
	} else {
		// fill background with light gray background
		if (!updateOnly)
			view->FillRect(bounds, B_SOLID_LOW);
	
		view->BeginLineArray(4);
		view->AddLine(bounds.LeftTop(), bounds.RightTop(), sShadowColor);
		view->AddLine(bounds.LeftBottom(), bounds.RightBottom(), sShadowColor);
		// draw lighter gray and white inset lines
		bounds.InsetBy(0, 1);
		view->AddLine(bounds.LeftBottom(), bounds.RightBottom(), sLightShadowColor);
		view->AddLine(bounds.LeftTop(), bounds.RightTop(), sShineColor);
		view->EndLineArray();
	}

	int32 count = fTitleList.CountItems();
	float minx = bounds.right;
	float maxx = bounds.left;
	for (int32 index = 0; index < count; index++) {
		BColumnTitle *title = fTitleList.ItemAt(index);
		title->Draw(view, title == pressedColumn);
		BRect titleBounds(title->Bounds());
		if (titleBounds.left < minx)
			minx = titleBounds.left;
		if (titleBounds.right > maxx)
			maxx = titleBounds.right;
	}

	if (be_control_look != NULL) {
		bounds = Bounds();
		minx--;
		view->SetHighColor(sLightShadowColor);
		view->StrokeLine(BPoint(minx, bounds.top), BPoint(minx, bounds.bottom - 1));
	} else {
		// first and last shades before and after first column
		maxx++;
		minx--;
		view->BeginLineArray(2);
		view->AddLine(BPoint(minx, bounds.top),
					  BPoint(minx, bounds.bottom), sShadowColor);
		view->AddLine(BPoint(maxx, bounds.top),
					  BPoint(maxx, bounds.bottom), sShineColor);
		view->EndLineArray();
	}

#if !(APP_SERVER_CLEARS_BACKGROUND)
	FillRect(BRect(bounds.left, bounds.top + 1, minx - 1, bounds.bottom - 1), B_SOLID_LOW);
	FillRect(BRect(maxx + 1, bounds.top + 1, bounds.right, bounds.bottom - 1), B_SOLID_LOW);
#endif

	if (useOffscreen) {
		if (trackRectBlitter)
			(trackRectBlitter)(view, passThru);
		view->Sync();
		DrawBitmap(sOffscreen->Bitmap());
		sOffscreen->DoneUsing();
	} else if (trackRectBlitter)
		(trackRectBlitter)(view, passThru);
}