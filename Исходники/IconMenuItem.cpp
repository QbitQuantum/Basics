void
ModelMenuItem::DrawContent()
{
	if (fDrawText) {
		BPoint drawPoint(ContentLocation());
		drawPoint.x += 20 + (fExtraPad ? 6 : 0);
		if (fHeightDelta > 0)
			drawPoint.y += ceil(fHeightDelta / 2);
		Menu()->MovePenTo(drawPoint);
		_inherited::DrawContent();
	}
	DrawIcon();
}