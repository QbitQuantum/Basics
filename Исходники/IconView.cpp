void
IconView::MouseMoved(BPoint where, uint32 transit, const BMessage* dragMessage)
{
	if (fTracking && !fDragging && fIcon != NULL
		&& (abs((int32)(where.x - fDragPoint.x)) > 3
			|| abs((int32)(where.y - fDragPoint.y)) > 3)) {
		// Start drag
		BMessage message(B_SIMPLE_DATA);

		::Icon* icon = fIconData;
		if (fHasRef || fHasType) {
			icon = new ::Icon;
			if (fHasRef)
				icon->SetTo(fRef, fType.Type());
			else if (fHasType)
				icon->SetTo(fType);
		}

		icon->CopyTo(message);

		if (icon != fIconData)
			delete icon;

		BBitmap *dragBitmap = new BBitmap(fIcon->Bounds(), B_RGBA32, true);
		dragBitmap->Lock();
		BView *view
			= new BView(dragBitmap->Bounds(), B_EMPTY_STRING, B_FOLLOW_NONE, 0);
		dragBitmap->AddChild(view);

		view->SetHighColor(B_TRANSPARENT_COLOR);
		view->FillRect(dragBitmap->Bounds());
		view->SetBlendingMode(B_CONSTANT_ALPHA, B_ALPHA_COMPOSITE);
		view->SetDrawingMode(B_OP_ALPHA);
		view->SetHighColor(0, 0, 0, 160);
		view->DrawBitmap(fIcon);

		view->Sync();
		dragBitmap->Unlock();

		DragMessage(&message, dragBitmap, B_OP_ALPHA,
			fDragPoint - BitmapRect().LeftTop(), this);
		fDragging = true;
		SetMouseEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
	}

	if (dragMessage != NULL && !fDragging && AcceptsDrag(dragMessage)) {
		bool dropTarget = transit == B_ENTERED_VIEW || transit == B_INSIDE_VIEW;
		if (dropTarget != fDropTarget) {
			fDropTarget = dropTarget;
			Invalidate();
		}
	} else if (fDropTarget) {
		fDropTarget = false;
		Invalidate();
	}
}