////////////////////////////////////////////////////////////
// TBitmap256Control
// -----------------
//  Display bitmap in DC
void TBitmap256Control::DisplayBitmap (TDC& dc, TRect &rect)
{
	// Display a cross if no bitmap
	if ( pDIBInfo == 0 )
	{
		dc.SelectObject(TPen(TColor::LtGray));
		dc.MoveTo (0, 0);
		dc.LineTo (MaxWidth, MaxHeight);
		dc.MoveTo (0, MaxHeight);
		dc.LineTo (MaxWidth, 0);
		dc.SetTextAlign(TA_CENTER);
		dc.SetTextColor(TColor::White);
		dc.SetBkColor(TColor::Black);
		char tmp[40];
		if ( BitmapName[0] != '\0' && BitmapName[0] != '-' )
			wsprintf (tmp, "No picture (%s)", BitmapName);
		else
			wsprintf (tmp, "No picture");
		dc.TextOut (MaxWidth / 2, MaxHeight / 2 - 6, tmp);
		return;
	}

	assert (pBitmapPalette != NULL);

	// pBitmapPalette->UnrealizeObject();
	dc.SelectObject (*pBitmapPalette);
	dc.RealizePalette();
	dc.SetStretchBltMode (COLORONCOLOR);

#if 1
	TRect ZoomRect;
	ZoomRect.left   = rect.left;
	ZoomRect.top    = rect.top;
	ZoomRect.right  = rect.right;
	ZoomRect.bottom = rect.bottom;

	// Convert the rect. size to a rect in the sprite
	rect.left   /= ZoomFactor;
	rect.top    /= ZoomFactor;
	rect.right  /= ZoomFactor;
	rect.bottom /= ZoomFactor;

	TRect DIBRect;
	DIBRect.left   = rect.left;
	DIBRect.top    = BitmapYSize - rect.bottom; 	// DIBs are Y inversed
	DIBRect.right  = DIBRect.left + rect.Width();
	DIBRect.bottom = DIBRect.top + rect.Height();

	dc.StretchDIBits (ZoomRect,
					  DIBRect,
					  pDIBits, *pDIBInfo,
					  DIB_PAL_COLORS, SRCCOPY);
#else
	// Create memory DC and display bitmap
	TMemoryDC mdc (dc);
	mdc.SelectObject (*pBitmapPalette);
	mdc.SelectObject (*pBitmap);
	dc.StretchBlt(0, 0, ZoomXSize,   ZoomYSize,
				  mdc,
				  0, 0, BitmapXSize, BitmapYSize,
				  SRCCOPY);

	// Restore GDI objects
	mdc.RestoreBitmap();
	mdc.RestorePalette();
#endif
	dc.RestorePalette();
}