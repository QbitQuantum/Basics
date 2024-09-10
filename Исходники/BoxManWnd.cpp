void CBoxManWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	CDC dcMemory;
	CBitmap bitmap;

	if (!dc.IsPrinting())
	{
		if (dcMemory.CreateCompatibleDC(&dc))
		{
			if (bitmap.CreateCompatibleBitmap(&dc,m_rcClient.right,m_rcClient.bottom))
			{
				dcMemory.SelectObject(&bitmap);
				theBoxMan.DrawGameArea(&dcMemory);
				dc.BitBlt(m_rcClient.left,m_rcClient.top,m_rcClient.right,m_rcClient.bottom,&dcMemory,0,0,SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}




}