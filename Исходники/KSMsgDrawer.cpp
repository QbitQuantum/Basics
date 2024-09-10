void KSMsgDrawer::DisplayMessages(CDC * pDC,const CRect & client)
{
	if(!m_showMessage)
		return;
	// 设置字体
	LOGFONT lf;
	memset(&lf,0,sizeof lf);
	lf.lfCharSet = GB2312_CHARSET;
	strcpy(lf.lfFaceName,m_fontName);
	lf.lfHeight = m_fontSize;
	lf.lfWeight = FW_BOLD;
//	lf.lfWeight = FW_MEDIUM;
	
	CFont font;
	CFont *oldFont;
	font.CreateFontIndirect(&lf);
	oldFont = pDC->SelectObject(&font);
	// 如果只有一行就居中
	int line_top = (m_displayMsgList.size() == 1) ? client.Height() / 2 :
		client.Height() / 3;
	int last_line = 1;

	for(cstr_vector::iterator i = m_displayMsgList.begin();
		i != m_displayMsgList.end();++i)
	{
		cstring_msg msg = (*i).second;
		int lineno = msg.GetLineno();
		if( lineno <= 0)
			continue;

		CString msg_str = msg.GetMsg();
		if(msg.GetSizeOffset() != 0)
		{
			pDC->SelectObject(oldFont);						// 新添加将老字体资源获得
			font.DeleteObject();
			lf.lfHeight = m_fontSize + msg.GetSizeOffset();
			font.CreateFontIndirect(&lf);
			//pDC->SelectObject(&font);						// 隐藏掉
			oldFont = pDC->SelectObject(&font);				// 把新的字体资源添加进来
		}
		CSize size = pDC->GetTextExtent(msg_str);
		RECT textRect;
		if (0 == m_MsgDlgflag)
		{
			textRect.left = client.Width() / 5;
 			textRect.right = client.Width();
			m_drawFormat = DT_LEFT;
		}
		else if (1 == m_MsgDlgflag)
		{
			textRect.left = (client.Width() - size.cx) / 2;
			if(textRect.left < 1)
				textRect.left = 1;
			textRect.right = textRect.left + size.cx;
			if (textRect.right >= client.right )
				textRect.right = client.right - 1;
			m_drawFormat = DT_CENTER;
		}
		else if (2 == m_MsgDlgflag)
		{
			textRect.left = client.Width() / 5;
			textRect.right = client.Width();
// 			if (client.right - textRect.left < size.cx)
// 			{
// 				textRect.left = client.right - size.cx;
// 			}
// 			textRect.right = textRect.left + size.cx;
// 			if (textRect.right >= client.right)
// 			{
// 				textRect.right = client.right - 1;
// 			}
			m_drawFormat = DT_RIGHT;
		}
		else
		{
			// 这个位置因为m_MsgDlgflag没有赋值将不会显示图像
		}
		textRect.top = line_top + (lineno - last_line) * size.cy;
		textRect.bottom = client.bottom;
		pDC->DrawText(msg_str,&textRect,m_drawFormat|DT_SINGLELINE);	
		last_line = msg.GetLineno();
		line_top = textRect.top + size.cy / 2 ;
	}
	pDC->SelectObject(oldFont);
}	