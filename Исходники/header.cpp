void THeaderView::Draw(BRect where)
{
	BRect	r;

	r = Window()->Bounds();
	if (!fWidth)
		fWidth = r.Width();

	r.OffsetTo(0, 0);
	if (fIncoming)
		r.bottom = MIN_HEADER_HEIGHT;
	else
		r.bottom = HEADER_HEIGHT;
	SetHighColor(255, 255, 255);
	StrokeLine(BPoint(r.left, r.top), BPoint(r.right, r.top));
	StrokeLine(BPoint(r.left, r.top), BPoint(r.left, r.bottom - 1));
	SetHighColor(120, 120, 120);
	StrokeLine(BPoint(r.left, r.bottom - 1), BPoint(r.right, r.bottom - 1));
	StrokeLine(BPoint(r.right, r.bottom - 1), BPoint(r.right, r.top + 1));
	SetHighColor(64, 64, 64);
	StrokeLine(BPoint(r.left, r.bottom), BPoint(r.right, r.bottom));

	SetHighColor(255, 255, 255);
	r = ((BTextView *)(fSubject->ChildAt(0)))->Frame();
	fSubject->ConvertToParent(&r);
	r.left -= 3;
	r.right += 3;
	r.top -= 3;
	if (r.Intersects(where)) {
		StrokeLine(BPoint(r.left, r.bottom + 2),
				   BPoint(r.right, r.bottom + 2));
		StrokeLine(BPoint(r.right, r.bottom + 1),
				   BPoint(r.right, r.top));
	}

	r = ((BTextView *)(fTo->ChildAt(0)))->Frame();
	fTo->ConvertToParent(&r);
	r.left -= 3;
	r.right += 3;
	r.top -= 3;
	if (r.Intersects(where)) {
		StrokeLine(BPoint(r.left, r.bottom + 2),
				   BPoint(r.right, r.bottom + 2));
		StrokeLine(BPoint(r.right, r.bottom + 1),
				   BPoint(r.right, r.top));
	}

	if (!fIncoming) {
		r = ((BTextView *)(fCc->ChildAt(0)))->Frame();
		fCc->ConvertToParent(&r);
		r.left -= 3;
		r.right += 3;
		r.top -= 3;
		if (r.Intersects(where)) {
			StrokeLine(BPoint(r.left, r.bottom + 2),
					   BPoint(r.right, r.bottom + 2));
			StrokeLine(BPoint(r.right, r.bottom + 1),
					   BPoint(r.right, r.top));
		}

		r = ((BTextView *)(fBcc->ChildAt(0)))->Frame();
		fBcc->ConvertToParent(&r);
		r.left -= 3;
		r.right += 3;
		r.top -= 3;
		if (r.Intersects(where)) {
			StrokeLine(BPoint(r.left, r.bottom + 2),
					   BPoint(r.right, r.bottom + 2));
			StrokeLine(BPoint(r.right, r.bottom + 1),
					   BPoint(r.right, r.top));
		}
	}
}