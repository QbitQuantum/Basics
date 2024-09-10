//=============================================================================	
void CXButtonXP::DrawIcon(CDC *pDC,
						  BOOL bHasText,
						  CRect& rectItem,		// from LPDRAWITEMSTRUCT
						  CRect& rectText,
						  BOOL bIsPressed,
						  BOOL bIsThemed,
						  BOOL bIsDisabled)
//=============================================================================	
{
	if (m_hIcon)
	{
		// first get size of icon

		DWORD dwWidth = 32;		// assume 32x32
		DWORD dwHeight = 32;
		ICONINFO iconinfo;

		if (GetIconInfo(m_hIcon, &iconinfo))
		{
			CBitmap* pBitmap = CBitmap::FromHandle(iconinfo.hbmColor);
			if (pBitmap)
			{
				BITMAP bm;
				pBitmap->GetBitmap(&bm);
				dwWidth = bm.bmWidth;
				dwHeight = bm.bmHeight;
			}

			if (iconinfo.hbmColor) 
				::DeleteObject(iconinfo.hbmColor);
			if (iconinfo.hbmMask) 
				::DeleteObject(iconinfo.hbmMask);
		}

		CRect rectImage(rectItem);

		PrepareImageRect(bHasText, rectItem, rectText, bIsPressed, bIsThemed,
			dwWidth, dwHeight, rectImage);

		HICON hIcon = m_hIcon;
		UINT nFlags = bIsDisabled ? DSS_DISABLED : DSS_NORMAL;

		if (bIsDisabled && m_hGrayIcon)
		{
			hIcon = m_hGrayIcon;
			nFlags = DSS_NORMAL;
		}

		nFlags |= DST_ICON;

		pDC->DrawState(CPoint(rectImage.left, rectImage.top),
					   CSize(rectImage.right - rectImage.left, rectImage.bottom - rectImage.top),
					   hIcon,
					   nFlags,
					   (CBrush *) NULL);
	}
}