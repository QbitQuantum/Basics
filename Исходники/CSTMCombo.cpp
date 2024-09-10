/*! Comment       : 
//******************************************************************/
void CCSTMCombo::DrawTransParentBitmap(CDC* pDC, CRect rect, HBITMAP hBitmap, long crTrans)
{
	// Create two memory dcs for the image and the mask
	CDC dcImage, dcTrans;
	dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);
	// Select the image into the appropriate dc
	CBitmap* pOldBmp = (CBitmap*)dcImage.SelectObject(CBitmap::FromHandle(hBitmap));

	// Create the mask bitmap
	CBitmap bitmapTrans;
	// get the image dimensions
	BITMAP bm = {NULL};
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
	int nWidth	= bm.bmWidth;
	int nHeight = bm.bmHeight;
	bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);

	// Select the mask bitmap into the appropriate dc
	CBitmap* pOldTransBmp = (CBitmap*)dcTrans.SelectObject(&bitmapTrans);

	// Build mask based on transparent colour
	dcImage.SetBkColor(crTrans);
	dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);

	// Do the work - True Mask method - cool if not actual display
//	pDC->BitBlt(xPos, yPos, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
//	pDC->BitBlt(xPos, yPos, nWidth, nHeight, &dcTrans, 0, 0, SRCAND);
//	pDC->BitBlt(xPos, yPos, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcImage,0,0,nWidth,nHeight,SRCCOPY);
//	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcImage,0,0,nWidth,nHeight,SRCAND);
//	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcImage,0,0,nWidth,nHeight,SRCINVERT);

	// Restore settings
	// don't delete this, since it is the bitmap
	dcImage.SelectObject(pOldBmp);
	dcTrans.SelectObject(pOldTransBmp);
	// delete bitmapTrans
	bitmapTrans.DeleteObject();
	// clean up
	dcImage.DeleteDC();
	dcTrans.DeleteDC();
////////////////////////////////////////////////////////////////////////////////////////////
}