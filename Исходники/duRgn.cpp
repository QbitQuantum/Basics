HRGN WINAPI duRgn::GetHRgn(int nWidth, int nHeight)
{
	duRect rectNew;
	rectNew.SetRect(0, 0, nWidth+1, nHeight+1);

	HRGN hRgnLeftBottom = NULL;
	HRGN hRgnRightBottom = NULL;

	if (lstrcmpi(m_szType, _T("roundrect")) == 0)
		return CreateRoundRectRgn(rectNew.left, rectNew.top, rectNew.right, rectNew.bottom, m_nRoundX, m_nRoundY);
	else if (lstrcmpi(m_szType, _T("halfroundrect")) == 0)
	{
		HRGN hRgn = CreateRoundRectRgn(rectNew.left, rectNew.top, rectNew.right, rectNew.bottom, m_nRoundX, m_nRoundY);
		hRgnLeftBottom = CreateRectRgn(rectNew.left, rectNew.bottom - m_nRoundY, rectNew.left + m_nRoundX, rectNew.bottom);
		
		if (hRgn && hRgnLeftBottom)
		{
			int nRegion = CombineRgn(hRgn, hRgn, hRgnLeftBottom, RGN_OR);
			if (nRegion == NULLREGION || ERROR)
			{
				SAFE_DELETE_OBJECT(hRgnLeftBottom);
				return NULL;
			}

			hRgnRightBottom = CreateRectRgn(rectNew.right - m_nRoundX, rectNew.bottom - m_nRoundY,  rectNew.right, rectNew.bottom);
			if (hRgnRightBottom)
			{
				nRegion = CombineRgn(hRgn, hRgn, hRgnRightBottom, RGN_OR);
				if (nRegion == NULLREGION || ERROR)
				{
					SAFE_DELETE_OBJECT(hRgnLeftBottom);
					SAFE_DELETE_OBJECT(hRgnRightBottom);
					return NULL;
				}
				
				m_hRgn = hRgn;
			}
		}
	}
	else if (lstrcmpi(m_szType, _T("style")) == 0)
		return GetStyleHRgn(nWidth, nHeight);

	SAFE_DELETE_OBJECT(hRgnLeftBottom);
	SAFE_DELETE_OBJECT(hRgnRightBottom);

	return m_hRgn;
}