 	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
 	{
		HWND hWnd  = CCDirector::sharedDirector()->getOpenGLView()->getHWnd();
		HDC hWndDC = GetDC(hWnd);
		m_hMemDC = CreateCompatibleDC(hWndDC);
		ReleaseDC(hWnd, hWndDC);

		// create font
		HFONT hFont = NULL;
		HFONT hNewFont = NULL;
		LOGFONT lFont = {0};
		lFont.lfHeight = -(LONG)fontSize;
		MultiByteToWideChar(CP_ACP, 0, fontName, -1, lFont.lfFaceName, LF_FACESIZE);
		hFont = CreateFontIndirect(&lFont);
		if (hFont)
		{
			hNewFont = hFont;
		}
		else
		{
			hNewFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		}
		HGDIOBJ hOldFont = SelectObject(m_hMemDC, hNewFont);

		// calculate text size
        int len = strlen(text);
		SIZE extent;
		if (CGSize::CGSizeEqualToSize(dimensions, CGSizeZero))
		{
			GetTextExtentPointA(m_hMemDC, text, len, &extent);
		}
		else
		{
			extent.cx = (int)dimensions.width;
			extent.cy = (int)dimensions.height;
		}

		// create hbitmap
		m_hBmp = CreateBitmap(extent.cx, extent.cy, 1, 32, NULL);
		m_hOld = SelectObject(m_hMemDC, m_hBmp);

		// set style
        DWORD dwStyle = DT_SINGLELINE | DT_VCENTER;

		switch (alignment)
		{
		case UITextAlignmentLeft:
			dwStyle |= DT_LEFT;
			break;
		case UITextAlignmentCenter:
			dwStyle |= DT_CENTER;
			break;
		case UITextAlignmentRight:
			dwStyle |= DT_RIGHT;
			break;
		default:
			dwStyle |= DT_CENTER;
			break;
		}

		// draw text
		RECT rc = {0, 0, extent.cx, extent.cy};
		SetBkMode(m_hMemDC, TRANSPARENT);
		SetTextColor(m_hMemDC, RGB(255, 255, 255)); // white color
		DrawTextA(m_hMemDC, text, len, &rc, dwStyle);

		// free resource
		SelectObject(m_hMemDC, hOldFont);
		if (hFont)
		{
			DeleteObject(hFont);
		}
 	}