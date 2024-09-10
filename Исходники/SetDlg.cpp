BOOL CSetDlg::OnEraseBkgnd(CDC* pDC) 
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


	m_DlgPic.Load(IDR_JPG_DIALOG1);
	if(m_DlgPic != NULL)
		m_DlgPic.Render(&memdc,m_rect);

	if (m_bensure) //确定
	{
		m_DlgPic.Load(IDR_JPG_BTN2_2);
	} 
	else
	{
		m_DlgPic.Load(IDR_JPG_BTN2);
			
	}
	m_DlgPic.Render(&memdc,m_rtensure);
	if (m_bcancel)  //取消
	{
		m_DlgPic.Load(IDR_JPG_BTN2_2);
	} 
	else
	{
		m_DlgPic.Load(IDR_JPG_BTN2);
		
	}
	m_DlgPic.Render(&memdc,m_rtcancal);
	if (m_bclose)
	{
		m_DlgPic.Load(IDR_CLOSEX1);
	} 
	else
	{
		m_DlgPic.Load(IDR_CLOSEX);
		
	}
	m_DlgPic.Render(&memdc,m_rtclose);



	CFont   *pOldfont = (CFont *)memdc.SelectObject(&m_font); 
  
	memdc.DrawText(m_strLanguage[0],CRect(m_rect.left+8,5,m_rect.left+150,30),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memdc.DrawText(m_strLanguage[5],m_rtensure,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	memdc.DrawText(m_strLanguage[6],m_rtcancal,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	pDC->BitBlt(0,0,m_rect.Width(),m_rect.Height(),&memdc,0,0,SRCCOPY);
	bmp.DeleteObject();
	memdc.DeleteDC();
	ReleaseDC(pDC);
	return true;

}