void CSkinVerticleScrollbar::Draw()
{

	CClientDC dc(this);
	CRect clientRect;
	GetClientRect(&clientRect);
	CMyMemDC memDC(&dc, &clientRect);
	memDC.FillSolidRect(&clientRect,  RGB(74,82,107));
	CDC bitmapDC;
	bitmapDC.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_TOP);
	CBitmap* pOldBitmap = bitmapDC.SelectObject(&bitmap);
	memDC.BitBlt(clientRect.left,clientRect.top,20,17,&bitmapDC,0,0,SRCCOPY);
	bitmapDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	pOldBitmap = NULL;

	bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_UPARROW);
	pOldBitmap = bitmapDC.SelectObject(&bitmap);
	memDC.BitBlt(clientRect.left,clientRect.top+17,20,19,&bitmapDC,0,0,SRCCOPY);
	bitmapDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	pOldBitmap = NULL;
	
	//draw the background (span)
	bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_SPAN);
	pOldBitmap = bitmapDC.SelectObject(&bitmap);
	int nHeight = clientRect.Height() - 37;

	memDC.StretchBlt(clientRect.left, clientRect.top+37, 20,nHeight,&bitmapDC, 0,0, 20, 1, SRCCOPY);

	bitmapDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	pOldBitmap = NULL;
	
	//draw the down arrow of the scrollbar
	bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_DOWNARROW);
	pOldBitmap = bitmapDC.SelectObject(&bitmap);
	memDC.BitBlt(clientRect.left,nHeight,20,16,&bitmapDC,0,0,SRCCOPY);
	bitmapDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	pOldBitmap = NULL;

		//draw the down arrow of the scrollbar
	bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_BOTTOM);
	pOldBitmap = bitmapDC.SelectObject(&bitmap);
	memDC.BitBlt(clientRect.left+1,nHeight+26,20,22,&bitmapDC,0,0,SRCCOPY);
	bitmapDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	pOldBitmap = NULL;

	//If there is nothing to scroll then don't
	//show the thumb control otherwise show it
	if(pList->GetScrollLimit(SB_VERT) != 0)
	{
		//draw the thumb control
		bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_THUMB);
		pOldBitmap = bitmapDC.SelectObject(&bitmap);
		memDC.BitBlt(clientRect.left,clientRect.top+nThumbTop,20,26,&bitmapDC,0,0,SRCCOPY);
		bitmapDC.SelectObject(pOldBitmap);
		bitmap.DeleteObject();
		pOldBitmap = NULL;
	}
}