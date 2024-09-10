void CSkinHeaderCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect					rect, rectItem, clientRect;

	GetClientRect(&rect);
	GetClientRect(&clientRect);

	CMemDC					memDC(&dc, rect);
	CDC						bitmapDC;

	bitmapDC.CreateCompatibleDC(&dc);
	
	memDC.FillSolidRect(&rect, RGB(76,85,118));

	CBitmap					bitmapSpan;

	bitmapSpan.LoadBitmap(IDB_COLUMNHEADER_SPAN);

	CBitmap					*pOldBitmapSpan = bitmapDC.SelectObject(&bitmapSpan);

	memDC.StretchBlt(2, 0, rect.Width(), 40, &bitmapDC, 0, 0, 1, 40, SRCCOPY);

	bitmapDC.SelectObject(pOldBitmapSpan);
	bitmapSpan.DeleteObject();
	
	int						nItems = GetItemCount();

	CBitmap					bitmap3;
	
	bitmap3.LoadBitmap(IDB_COLUMNHEADER_END);

	for(int i = 0; i <nItems; i++)
	{		
		TCHAR					buf1[256];
		HD_ITEM					hditem1;
		
		hditem1.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		hditem1.pszText = buf1;
		hditem1.cchTextMax = 255;

		GetItem(i, &hditem1);
		
		GetItemRect(i, &rect);
		
/*		CBitmap* pOldBitmap = NULL;
		
		//make sure we draw the start piece
		//on the first item so it has a left border

		//For the following items we will just use the
		//right border of the previous items as the left
		//border
		if(hditem1.iOrder==0)
		{
			pOldBitmap = bitmapDC.SelectObject(&bitmap);
			memDC.BitBlt(rect.left,rect.top,2,12,&bitmapDC,0,0,SRCCOPY);
		}
		else
		{
			memDC.BitBlt(rect.left-1,rect.top,2,12,&bitmapDC,0,0,SRCCOPY);
			pOldBitmap = bitmapDC.SelectObject(&bitmap2);
			memDC.BitBlt(rect.left+1,rect.top,1,12,&bitmapDC,0,0,SRCCOPY);
		}

		bitmapDC.SelectObject(pOldBitmap);
		
		//span the bitmap for the width of the column header item
		int nWidth = rect.Width() - 4;
		
		CBitmap* pOldBitmap2 = bitmapDC.SelectObject(&bitmap2);
		
		memDC.StretchBlt(rect.left+2, 0, nWidth, 1, &bitmapDC, 0,0, 1, 12, SRCCOPY);

		bitmapDC.SelectObject(pOldBitmap2);
*/		
		
		//draw the end piece of the column header
		CBitmap					*pOldBitmap3 = bitmapDC.SelectObject(&bitmap3);

		//memDC.BitBlt((rect.right - 2), 0, 2, 12, &bitmapDC, 0, 0, SRCCOPY);
		memDC.StretchBlt((rect.right-1), 0, 2, 40, &bitmapDC, 0, 0,2,40, SRCCOPY);

		bitmapDC.SelectObject(pOldBitmap3);
		
		//Get all the info for the current
		//item so we can draw the text to it
		//in the desired font and style
		DRAWITEMSTRUCT			DrawItemStruct;

		GetItemRect(i, &rectItem);
				
		DrawItemStruct.CtlType = 100;
		DrawItemStruct.hDC = dc.GetSafeHdc();
		DrawItemStruct.itemAction = ODA_DRAWENTIRE; 
		DrawItemStruct.hwndItem = GetSafeHwnd(); 
		DrawItemStruct.rcItem = rectItem;
		DrawItemStruct.itemID = i;

		DrawItem(&DrawItemStruct);
		
		UINT					uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_TOP |DT_CENTER;
						
		CFont					font;
		LOGFONT					lf;

		memset(&lf, 0, sizeof(LOGFONT));
		
		//폰트의 속성 지정.
		lf.lfHeight = 22;
		lf.lfWeight = FW_BOLD;
		//strcpy(lf.lfFaceName, "Sevenet 7");

		font.CreateFontIndirect(&lf);

		CFont					*def_font = memDC.SelectObject(&font);
		
		memDC.SetBkMode(TRANSPARENT);
		memDC.SetTextColor(RGB(128, 128, 0));

		// 폰트의 세로 맞춤.
		//rectItem.DeflateRect(2, 2, 2, 2);
		rectItem.DeflateRect(2, 2, 2, 2);
		
		TCHAR					buf[256];
		HD_ITEM					hditem;
		
		hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		hditem.pszText = buf;
		hditem.cchTextMax = 255;

		GetItem(DrawItemStruct.itemID, &hditem);

		memDC.DrawText(buf, &rectItem, uFormat);

		memDC.SelectObject(def_font);
		font.DeleteObject();
	}		
}