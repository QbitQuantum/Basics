BOOL CImageEdit::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);
	CDC dcMemory;
	BITMAP bmpInfo;

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_Bitmap_Back);
	bitmap.GetBitmap(&bmpInfo);

	CBrush brush;
	brush.CreatePatternBrush(&bitmap);
	pDC->FillRect(&rect, &brush);

	return TRUE;
//	return CEdit::OnEraseBkgnd(pDC);
}