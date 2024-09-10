void
TouchpadView::DrawSliders()
{
	BView* view;
	if (fOffScreenView != NULL)
		view = fOffScreenView;
	else
		view = this;

	if (!LockLooper())
		return;

	if (fOffScreenBitmap->Lock()) {
		view->SetHighColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		view->FillRect(Bounds());
		view->SetHighColor(100, 100, 100);
		view->FillRoundRect(fPadRect, 4, 4);

		int32 dragSize = 3; // half drag size

		// scroll areas
		view->SetHighColor(145, 100, 100);
		BRect rightRect(fPadRect.left + fXScrollRange,  fPadRect.top,
			fPadRect.right, fPadRect.bottom);
		view->FillRoundRect(rightRect, 4, 4);

		BRect bottomRect(fPadRect.left, fPadRect.top + fYScrollRange,
			fPadRect.right, fPadRect.bottom);
		view->FillRoundRect(bottomRect, 4, 4);

		// Stroke Rect
		view->SetHighColor(100, 100, 100);
		view->SetPenSize(2);
		view->StrokeRoundRect(fPadRect, 4, 4);

		// x scroll range line
		view->SetHighColor(200, 0, 0);
		view->StrokeLine(BPoint(fPadRect.left + fXScrollRange, fPadRect.top),
			BPoint(fPadRect.left + fXScrollRange, fPadRect.bottom));

		fXScrollDragZone = BRect(fPadRect.left + fXScrollRange - dragSize,
			fPadRect.top - dragSize, fPadRect.left + fXScrollRange + dragSize,
			fPadRect.bottom + dragSize);
		fXScrollDragZone1 = BRect(fPadRect.left + fXScrollRange - dragSize,
			fPadRect.top - dragSize, fPadRect.left + fXScrollRange + dragSize,
			fPadRect.top + dragSize);
		view->FillRect(fXScrollDragZone1);
		fXScrollDragZone2 = BRect(fPadRect.left + fXScrollRange - dragSize,
			fPadRect.bottom - dragSize,
			fPadRect.left + fXScrollRange + dragSize,
			fPadRect.bottom + dragSize);
		view->FillRect(fXScrollDragZone2);

		// y scroll range line
		view->StrokeLine(BPoint(fPadRect.left, fPadRect.top + fYScrollRange),
			BPoint(fPadRect.right, fPadRect.top  + fYScrollRange));

		fYScrollDragZone = BRect(fPadRect.left - dragSize,
			fPadRect.top + fYScrollRange - dragSize,
			fPadRect.right  + dragSize,
			fPadRect.top + fYScrollRange + dragSize);
		fYScrollDragZone1 = BRect(fPadRect.left - dragSize,
			fPadRect.top + fYScrollRange - dragSize, fPadRect.left  + dragSize,
			fPadRect.top + fYScrollRange + dragSize);
		view->FillRect(fYScrollDragZone1);
		fYScrollDragZone2 = BRect(fPadRect.right - dragSize,
			fPadRect.top + fYScrollRange - dragSize, fPadRect.right  + dragSize,
			fPadRect.top + fYScrollRange + dragSize);
		view->FillRect(fYScrollDragZone2);

		fOffScreenView->Sync();
		fOffScreenBitmap->Unlock();
		DrawBitmap(fOffScreenBitmap, B_ORIGIN);
	}

	UnlockLooper();
}