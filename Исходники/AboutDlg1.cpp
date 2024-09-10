BOOL AboutDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
		CRect rect;
	GetWindowRect(&rect);
	GetClientRect(&m_rect);
	CDC memdc;     //定义一个显示设备对象 
	CBitmap bmp;       //定义一个位图对象 
	memdc.CreateCompatibleDC(pDC);     //建立与屏幕显示兼容的内存显示设备 
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//建立一个与屏幕显示兼容的位图
	memdc.SetBkMode(TRANSPARENT);
	CBitmap* pOldBmp = memdc.SelectObject(&bmp);            //将位图选入到内存显示设备中		
	DWORD style = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
	m_DlgPic.Load(IDR_ABOUT);
	if(m_DlgPic != NULL)
		m_DlgPic.Render(&memdc,m_rect);

	m_DlgPic.Load(IDR_JPG_BTN1);
	if(m_DlgPic != NULL)
		m_DlgPic.Render(&memdc,m_rtbutton);

	m_DlgPic.Load(IDR_CLOSEX);
	if(m_DlgPic != NULL)
		m_DlgPic.Render(&memdc,m_rtclose);
	switch(m_numbtn)
	{
	case 0:

		break;
	case 1:		m_DlgPic.Load(IDR_JPG_BTN1_1);
				if(m_DlgPic != NULL)
						m_DlgPic.Render(&memdc,m_rtbutton);
	break;
	case 2:		m_DlgPic.Load(IDR_CLOSEX1);
				if(m_DlgPic != NULL)
					m_DlgPic.Render(&memdc,m_rtclose);
	
		break;
	default:
		break;
	}

	CFont   *pOldfont = (CFont *)memdc.SelectObject(&m_font); 
    memdc.SetTextColor(RGB(0, 0, 0)); 
	//memdc.SetBkColor(TRANSPARENT);
	CString str,str1;
	if (g_Language)
	{
		str = GetStringLanguage("About","Caption","About RiPlayer");
		str1 = GetStringLanguage("About","Button1","Ok");
	}
	else
	{
		str = GetStringLanguage("About","Caption","关于RiPlayer");
		str1 = GetStringLanguage("About","Button1","确定");
	}
	memdc.DrawText(str,CRect(10,2,180,28),DT_LEFT| DT_VCENTER | DT_SINGLELINE);
	memdc.DrawText(str1,m_rtbutton,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	pDC->BitBlt(0,0,m_rect.Width(),m_rect.Height(),&memdc,0,0,SRCCOPY);
	bmp.DeleteObject();
	memdc.DeleteDC();
	ReleaseDC(pDC);
	return true;//true
}