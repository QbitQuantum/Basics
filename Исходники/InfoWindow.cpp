void
LeftView::Draw(BRect updateRect)
{
	float right = Bounds().Width() - kSmallHMargin;
	BRect iconRect(right - 31.0, kSmallVMargin, right, kSmallVMargin + 31.0);
	if (updateRect.Intersects(iconRect)) {
		SetDrawingMode(B_OP_OVER);
		DrawBitmap(fIcon, iconRect);
	}
}