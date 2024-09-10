HBITMAP CScreenSnap::ChangeDataToBitmap(BYTE* pData)
{
	BITMAPFILEHEADER* pbmfh ;     // DIB位图文件头
	HBITMAP           hBitmap ;
	
	pbmfh = (BITMAPFILEHEADER *)pData;
	if (pbmfh->bfType != * (WORD *) "BM") 
		return NULL ;
	
	HDC hdc = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	if(hdc == NULL)
		return NULL;

	// 创建DDB位图
	hBitmap = CreateDIBitmap(hdc,              
							(BITMAPINFOHEADER *) (pbmfh + 1),
							CBM_INIT,
							(BYTE *) pbmfh + pbmfh->bfOffBits,
							(BITMAPINFO *) (pbmfh + 1),
							DIB_RGB_COLORS) ;

	DeleteDC(hdc);

	return hBitmap ;
}