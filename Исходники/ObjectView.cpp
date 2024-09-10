// MouseMoved
void
ObjectView::MouseMoved(BPoint where, uint32 transit,
					   const BMessage* dragMessage)
{
//	BRect dirty(where, where);
//	dirty.InsetBy(-10, -10);
//	Invalidate(dirty);
	
if (dragMessage) {
//printf("ObjectView::MouseMoved(BPoint(%.1f, %.1f)) - DRAG MESSAGE\n", where.x, where.y);
//Window()->CurrentMessage()->PrintToStream();
} else {
//printf("ObjectView::MouseMoved(BPoint(%.1f, %.1f))\n", where.x, where.y);
}

	if (fScrolling) {
		BCursor cursor(kGrabCursor);
		SetViewCursor(&cursor);
	
		BPoint offset = fLastMousePos - where;
		ScrollBy(offset.x, offset.y);
		fLastMousePos = where + offset;
	} else if (fInitiatingDrag) {
		BPoint offset = fLastMousePos - where;
		if (sqrtf(offset.x * offset.x + offset.y * offset.y) > 5.0) {
			BMessage newDragMessage('drag');
			BBitmap* dragBitmap = new BBitmap(BRect(0, 0, 40, 40), B_RGBA32,
				true);
			if (dragBitmap->Lock()) {
				BView* helper = new BView(dragBitmap->Bounds(),
					"offscreen view", B_FOLLOW_ALL, B_WILL_DRAW);
				dragBitmap->AddChild(helper);
				helper->SetDrawingMode(B_OP_ALPHA);
				helper->SetBlendingMode(B_CONSTANT_ALPHA, B_ALPHA_COMPOSITE);

				BRect r(helper->Bounds());
				helper->SetHighColor(0, 0, 0, 128);
				helper->StrokeRect(r);

				helper->SetHighColor(200, 200, 200, 100);
				r.InsetBy(1, 1);
				helper->FillRect(r);

				helper->SetHighColor(0, 0, 0, 255);
				const char* text = B_TRANSLATE("Test");
				float pos = (r.Width() - helper->StringWidth(text)) / 2;
				helper->DrawString(text, BPoint(pos, 25));
				helper->Sync();
			}
			
			DragMessage(&newDragMessage, dragBitmap, B_OP_ALPHA, B_ORIGIN,
				this);
			fInitiatingDrag = false;
		}
	} else {
		BCursor cursor(kMoveCursor);
		SetViewCursor(&cursor);
	
		if (fState && fState->IsTracking()) {
			BRect before = fState->Bounds();
	
			fState->MouseMoved(where);
	
			BRect after = fState->Bounds();
			BRect invalid(before | after);
			Invalidate(invalid);
		}
	}
//	SetViewCursor();
}