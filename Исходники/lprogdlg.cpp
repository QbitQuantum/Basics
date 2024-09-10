///////////////////////////////////////////////////////////////
// TLevelProgressDialog
// --------------------
//
void DrawIconicGauge(TDC &dc, int yPosition, int Width, int Height, int Value)
{
	TBrush BleueBrush(TColor(0,0,255));
	TPen BleuePen (TColor(0,0,255));
	// TBrush GrayBrush (TColor(200,200,200));
	TPen WhitePen (TColor(255,255,255));
	TPen GrayPen (TColor(100,100,100));
	// TPen GrayPen (TColor(0,0,0));

	// Draw upper left white border
	dc.SelectObject(GrayPen);
	dc.MoveTo(0, yPosition + Height - 1);
	dc.LineTo(0, yPosition);
	dc.LineTo(Width - 1, yPosition);

	// Draw lower right border
	dc.SelectObject(WhitePen);
	dc.LineTo(Width - 1, yPosition + Height - 1);
	dc.LineTo(0, yPosition + Height - 1);

	// Draw gauge
	dc.SelectObject(BleueBrush);
	dc.SelectObject(BleuePen);
	dc.Rectangle(1, yPosition + 1, (Width - 1) * Value / 100, yPosition + Height - 1);

	dc.RestoreObjects();
}