void MenuItemSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
	{
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),FALSE);
		if(m_iCurFrame==7&&m_bWithText)
		{
			int oldMode;
			COLORREF oldColor;
			CFont cf;
			cf.CreateFont(
				19,                        // nHeight
				0,                         // nWidth
				0,                         // nEscapement
				0,                         // nOrientation
				FW_NORMAL,                 // nWeight
				FALSE,                     // bItalic
				FALSE,                     // bUnderline
				0,                         // cStrikeOut
				ANSI_CHARSET,              // nCharSet
				OUT_DEFAULT_PRECIS,        // nOutPrecision
				CLIP_DEFAULT_PRECIS,       // nClipPrecision
				DEFAULT_QUALITY,           // nQuality
				DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
				"���ו"); 

			HFONT oldFont=(HFONT)SelectObject(hDC,cf.m_hObject);

			oldColor=SetTextColor(hDC,RGB(252,252,56));
			oldMode=SetBkMode(hDC,TRANSPARENT);
			RECT rt=m_rcPosition;
			rt.left-=4;rt.right-=4;
			rt.top++;rt.bottom++;
			DrawText(hDC,m_strText,-1,&rt,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
			
			SelectObject(hDC,oldFont);
			cf.DeleteObject();
			SetTextColor(hDC,oldColor);
			SetBkMode(hDC,oldMode);
		}
	}
}