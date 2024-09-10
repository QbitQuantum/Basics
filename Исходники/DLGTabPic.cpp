void CDLGTabPic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
	//贴背景图	
	CRect    rect;     
	GetClientRect(&rect);     

	//从资源中载入位图     
	CBitmap    bitmap;     
	bitmap.LoadBitmap(IDB_FIND_BACK);    
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	CDC    memdc;     
	memdc.CreateCompatibleDC(&dc);     
	memdc.SelectObject(bitmap); 
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();


	int w,h;

	if(bim)
	{
		//显示图片
		CDC *pDC=m_pic.GetDC();
		CRect rect; 
		m_pic.GetClientRect(&rect);//获得pictrue控件所在的举行区域

		PicAutoWH(rect.Width(),rect.Height(),pic._GetWidth(),pic._GetHeight(),&w,&h);

		pic.DrawPicture(*pDC, (rect.Width()-w)/2,(rect.Height()-h)/2,w,h);
		m_pic.ReleaseDC(pDC);
	}

	if(bimsmall)
	{
		//显示图片
		CDC *pDCsmall=m_pic_small.GetDC();
		CRect rectsmall; 
		m_pic_small.GetClientRect(&rectsmall);//获得pictrue控件所在的举行区域

		PicAutoWH(rectsmall.Width(),rectsmall.Height(),picsmall._GetWidth(),picsmall._GetHeight(),&w,&h);

		picsmall.DrawPicture(*pDCsmall,(rectsmall.Width()-w)/2,(rectsmall.Height()-h)/2,w,h);
		m_pic_small.ReleaseDC(pDCsmall);
	}

	GetDlgItem(IDC_STATIC_TXT)->SetWindowText(m_txt);
	CDialog::OnPaint();
}