//重画函数
void CTimerControl::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//加载位图
	CImageHandle HandleBack(&m_ImageBack);
	CImageHandle HandleArrow(&m_ImageArrow);

	//创建位图
	CBitmap BufferImage;
	if (!BufferImage.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height())) return;

	//创建 DC
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(&dc);
	BufferDC.SelectObject(&BufferImage);

	//m_ImageBack.AlphaDrawImage(&BufferDC,0,0,RGB(255,0,255));
	switch(m_dwCurrentIndex)
	{
		case 0:
			m_ImageArrow.AlphaDrawImage(&BufferDC,rcClient.Width()/2-m_ImageArrow.GetWidth()/4/2,0,16,16,0,0,RGB(255,0,255));
			break;
		case 1:
			m_ImageArrow.AlphaDrawImage(&BufferDC,0,rcClient.Height()/2-m_ImageArrow.GetHeight()/2,16,16,16,0,RGB(255,0,255));
			break;
		case 2:
			m_ImageArrow.AlphaDrawImage(&BufferDC,rcClient.Width()/2-m_ImageArrow.GetWidth()/4/2,rcClient.Height()-m_ImageArrow.GetHeight(),16,16,32,0,RGB(255,0,255));
			break;
		case 3:
			m_ImageArrow.AlphaDrawImage(&BufferDC,rcClient.Width()-m_ImageArrow.GetWidth()/4,rcClient.Height()/2-m_ImageArrow.GetHeight()/2,16,16,48,0,RGB(255,0,255));
			break;
	}

	BufferDC.SetTextColor(RGB(220,220,220));
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextAlign(TA_CENTER);
	CString str;
	if (m_nTimer!=-1)
		str.Format("%02d",m_nTimer/2);
	else
		str="00";
	BufferDC.TextOut(rcClient.Width()/2,rcClient.Height()/2-10,str);

	//绘画界面
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//清理资源
	BufferDC.DeleteDC();
	BufferImage.DeleteObject();

	return;
}