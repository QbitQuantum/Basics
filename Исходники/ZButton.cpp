void CZButton::DrawTransparent(int x,int y,CDC *pDC,CBitmap *pBitmap,COLORREF Color,CRect* rect)
{
	BITMAP bm;
	pBitmap->GetObject(sizeof(BITMAP),&bm);
	CDC ImageDC;
	ImageDC.CreateCompatibleDC(pDC);
	CBitmap *pOldImageBitmap=ImageDC.SelectObject(pBitmap);
	CDC MaskDC;
	MaskDC.CreateCompatibleDC(pDC);
	CBitmap MaskBitmap;
	MaskBitmap.CreateBitmap(bm.bmWidth,bm.bmHeight,1,1,NULL);
	CBitmap *pOldMaskBitmap=MaskDC.SelectObject(&MaskBitmap);
	ImageDC.SetBkColor(Color);
	MaskDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&ImageDC,0,0,SRCCOPY);
	CDC OrDC;
	OrDC.CreateCompatibleDC(pDC);
	CBitmap OrBitmap;
	OrBitmap.CreateCompatibleBitmap(&ImageDC,bm.bmWidth,bm.bmHeight);
	CBitmap *pOldOrBitmap=OrDC.SelectObject(&OrBitmap);
	OrDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&ImageDC,0,0,SRCCOPY);
	OrDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&MaskDC,0,0,0x220326);
	CDC TempDC;
	TempDC.CreateCompatibleDC(pDC);
	CBitmap TempBitmap;
	TempBitmap.CreateCompatibleBitmap(&ImageDC,bm.bmWidth,bm.bmHeight);
	CBitmap *pOldTmepBitmap=TempDC.SelectObject(&TempBitmap);
	TempDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,pDC,x,y,SRCCOPY);
	TempDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&MaskDC,0,0,SRCAND);
	TempDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&OrDC,0,0,SRCPAINT);
	if (rect!=NULL)
		pDC->BitBlt(x,y,rect->Width(),rect->Height(),&TempDC,rect->left,rect->top,SRCCOPY);
	else
		pDC->BitBlt(x,y,bm.bmWidth,bm.bmHeight,&TempDC,0,0,SRCCOPY);
	TempDC.SelectObject(pOldTmepBitmap);
	OrDC.SelectObject(pOldOrBitmap);
	MaskDC.SelectObject(pOldMaskBitmap);
	ImageDC.SelectObject(pOldImageBitmap);

	DeleteDC(TempDC);
	DeleteDC(OrDC);
	DeleteDC(MaskDC);
	DeleteDC(ImageDC);
}