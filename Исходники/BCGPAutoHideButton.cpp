//**********************************************************************************//
void CBCGPAutoHideButton::OnDraw (CDC* pDC)
{
	ASSERT_VALID (this);

	const BOOL bIsOverlapped = 
		(CBCGPVisualManager::GetInstance ()->HasOverlappedAutoHideButtons ()) || m_bOverlappingTabs;
	const int nTextMargin = bIsOverlapped ? (IsHorizontal () ? 5 : 7) : 
							m_nTextMargin;

	CSize size = GetSize ();
	m_rect.SetRect (0, 0, size.cx, size.cy);

	// calculate border size and draw the border
	CRect rectBorderSize (m_nBorderSize, 0, m_nBorderSize, m_nBorderSize);

	switch (m_dwAlignment & CBRS_ALIGN_ANY)
	{
	case CBRS_ALIGN_RIGHT:
		globalUtils.FlipRect (rectBorderSize, 90);
		break;
	case CBRS_ALIGN_BOTTOM:
		globalUtils.FlipRect (rectBorderSize, 180);
		break;
	case CBRS_ALIGN_LEFT:
		globalUtils.FlipRect (rectBorderSize, -90);
		break;
	}

	if (bIsOverlapped && !m_pParentBar->m_bFirstInGroup)
	{
		CRect rectPrev = m_rect;

		switch (m_dwAlignment & CBRS_ALIGN_ANY)
		{
		case CBRS_ALIGN_RIGHT:
		case CBRS_ALIGN_LEFT:
			rectPrev.OffsetRect (0, -m_rect.Height () + size.cx / 2);
			break;

		case CBRS_ALIGN_TOP:
		case CBRS_ALIGN_BOTTOM:
			rectPrev.OffsetRect (-m_rect.Width () + size.cy / 2, 0);
			break;
		}

		OnFillBackground (pDC, rectPrev);
		OnDrawBorder (pDC, rectPrev, rectBorderSize);
	}

	OnFillBackground (pDC, m_rect);
	OnDrawBorder (pDC, m_rect, rectBorderSize);

	if (m_pAutoHideWindow == NULL)
	{
		return;
	}

	ASSERT_VALID (m_pAutoHideWindow);

	CRect rectDraw = m_rect;

	if (!bIsOverlapped)
	{
		rectDraw.DeflateRect (rectBorderSize);
	}

	rectDraw.DeflateRect (m_nMarginSize, m_nMarginSize);

	if (m_pAutoHideWindow != NULL)
	{
		// draw the icon (if any)
		HICON hIcon = m_pAutoHideWindow->GetBarIcon (FALSE);
		if (hIcon != NULL || bIsOverlapped)
		{
			CSize sizeIcon (globalData.m_sizeSmallIcon);

			int dx = IsHorizontal () ? 0 : (rectDraw.Width () - sizeIcon.cx) / 2;
			int dy = IsHorizontal () ? (rectDraw.Height () - sizeIcon.cy) / 2 : 0;

			if (bIsOverlapped && !m_bOverlappingTabs)
			{
				if (IsHorizontal ()	)
				{
					dx += rectDraw.Height () / 2 + 1;
				}
				else
				{
					dy += rectDraw.Width () / 2 + 1;
				}
			}

			if (hIcon != NULL)
			{
				::DrawIconEx (pDC->GetSafeHdc (), 
							rectDraw.left + dx, rectDraw.top + dy, hIcon,
							sizeIcon.cx, sizeIcon.cy, 0, NULL, DI_NORMAL);
			}
			else
			{
				#ifndef BCGP_EXCLUDE_RIBBON
					CBCGPVisualManager::GetInstance ()->
						OnDrawDefaultRibbonImage (pDC, 
							CRect (CPoint (rectDraw.left + dx, rectDraw.top + dy), sizeIcon));
				#endif
			}
			if (IsHorizontal ())
			{
				rectDraw.left += nTextMargin + sizeIcon.cx + dx;
			}
			else
			{
				rectDraw.top += nTextMargin + sizeIcon.cy + dy;
			}
		}
		else
		{
			if (IsHorizontal ())
			{
				rectDraw.left += m_nMarginSize;
			}
			else
			{
				rectDraw.top += m_nMarginSize;
			}
		}

		// Draw text:
		CString strText;
		m_pAutoHideWindow->GetWindowText (strText);

		if (!strText.IsEmpty () && m_pParentBar->m_bActiveInGroup || !m_bOverlappingTabs)
		{
			int nOldMode = pDC->SetBkMode (TRANSPARENT);

			CFont* pFontOld = (CFont*) pDC->SelectObject (IsHorizontal () ? 
										&globalData.fontRegular : &globalData.fontVert);
			ASSERT(pFontOld != NULL);

			pDC->SetTextColor (
				CBCGPVisualManager::GetInstance ()->GetAutoHideButtonTextColor (this));

			if (IsHorizontal ())
			{
				pDC->DrawText (strText, &rectDraw, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			}
			else
			{
				TEXTMETRIC tm;
				pDC->GetTextMetrics (&tm);

				CRect rectText = rectDraw;

				rectText.left = rectText.right - (rectDraw.Width () - tm.tmHeight + 1) / 2;
				rectText.bottom = rectDraw.top + nTextMargin;

				pDC->DrawText (strText, &rectText, DT_SINGLELINE | DT_NOCLIP);
			}

			pDC->SelectObject (pFontOld);
			pDC->SetBkMode (nOldMode);
		}
	}
}