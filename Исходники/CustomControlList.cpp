void CCustomControlList::Draw(CBitmapContext& gc)
	{
	TInt x = iDrawPoint.iX + iDisplayPoint.iX;
	TInt x2 = iDrawPoint.iX + iDisplayPoint.iX + 16;
	TInt y;
	TInt dy = iDrawPoint.iY;
	for (TInt i=0; i<iList->Count(); i++)
		{
		if (dy < 0)
			{
			dy += iRowHeight;
			continue;
			}
		if (dy >= iDisplaySize.iHeight)
			{
			break;
			}
		y = dy + iDisplayPoint.iY;
		pListItemStruct item = (*iList)[i];
		CGulIcon* icon = (*iIcons)[item->iIconIndex];
		CFbsBitmap* bitmap = icon->Bitmap();
		gc.BitBlt(TPoint(x, y), bitmap);

		gc.UseFont(iFont);
		if (i!=iSelectIndex)
			{
			gc.SetPenColor(iTextColor);
			//			HBufC* text = item->iShowName;
			//			gc.DrawText(*(item->iShowName), TPoint(x2, y));
			}
		else
			{
			gc.SetPenColor(iSelectTextColor);
			//			HBufC* text = item->iShowName;
			//			gc.DrawText(*(item->iShowName), TPoint(x2, y));
			}
		y += iFontHeight;
		gc.DrawText(*(item->iShowName), TPoint(x2, y));
		gc.DiscardFont();

		dy += iRowHeight;
		}
	}