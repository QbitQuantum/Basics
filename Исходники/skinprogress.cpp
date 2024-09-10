BOOL CSkinProgress::SetBitmap(
	CBitmap *pTempBitmap,
	BOOL bDisplay)
{ 
	BITMAP sBmpSrc;
	HBITMAP hOldBitmap;
	HBITMAP hOldStretch;
	CRect WndRect;
	CDC BmpDC;
	CDC StretchDC;

	mPaintRect.SetRect(0, 0, 0, 0);

	GetClientRect(&WndRect);

	CPaintDC PaintDC(m_hWnd);

	if (mpBaseBmp != NULL)
		delete mpBaseBmp;

	mpBaseBmp = new CBitmap;

	if (mpCompatibleBmp != NULL)
		delete mpCompatibleBmp;

	mpCompatibleBmp = new CBitmap;

	if (pTempBitmap == NULL)
		return FALSE;

	CopyBitmap(mpBaseBmp, pTempBitmap);

	ConvertBitmap(mpCompatibleBmp, mpBaseBmp, &PaintDC);

	mpCompatibleBmp->GetBitmap(&sBmpSrc);
	mnBmpWidth  = sBmpSrc.bmWidth / SKIN_PROGRESS_BITMAP_COUNT;
	mnBmpHeight = sBmpSrc.bmHeight;

	if (mpStretchBmp != NULL)
		delete mpStretchBmp;

	mpStretchBmp = new CBitmap;

	mpStretchBmp->CreateCompatibleBitmap(PaintDC, sBmpSrc.bmWidth, WndRect.Height() - 2);

	BmpDC.CreateCompatibleDC(PaintDC);
	hOldBitmap = BmpDC.SelectBitmap(*mpCompatibleBmp);

	StretchDC.CreateCompatibleDC(PaintDC);
	hOldStretch = StretchDC.SelectBitmap(*mpStretchBmp);

	StretchDC.SetStretchBltMode(HALFTONE);

	StretchDC.StretchBlt(0, 0, sBmpSrc.bmWidth, WndRect.Height() - 2, BmpDC, 0, 0, sBmpSrc.bmWidth, sBmpSrc.bmHeight, SRCCOPY);

	StretchDC.SelectBitmap(hOldStretch);
	StretchDC.DeleteDC();

	BmpDC.SelectBitmap(hOldBitmap);
	BmpDC.DeleteDC();

	mpStretchBmp->GetBitmap(&sBmpSrc);

	mnBmpWidth  = sBmpSrc.bmWidth / SKIN_PROGRESS_BITMAP_COUNT;
	mnBmpHeight = sBmpSrc.bmHeight;

	mBarImageList.Destroy();

	if(!mBarImageList.Create(mnBmpWidth, mnBmpHeight, ILC_COLOR32, 0, 0))
	{
		return false;
	}else
	{
		mBarImageList.Add(*mpStretchBmp, RGB(0, 255, 255));

		if (bDisplay != false)
		{
			OnCalcPos();
		}

		return true;
	}
}