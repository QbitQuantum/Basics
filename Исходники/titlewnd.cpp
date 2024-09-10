//-----------------------------------------------------------------------------
// Purpose: Renders the title window. A special font is used if the mouse is
//			over the title window or if the window's menu is open.
//-----------------------------------------------------------------------------
void CTitleWnd::OnPaint(void)
{
	if (m_szTitle[0] != '\0')
	{
		if (GetUpdateRect(NULL, TRUE))
		{
			CPaintDC dc(this);
			CFont *pFontOld;

			if ((m_bMouseOver) || (m_bMenuOpen))
			{
				pFontOld = dc.SelectObject(&m_FontActive);
				dc.SetTextColor(RGB(255, 255, 255));
			}
			else
			{
				pFontOld = dc.SelectObject(&m_FontNormal);
				dc.SetTextColor(RGB(200, 200, 200));
			}

			dc.SetBkMode(TRANSPARENT);
			dc.TextOut(0, 0, m_szTitle, strlen(m_szTitle));
			dc.SelectObject(pFontOld);
		}
	}
}