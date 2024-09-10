/**
 * Draws the icon for the item to the graphics context aGc, in the middle of the rectangle aRect
 */
EXPORT_C void LafMenuPaneItem::DrawIcon(const MLafEnv& /*aLafEnv*/, const CCoeControl& /*aMenuPane*/, CWindowGc& aGc, const TRect& aRect, const CGulIcon* aIcon, SLafMenuPane::THighlightType aHighlightType)
	{
	if (aIcon)
		{
		if (aHighlightType == SLafMenuPane::EDrawHighlight)
			aGc.SetBrushStyle(CGraphicsContext::ENullBrush);

		// Determine the rect available for the bitmap
		TRect rect = aRect;
		// put the image in the middle of available rect
		const CFbsBitmap* bitmap = aIcon->Bitmap();
		const TSize bmpSize(bitmap->SizeInPixels());
		const TSize rectSize(aRect.Size());
		const TPoint offset(((rectSize.iWidth - bmpSize.iWidth) / 2), ((rectSize.iHeight - bmpSize.iHeight) / 2));
		const CFbsBitmap* mask = aIcon->Mask();
		if (mask)
			{
			const TRect bmpRect(0, 0, bmpSize.iWidth, bmpSize.iHeight);
			aGc.BitBltMasked(rect.iTl+offset, bitmap, bmpRect, mask, ETrue);
			}
		else
			aGc.BitBlt(rect.iTl+offset, bitmap);
		if (aHighlightType == SLafMenuPane::EDrawHighlight)
			aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		}
	}