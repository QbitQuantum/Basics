void
KeyboardLayoutView::Draw(BRect updateRect)
{
	if (fOldSize != BSize(Bounds().Width(), Bounds().Height())) {
		_InitOffscreen();
		_LayoutKeyboard();
	}

	BView* view;
	if (fOffscreenBitmap != NULL) {
		view = fOffscreenView;
		view->LockLooper();
	} else
		view = this;

	// Draw background

	if (Parent())
		view->SetLowColor(Parent()->ViewColor());
	else
		view->SetLowColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	view->FillRect(updateRect, B_SOLID_LOW);

	// Draw keys

	for (int32 i = 0; i < fLayout->CountKeys(); i++) {
		Key* key = fLayout->KeyAt(i);

		_DrawKey(view, updateRect, key, _FrameFor(key),
			_IsKeyPressed(key->code));
	}

	// Draw LED indicators

	for (int32 i = 0; i < fLayout->CountIndicators(); i++) {
		Indicator* indicator = fLayout->IndicatorAt(i);

		_DrawIndicator(view, updateRect, indicator, _FrameFor(indicator->frame),
			(fModifiers & indicator->modifier) != 0);
	}

	if (fOffscreenBitmap != NULL) {
		view->Sync();
		view->UnlockLooper();

		DrawBitmapAsync(fOffscreenBitmap, BPoint(0, 0));
	}
}