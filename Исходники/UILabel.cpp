void CUILabel::DoPaint(HDC hDC, const RECT& rcPaint)
{
	if (m_BackColor != INVALID__UICOLOR)
	{
		CUIBlueRenderEngine::DoFillRect(hDC, m_pManager, m_rcItem, m_BackColor);
	}

	if (m_BorderColorOutside != INVALID__UICOLOR)
	{
		RECT rect = {m_rcItem.left + 1, m_rcItem.top + 1, m_rcItem.right - 1, m_rcItem.bottom - 1};
		CUIBlueRenderEngine::DoPaintBorder(hDC, m_pManager, m_rcItem, m_BorderColorOutside);
	}

	if (m_BorderColorInside != INVALID__UICOLOR)
	{
		RECT rect = {m_rcItem.left + 1, m_rcItem.top + 1, m_rcItem.right - 1, m_rcItem.bottom - 1};
		CUIBlueRenderEngine::DoPaintBorder(hDC, m_pManager, rect, m_BorderColorInside);
	}

	if (m_pImageOwner != NULL && m_nIndex >= 0)
	{
		RECT rc = m_rcItem;

		Graphics graph(hDC);

		int nStartX = rc.left;
		int nStartY = rc.top;

		int nImageWidth = m_pImageOwner->GetWidth() / m_nImageCount;
		int nImageHeight = m_pImageOwner->GetHeight();

		double dblScal = (double)nImageWidth / nImageHeight;

		int nRectWidth = nImageWidth;
		int nRectHeight = nImageHeight;

		if (m_sizeAnimate.cx != 0 && m_sizeAnimate.cy != 0)
		{
			nRectWidth = m_sizeAnimate.cx;
			nRectHeight = m_sizeAnimate.cy;
		}


		if ((m_rcItem.bottom - m_rcItem.top) * dblScal < (m_rcItem.right - m_rcItem.left))
		{
			nRectWidth = (int)(nRectHeight * dblScal);
		}
		else
		{
			nRectHeight = (int)(nRectWidth / dblScal);
		}


		nStartX = rc.left + (rc.right - rc.left - nRectWidth) / 2;
		if (nStartX < rc.left)
		{
			nStartX = rc.left;

			nRectWidth = rc.right - rc.left;
		}

		nStartY = rc.top + (rc.bottom - rc.top - nRectHeight) / 2;
		if (nStartY < rc.top)
		{
			nStartY = rc.top;

			nRectHeight = rc.bottom - rc.top;
		}


		RectF rfDest(PointF((REAL)nStartX, (REAL)nStartY), SizeF((REAL)nRectWidth, (REAL)nRectHeight));

		if (m_fAlpha <= 1.0)
		{
			ColorMatrix colorMatrix = {	1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
				0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 0.0f, m_fAlpha, 0.0f, 
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f
			}; 

			ImageAttributes imageAtt; 
			imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap); 
			graph.DrawImage(m_pImageOwner, rfDest, (REAL)nImageWidth * m_nIndex, (REAL)0, (REAL)nImageWidth, (REAL)nImageHeight, UnitPixel, &imageAtt);
		}
		else
		{
			graph.DrawImage(m_pImageOwner, rfDest, (REAL)nImageWidth * m_nIndex, (REAL)0, (REAL)nImageWidth, (REAL)nImageHeight, UnitPixel, NULL);
		}


		if (m_bImageAsLinker && m_sText.GetLength() == 0)
		{
			m_nLinks = 1;
			m_rcLinks[0] = CUIRect(nStartX, nStartY, nStartX + nRectWidth, nStartY + nRectHeight);
		}
	}
	
	if (m_sText.GetLength() > 0)
	{
		RECT rcText = m_rcItem;
		m_nLinks = lengthof(m_rcLinks);
		COLORREF color = m_TextColor;
		if (!IsEnabled())
		{
			color = m_TextColor_Disable;
		}

		CUIBlueRenderEngine::DoPaintPrettyText(hDC, m_pManager, rcText, m_sText, color, INVALID__UICOLOR, m_rcLinks, m_nLinks, m_uTextStyle);

		if (m_nLinks == 1 && m_sText.GetLength() > 4)
		{
			if ((m_sText.GetAt(0) == _T('<') && m_sText.GetAt(1) == _T('a')) && 
				(m_sText.GetAt(m_sText.GetLength() - 1) == _T('>') && m_sText.GetAt(m_sText.GetLength() - 2) == _T('a'))
				)
			{
				if (m_rcLinks[0].right - m_rcLinks[0].left < 20)
				{
					m_rcLinks[0].left = m_rcItem.left;
					m_rcLinks[0].right = m_rcItem.right;
				}
			}	
		}
	}
}