void Dg_BodyAnglesDyn::OnPrintPrintwindow()
{
	// TODO: Add your command handler code here
	CRect m_rect;
	GetClientRect(&m_rect);
	CDC* pImageDC=GetDC();
	 int formx,formy;
	formx=pImageDC->GetDeviceCaps(LOGPIXELSX);
	formy=pImageDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pImageDC);
	DWORD dwflags=PD_PAGENUMS|PD_HIDEPRINTTOFILE|PD_SELECTION;  
	CPrintDialog m_printdlg(FALSE,dwflags,NULL);     
	if(m_printdlg.DoModal()==IDOK)
	{
		CDC pdc;
		pdc.Attach(m_printdlg.GetPrinterDC());
		int printerx,printery;
		printerx=pdc.GetDeviceCaps(LOGPIXELSX);
		printery=pdc.GetDeviceCaps(LOGPIXELSY);
		double ratex,ratey;
		ratex=(double)printerx/formx;
		ratey=(double)printery/formy;
		CClientDC dc(this);
		CBitmap bmp;
		int w=m_rect.Width();
		int h =m_rect.Height();
		bmp.CreateCompatibleBitmap(&dc,m_rect.Width(),m_rect.Height());
		CDC imagedc;
		imagedc.CreateCompatibleDC(&dc);
		imagedc.SelectObject(&bmp);
		imagedc.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&dc,0,0,SRCCOPY);
		BITMAP bmap;
		bmp.GetBitmap(&bmap);
		int panelsize=0;
		if(bmap.bmBitsPixel<16)
		{
			panelsize=pow(2,bmap.bmBitsPixel*sizeof(RGBQUAD));
		}
		BITMAPINFO* bInfo=(BITMAPINFO*)LocalAlloc(LPTR,sizeof(BITMAPINFO)+panelsize);
		bInfo->bmiHeader.biClrImportant=0;
		bInfo->bmiHeader.biBitCount=bmap.bmBitsPixel;
		bInfo->bmiHeader.biCompression=0;
		bInfo->bmiHeader.biHeight=bmap.bmHeight;
		bInfo->bmiHeader.biPlanes=bmap.bmPlanes;
		bInfo->bmiHeader.biSize=sizeof(BITMAPINFO);
		bInfo->bmiHeader.biSizeImage=bmap.bmWidthBytes*bmap.bmHeight;
		bInfo->bmiHeader.biWidth=bmap.bmWidth;
		bInfo->bmiHeader.biXPelsPerMeter=0;
		bInfo->bmiHeader.biYPelsPerMeter=0;
		char *pData=new char[bmap.bmWidthBytes*bmap.bmHeight];
		::GetDIBits(imagedc.m_hDC,bmp,0,bmap.bmHeight,pData,bInfo,DIB_RGB_COLORS);
		pdc.StartDoc("print");
		::StretchDIBits(pdc.m_hDC,0,0,(int)((m_rect.Width()*ratex)),
		(int)((m_rect.Height())*ratey),0,0,m_rect.Width(),
		m_rect.Height(),pData,bInfo,DIB_RGB_COLORS,SRCCOPY);
		pdc.EndDoc();
		LocalFree(bInfo);
  
		delete[] pData;
		pData = NULL;
		bmp.DeleteObject();
	}
}