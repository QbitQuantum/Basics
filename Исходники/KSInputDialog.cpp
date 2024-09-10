void CKSInputDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC memDC;
	CBitmap bkBit,*oldBkBit;
	CRect client;
	RECT clientRect,edtRect;
	dc.GetClipBox(client);
	if(memDC.CreateCompatibleDC(&dc))
	{
		memDC.SetBkMode(TRANSPARENT);
		if(bkBit.CreateCompatibleBitmap(&dc,client.Width(),client.Height()))
		{
			oldBkBit = memDC.SelectObject(&bkBit);
			/*
			CBrush brh;
			brh.CreateSolidBrush( RGB(0,0,255) );
			brh.UnrealizeObject();
			memDC.FillRect( client , &brh );
			*/
			if(m_config)
			{
				CRect parentRect;
				CWnd * parentWnd = GetParent();
				ASSERT(parentWnd != NULL);
				parentWnd->GetWindowRect(parentRect);
				GetWindowRect(&clientRect);
				m_config->m_bkImg.m_Dest.x = -(clientRect.left);
				m_config->m_bkImg.m_Dest.y = -(clientRect.top);
				m_config->m_bkImg.m_DestSize.cx = parentRect.Width();
				m_config->m_bkImg.m_DestSize.cy = parentRect.Height();
				m_config->m_bkImg.m_Src.x = 0;
				m_config->m_bkImg.m_Src.y = 0;
				m_config->m_bkImg.m_SrcSize.cx = m_config->m_bkImg.GetWidth();
				m_config->m_bkImg.m_SrcSize.cy = m_config->m_bkImg.GetHeight();
				m_config->m_bkImg.Display(&memDC);
				/*
				dc.StretchBlt(0,0,client.Width(),client.Height(),&memDC
				,0,0,m_config->m_bkImg.GetWidth(),m_config->m_bkImg.GetHeight(),SRCCOPY);
				*/
			}
			//////////////////////////////////////////////////////////////////////////
			// 设置字体
			LOGFONT lf;
			memset(&lf,0,sizeof lf);
			lf.lfCharSet = GB2312_CHARSET;
			strcpy(lf.lfFaceName,m_fontName.GetBuffer(1));
			lf.lfHeight = m_fontSize;
			lf.lfWeight = FW_BOLD;			

			CFont font;
			CFont *pOldFont;						// 新添加的老字体资源
			font.CreateFontIndirect(&lf);
			// memDC.SelectObject(font);			// 隐掉
			pOldFont = memDC.SelectObject(&font);	// 新添加获得老字体资源		
			//////////////////////////////////////////////////////////////////////////
			// 取得字体属性
			TEXTMETRIC tm;
			memset(&tm,0,sizeof tm);
			memDC.GetTextMetrics(&tm);
			CSize fs = memDC.GetTextExtent(m_prompt);
			int textWidth = fs.cx;//tm.tmAveCharWidth * (m_prompt.GetLength() + 1);
			//////////////////////////////////////////////////////////////////////////
			// 设置字体颜色
			memDC.SetTextColor(m_fontColor);
			//////////////////////////////////////////////////////////////////////////
			GetWindowRect(&clientRect);
			ScreenToClient(&clientRect);
			m_edtInput.GetWindowRect(&edtRect);
			ScreenToClient(&edtRect);
			int x,y;
			RECT textRect;
			if(clientRect.right > textWidth)
			{
				x = (clientRect.right - textWidth) / 2;
				textRect.left = x;
				textRect.right = textRect.left + textWidth;
			}
			else
			{
				x = 20;
				textRect.left = x;
				textRect.right = clientRect.right - 20;
			}
			
			//y = (edtRect.top - tm.tmHeight - 2);
			y = 5;
			memDC.MoveTo(x,y);
			textRect.top = y;
			
			textRect.bottom = y + GetTextLineHeight(fs.cy,textRect.right-textRect.left
				,fs.cx);
			memDC.DrawText(m_prompt,&textRect,DT_WORDBREAK|DT_CENTER);
			//////////////////////////////////////////////////////////////////////////
			
			dc.BitBlt(0,0,client.Width(),client.Height(),&memDC,0,0,SRCCOPY);
			memDC.SelectObject(pOldFont);				// 新添加的把老字体资源选回去
			font.DeleteObject();
			//brh.DeleteObject();
			memDC.SelectObject(oldBkBit);
			memDC.DeleteDC();
		}
	}
}