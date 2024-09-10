BOOL PASCAL CInfBam::FitAndCenterBitmap(HBITMAP &hOriginal, COLORREF clrBackground,
	int nWidth, int nHeight)
{
	CBitmap *pBmp = CBitmap::FromHandle(hOriginal);
	if (!pBmp)
		return(FALSE);

	BITMAP bm;
	pBmp->GetBitmap(&bm);
	
	if (bm.bmWidth >= nWidth && bm.bmHeight >= nHeight)
		return(TRUE);

	CDC *pDC = AfxGetMainWnd()->GetDC();
	if (!pDC)
		return(FALSE);

	// DC to use to create the new image.
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);

	// Need to have the original bitmap in a dc to manipulate it.
	CDC dcBmp;
	dcBmp.CreateCompatibleDC(pDC);
	CBitmap *pOldBmp = dcBmp.SelectObject(pBmp);

	// Need a new bitmap in the memory dc to copy onto.
	CBitmap bmpNew;
	bmpNew.CreateCompatibleBitmap(pDC,nWidth,nHeight);
	CBitmap *pOldMemBmp = dcMem.SelectObject(&bmpNew);

	// Erase the surface the background color.
	dcMem.FillSolidRect(0,0,nWidth,nHeight,clrBackground);

	// Find the centered coordinates.
	int nLeft = nWidth/2 - bm.bmWidth/2;
	int nTop = nHeight/2 - bm.bmHeight/2;

	// Copy the smaller original bitmap onto the 32x32 in the cenetered position.
	dcMem.BitBlt(nLeft,nTop,bm.bmWidth,bm.bmHeight,&dcBmp,0,0,SRCCOPY);

	// Select out the bitmaps.
	dcMem.SelectObject(pOldMemBmp);
	dcBmp.SelectObject(pOldBmp);

	AfxGetMainWnd()->ReleaseDC(pDC);

	// Delete the original and point it at the new one.
	pBmp->Detach();
	::DeleteObject(hOriginal);

	hOriginal = (HBITMAP)bmpNew;
	bmpNew.Detach();

	return(TRUE);
}