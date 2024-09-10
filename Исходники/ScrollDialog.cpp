//-------------------------------------------------------------------//
// OnVScroll()																			//
//-------------------------------------------------------------------//
void CScrollDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ( pScrollBar == 0 )
	{
		// The current client rect		= the page size.
		// The provided client size	= the max size.
		CRect tempRect;
		GetClientRect(&tempRect);

		// Handle vertical scrollbar messages
		int nInc;
		switch (nSBCode)
		{
			/*
			// These can be tweaked to better fit the implementation
			case SB_TOP:        nInc = -m_nVscrollPos;               break;
			case SB_BOTTOM:     nInc = m_nVscrollMax-m_nVscrollPos;  break;
			case SB_LINEUP:     nInc = -1;                           break;
			case SB_LINEDOWN:   nInc = 1;                            break;
			case SB_PAGEUP:     nInc = __min(-1, -m_nVertInc);       break;
			case SB_PAGEDOWN:   nInc = __max(1, m_nVertInc);         break;
			case SB_THUMBTRACK: nInc = nPos - m_nVscrollPos;         break;
			default:            nInc = 0;
			*/

			case SB_TOP:        nInc = -m_nVscrollPos;								break;
			case SB_BOTTOM:     nInc = m_ClientRect.Height()-m_nVscrollPos;	break;
			case SB_LINEUP:     nInc = -10;												break;
			case SB_LINEDOWN:   nInc = 10;												break;
			case SB_PAGEUP:     nInc = __min(-1, -tempRect.Height() );			break;
			case SB_PAGEDOWN:   nInc = __max(1, tempRect.Height() );				break;
			case SB_THUMBTRACK: nInc = nPos - m_nVscrollPos;						break;
			default:            nInc = 0;
		}

		#pragma _TODO("Fix this so we can't scroll the dlg off the top of the screen")
		nInc = __max( -m_nVscrollPos, __min( nInc, m_ClientRect.Height() - m_nVscrollPos) );

		if (nInc)
		{
			// We are about to scroll, time to invalidate
			// so the backgrounds get updated.
			InvalidateTransparency();
			
			m_nVscrollPos += nInc;
			// int iMove = -tempRect.Height() * nInc;
			int iMove = -nInc;
			ScrollWindow(0, iMove, NULL, NULL);
			SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);

		}

	}

	inherited::OnVScroll(nSBCode, nPos, pScrollBar);

}