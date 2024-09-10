void CKSNLDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC memDC;
	CBitmap bkBit,*oldBkBit;
	CRect client;
	dc.GetClipBox(client);
	if(memDC.CreateCompatibleDC(&dc))
	{
		if(bkBit.CreateCompatibleBitmap(&dc,client.Width(),client.Height()))
		{
			oldBkBit = memDC.SelectObject(&bkBit);
			//////////////////////////////////////////////////////////////////////////
			// 设置字体
			LOGFONT lf;
			memset(&lf,0,sizeof lf);
			lf.lfCharSet = GB2312_CHARSET;
			strcpy(lf.lfFaceName,m_config.m_fontName);
			lf.lfHeight = m_config.m_fontSize;
			lf.lfWeight = FW_BOLD;

			CFont font;
			font.CreateFontIndirect(&lf);
			memDC.SelectObject(font);
			//////////////////////////////////////////////////////////////////////////
			// 设置字体颜色
			memDC.SetTextColor(m_config.m_fontColor);
			//////////////////////////////////////////////////////////////////////////
			CRect clientRect;
			GetWindowRect(clientRect);
			memDC.SetBkMode(TRANSPARENT);
			m_config.m_bkImg.m_Dest.x = 0;
			m_config.m_bkImg.m_Dest.y = 0;
			m_config.m_bkImg.m_DestSize.cx = clientRect.Width();
			m_config.m_bkImg.m_DestSize.cy = clientRect.Height();
			m_config.m_bkImg.m_Src.x = 0;
			m_config.m_bkImg.m_Src.y = 0;
			m_config.m_bkImg.m_SrcSize.cx = m_config.m_bkImg.GetWidth();
			m_config.m_bkImg.m_SrcSize.cy = m_config.m_bkImg.GetHeight();
			m_config.m_bkImg.Display(&memDC);
			if(!GetCurrentWorkflow())
			{
				DrawFuncBtn(&memDC);          
			}
			//////////////////////////////////////////////////////////////////////////
			// show tip messages
			m_drawer.DisplayMessages(&memDC,clientRect);
			//////////////////////////////////////////////////////////////////////////
			//
			dc.BitBlt(0,0,client.Width(),client.Height(),&memDC
				,0,0,SRCCOPY);
			font.DeleteObject();
			memDC.SelectObject(oldBkBit);
			memDC.DeleteDC();
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}