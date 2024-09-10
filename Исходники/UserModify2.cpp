void CUserModify2::DrawRangeImage(int i, CDC *pDC, CRect rc){
	HBITMAP hBitmap1 = NULL;
	HBITMAP hBitmap2 = NULL;
	CBitmap bit[2];
	if(hBitmap1 ==NULL||hBitmap2 ==NULL){

		hBitmap1 = (HBITMAP)::LoadImage(NULL,_T("images/top.bmp"), 
			IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
		hBitmap2 = (HBITMAP)::LoadImage(NULL,_T("images/band.bmp"), 
			IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
		if(hBitmap1 == NULL||hBitmap2 == NULL)
		{
			AfxMessageBox(_T("无法加载图片"));
			PostQuitMessage(0);
		}
		if (bit[0].m_hObject)
			bit[0].Detach();
		if (bit[1].m_hObject)
			bit[1].Detach();
		bit[0].Attach(hBitmap1);
		bit[1].Attach(hBitmap2);
	}


	CDC MemDC;
	BITMAP bm;
	bit[i].GetBitmap(&bm);

	int li_Width = bm.bmWidth;
	int li_Height = bm.bmHeight;


	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = MemDC.SelectObject(&bit[i]);

	int x=rc.left;
	int y=rc.top;

	while (y < (rc.Height()+rc.top)) 
	{
		while(x < (rc.Width()+rc.left)) 
		{
			pDC->BitBlt(x, y, li_Width, li_Height, &MemDC, 0, 0, SRCCOPY);
			x += li_Width;
		}
		x = rc.left;
		y += li_Height;
	}

	//pDC->StretchBlt(x, y, rc.right - rc.left, rc.bottom - rc.top, &MemDC, 0, 0,2,2 ,SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();

}