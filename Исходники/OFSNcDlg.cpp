void COFSNcDlg::DrawCaption(CDC &dc,const CRect &m_Rect)
{
	if(m_Rect.Width()==0||m_Rect.Height()==0) return;
	switch(m_CaptionMode)
	{
     case CAP_NONE:
	 case CAP_COLOR:	 
		 {
			 CFont m_font;
			 CBrush m_br;
			 CRect m_TextRect = m_Rect;
			 
			 if(m_bActive)
				 m_br.CreateSolidBrush(m_ActiveColor);
		     else
			     m_br.CreateSolidBrush(m_InactiveColor);

			 dc.FillRect(m_Rect,&m_br);
			 CString str;
			 GetWindowText(str);
			 m_font.Attach(GetStockObject(DEFAULT_GUI_FONT));
			 dc.SelectObject(&m_font);
			 dc.SetTextColor(RGB(255,255,255));
			 dc.SetBkMode(TRANSPARENT);
			 m_TextRect.right -= 80;
			 dc.DrawText(str,(LPRECT)&m_TextRect ,DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS|DT_SINGLELINE);
		 }
		 break;
     case CAP_BITMAP_1:	 		
		 {
			 CDC dcT;
			 dcT.CreateCompatibleDC(&dc);
			 dcT.SelectObject(pActiveBMP);
			 dc.BitBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),&dcT,0,0,SRCCOPY);
		 }
		 break;
     case CAP_BITMAP_1_ZOOM:	 		 
		 {
			 CDC dcT;
			 dcT.CreateCompatibleDC(&dc);
			 dcT.SelectObject(pActiveBMP);
			 dc.StretchBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),&dcT,0,0,m_ActiveBMPSize.cx,m_ActiveBMPSize.cy,SRCCOPY);
//			 dc.BitBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),&dcT,0,0,SRCCOPY);
		 }
		 break;
     case CAP_BITMAP_2:	 		 
		 {
			 CDC dcT;
			 dcT.CreateCompatibleDC(&dc);
			 if(m_bActive)
				 dcT.SelectObject(pActiveBMP);
			 else
                 dcT.SelectObject(pInactiveBMP);    
			 dc.BitBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),&dcT,0,0,SRCCOPY);
		 }
		 break;
     case CAP_BITMAP_2_ZOOM:	 		 
		 {
			 CDC dcT;
			 dcT.CreateCompatibleDC(&dc);
			 if(m_bActive)
			 {
				 dcT.SelectObject(pActiveBMP);
				 dc.StretchBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),&dcT,0,0,m_ActiveBMPSize.cx,m_ActiveBMPSize.cy,SRCCOPY);
			 }
			 else
			 {
                 dcT.SelectObject(pInactiveBMP);    
				 dc.StretchBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),&dcT,0,0,m_InactiveBMPSize.cx,m_InactiveBMPSize.cy,SRCCOPY);
			 }
		 }
		 break;
	}

	DWORD dwStyle = GetStyle();
	CRect m_ButtonRect;
	m_ButtonRect.SetRect(m_Rect.right - CaptionH +2 ,m_Rect.top + 4,
		m_Rect.right - 2,m_Rect.bottom - 2);
	
	if(dwStyle&WS_SYSMENU)
		dc.DrawFrameControl(&m_ButtonRect,DFC_CAPTION,DFCS_CAPTIONCLOSE);
	
	if (dwStyle & WS_MAXIMIZEBOX) 
	{
	   m_ButtonRect-=CPoint(CaptionH-2,0);
       dc.DrawFrameControl(&m_ButtonRect, DFC_CAPTION, IsZoomed()?DFCS_CAPTIONRESTORE:DFCS_CAPTIONMAX);
	}
	
	if (dwStyle & WS_MINIMIZEBOX) 
	{
		m_ButtonRect-=CPoint(CaptionH-2,0);
        dc.DrawFrameControl(&m_ButtonRect, DFC_CAPTION ,DFCS_CAPTIONMIN);
	}

}