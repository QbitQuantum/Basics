//*****************************************************************************************
void CBCGPSliderCtrl::OnDraw(CDC* pDCIn) 
{
	CBCGPMemDC memDC (*pDCIn, this);
	CDC* pDC = &memDC.GetDC ();

	if (!CBCGPVisualManager::GetInstance ()->OnFillParentBarBackground (this, pDC))
	{
		globalData.DrawParentBackground (this, pDC, NULL);
	}

	DWORD dwStyle = GetStyle ();
	BOOL bVert = (dwStyle & TBS_VERT);
	BOOL bLeftTop = (dwStyle & TBS_BOTH) || (dwStyle & TBS_LEFT);
	BOOL bRightBottom = (dwStyle & TBS_BOTH) || ((dwStyle & TBS_LEFT) == 0);
	BOOL bIsFocused = GetSafeHwnd () == ::GetFocus ();

	CRect rectChannel;
	GetChannelRect (rectChannel);

	if (bVert)
	{
		CRect rect = rectChannel;

		rectChannel.left = rect.top;
		rectChannel.right = rect.bottom;
		rectChannel.top = rect.left;
		rectChannel.bottom = rect.right;
	}

	CBCGPDrawOnGlass dog(m_bOnGlass);

	CBCGPVisualManager::GetInstance ()->OnDrawSliderChannel (pDC, this, bVert, rectChannel, m_bOnGlass);

	CRect rectThumb;
	GetThumbRect (rectThumb);

	int nTicSize = max(3, (bVert ? rectThumb.Height() : rectThumb.Width()) / 3);
	int nTicOffset = 2;

	int nNumTics = GetNumTics();
	for (int i = 0; i < nNumTics; i++)
	{
		int nTicPos = GetTicPos(i);

		if (nTicPos < 0)
		{
			if (i == nNumTics - 2)
			{
				if (bVert)
				{
					nTicPos = rectChannel.top + rectThumb.Height() / 2;
				}
				else
				{
					nTicPos = rectChannel.left + rectThumb.Width() / 2;
				}
			}
			else if (i == nNumTics - 1)
			{
				if (bVert)
				{
					nTicPos = rectChannel.bottom - rectThumb.Height() / 2 - 1;
				}
				else
				{
					nTicPos = rectChannel.right - rectThumb.Width() / 2 - 1;
				}
			}
		}

		if (nTicPos >= 0)
		{
			CRect rectTic1(0, 0, 0, 0);
			CRect rectTic2(0, 0, 0, 0);

			if (bVert)
			{
				if (bLeftTop)
				{
					rectTic1 = CRect(rectThumb.left - nTicOffset - nTicSize, nTicPos, rectThumb.left - nTicOffset, nTicPos + 1);
				}
				
				if (bRightBottom)
				{
					rectTic2 = CRect(rectThumb.right + nTicOffset, nTicPos, rectThumb.right + nTicOffset + nTicSize, nTicPos + 1);
				}
			}
			else
			{
				if (bLeftTop)
				{
					rectTic1 = CRect(nTicPos, rectThumb.top - nTicOffset - nTicSize, nTicPos + 1, rectThumb.top - nTicOffset);
				}

				if (bRightBottom)
				{
					rectTic2 = CRect(nTicPos, rectThumb.bottom + nTicOffset, nTicPos + 1, rectThumb.bottom + nTicOffset + nTicSize);
				}
			}

			if (!rectTic1.IsRectEmpty())
			{
				CBCGPVisualManager::GetInstance ()->OnDrawSliderTic(pDC, this, rectTic1, bVert, TRUE, m_bOnGlass);
			}

			if (!rectTic2.IsRectEmpty())
			{
				CBCGPVisualManager::GetInstance ()->OnDrawSliderTic(pDC, this, rectTic2, bVert, FALSE, m_bOnGlass);
			}
		}
	}

	CBCGPVisualManager::GetInstance ()->OnDrawSliderThumb (
		pDC, this, rectThumb, m_bIsThumbHighligted || bIsFocused,
		m_bIsThumPressed, !IsWindowEnabled (),
		bVert, bLeftTop, bRightBottom, m_bOnGlass);

	if (bIsFocused && m_bDrawFocus)
	{
		CRect rectFocus;
		GetClientRect (rectFocus);

		if (m_bOnGlass)
		{
			CBCGPDrawManager dm (*pDC);
			dm.DrawFocusRect(rectFocus);
		}
		else
		{
			pDC->DrawFocusRect (rectFocus);
		}
	}
}