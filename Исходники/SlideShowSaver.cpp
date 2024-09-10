void
SlideShowSaver::Draw(BView *view, int32 frame)
{
	fLock.Lock();

	view->SetLowColor(0, 0, 0);
	view->SetHighColor(192, 192, 192);
	view->SetViewColor(192, 192, 192);

	bool bResult = false;
	if (fNewDirectory == true) {
		// Already have a bitmap on the first frame
		bResult = true;
	} else {
		bResult = ShowNextImage(true, false);
		// try rewinding to beginning
		if (bResult == false)
			bResult = ShowNextImage(true, true);
	}
	fNewDirectory = false;

	if (bResult == true && fBitmap != NULL) {
		BRect destRect(0, 0, fBitmap->Bounds().Width(), fBitmap->Bounds().Height()),
			vwBounds = view->Bounds();

		if (destRect.Width() < vwBounds.Width()) {
			destRect.OffsetBy((vwBounds.Width() - destRect.Width()) / 2, 0);
		}
		if (destRect.Height() < vwBounds.Height()) {
			destRect.OffsetBy(0, (vwBounds.Height() - destRect.Height()) / 2);
		}

		BRect border = destRect, bounds = view->Bounds();
		// top
		view->FillRect(BRect(0, 0, bounds.right, border.top-1), B_SOLID_LOW);
		// left
		view->FillRect(BRect(0, border.top, border.left-1, border.bottom), B_SOLID_LOW);
		// right
		view->FillRect(BRect(border.right+1, border.top, bounds.right, border.bottom), B_SOLID_LOW);
		// bottom
		view->FillRect(BRect(0, border.bottom+1, bounds.right, bounds.bottom), B_SOLID_LOW);

		if (fShowBorder == true) {
			BRect strokeRect = destRect;
			strokeRect.InsetBy(-1, -1);
			view->StrokeRect(strokeRect);
		}

		view->DrawBitmap(fBitmap, fBitmap->Bounds(), destRect);

		if (fShowCaption == true)
			DrawCaption(view);
	}

	fLock.Unlock();
}