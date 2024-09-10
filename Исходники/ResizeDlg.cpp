void CResizeDlg::OnSize(UINT nType,int cx,int cy)
{
	int	 nCount;

	std::vector<CItemCtrl>::iterator it;

	CDialog::OnSize(nType,cx,cy);

	if((nCount = m_Items.size()) > 0) {
		CRect  cltRect;
		GetClientRect(&cltRect);
		ClientToScreen(cltRect);

		HDWP   hDWP;
		int    sizeType = WST_NONE;		

#if 0
		int    deltaX = cltRect.Width() - m_cltRect.Width();
		int	   deltaY = cltRect.Height()- m_cltRect.Height();
		int	   midX = (cltRect.left + cltRect.right) / 2;
		int    midY = (cltRect.top + cltRect.bottom) / 2;
		CPoint csrPt(::GetMessagePos());

		if (deltaX) {
			if (csrPt.x < midX)
				sizeType |= WST_LEFT;
			else
				sizeType |= WST_RIGHT;
		}

		if (deltaY) {
			if (csrPt.y < midY)
				sizeType |= WST_TOP;
			else
				sizeType |= WST_BOTTOM;
		}
#else
		switch (m_nDelaySide) {
		case WMSZ_BOTTOM:
			sizeType = WST_BOTTOM;
			break;
		case WMSZ_BOTTOMLEFT:
			sizeType = WST_BOTTOM|WST_LEFT;
			break;
		case WMSZ_BOTTOMRIGHT:
			sizeType = WST_BOTTOM|WST_RIGHT;
			break;
		case WMSZ_LEFT:
			sizeType = WST_LEFT;
			break;
		case WMSZ_RIGHT:
			sizeType = WST_RIGHT;
			break;
		case WMSZ_TOP:
			sizeType = WST_TOP;
			break;
		case WMSZ_TOPLEFT:
			sizeType = WST_TOP|WST_LEFT;
			break;
		case WMSZ_TOPRIGHT:
			sizeType = WST_TOP|WST_RIGHT;
			break;
		default:
			break;
		}
#endif

		if (sizeType != WST_NONE) {
			hDWP = ::BeginDeferWindowPos(nCount);

			for (it = m_Items.begin(); it != m_Items.end(); it++)
				hDWP = it->OnSize(hDWP, sizeType, &cltRect, &m_cltRect, &m_cltR0, this);

			::EndDeferWindowPos(hDWP);
		}

		m_cltRect = cltRect;
	}

	m_nDelaySide = 0;
}