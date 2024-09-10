CSize CExtDockBar::CalcFixedLayout(
	BOOL bStretch,
	BOOL bHorz
	)
{
	// based on MFC's source of
	// CDockBar::CalcFixedLayout()
	ASSERT_VALID(this);
CSize sizeFixed =
		CControlBar::CalcFixedLayout( bStretch, bHorz );
	// get max size
CSize sizeMax;
	if( !m_rectLayout.IsRectEmpty() )
		sizeMax = m_rectLayout.Size();
	else
	{
		CFrameWnd * pFrame = GetParentFrame();
		CRect rcFrameWindow;
		pFrame->GetClientRect( &rcFrameWindow );
		sizeMax = rcFrameWindow.Size();
	}
	// prepare for layout
AFX_SIZEPARENTPARAMS layout;
	layout.hDWP = m_bLayoutQuery ?
		NULL : ::BeginDeferWindowPos( m_arrBars.GetSize() );

CPoint pt( 0, 0 );
int nWidth = 0;

BOOL bWrapped = FALSE;

	for( int nPos = 0; nPos < m_arrBars.GetSize(); nPos++ )
	{ // layout all the control bars
		CControlBar * pBar = GetDockedControlBar(nPos);
		void * pVoid = m_arrBars[nPos];

		if( pBar != NULL )
		{
			CRect rcBarWin, rcBarClient;
			pBar->GetWindowRect( &rcBarWin );
			pBar->ScreenToClient( & rcBarWin );
			pBar->GetClientRect( &rcBarClient );
			CSize sizeBarMin =
				rcBarWin.Size() - rcBarClient.Size();

			if(	pBar->IsKindOf(RUNTIME_CLASS(CExtControlBar)) )
			{
				if( ! ((CExtControlBar*)pBar)->m_bFixedMode )
				{
					sizeBarMin =
						CSize(
							((CExtControlBar *)pBar)->_CalcDesiredMinHW(),
							((CExtControlBar *)pBar)->_CalcDesiredMinVH()
							);
				} // if( ! ((CExtControlBar*)pBar)->m_bFixedMode )
			} // if(	pBar->IsKindOf(RUNTIME_CLASS(CExtControlBar)) )
			if( pBar->IsVisible() )
			{
				// get ideal rect for bar
				DWORD dwMode = 0;
				if(	(pBar->m_dwStyle & CBRS_SIZE_DYNAMIC)
					&&
					(pBar->m_dwStyle & CBRS_FLOATING)
					)
					dwMode |= LM_HORZ | LM_MRUWIDTH;
				else if(pBar->m_dwStyle & CBRS_ORIENT_HORZ)
					dwMode |= LM_HORZ | LM_HORZDOCK;
				else
					dwMode |=  LM_VERTDOCK;

				CSize sizeBar =
					pBar->CalcDynamicLayout(-1, dwMode);
				BOOL bIsMenuBar = FALSE;

				if( pBar->IsKindOf(RUNTIME_CLASS(CExtMenuControlBar)) )
				{
					bIsMenuBar = TRUE;
					if(dwMode & LM_HORZDOCK)
						sizeBar.cx = sizeMax.cx;
					else if(dwMode & LM_VERTDOCK)
						sizeBar.cy = sizeMax.cy;
				}

				CRect rc(pt, sizeBar);

				// get current rect for bar
				CRect rcBar;
				pBar->GetWindowRect( &rcBar );
				ScreenToClient( &rcBar );

				BOOL bMenuIsCutted = FALSE;

				if( bHorz )
				{
					// Offset Calculated Rect out to Actual
					if(	rcBar.left > rc.left
						&& !m_bFloating
						)
						rc.OffsetRect(
							rcBar.left - rc.left,
							0
							);

					// If ControlBar goes off the right, then right justify
					if(	rc.right > sizeMax.cx
						&& !m_bFloating
						)
					{
						int x = rc.Width();
						x = max(sizeMax.cx - x, pt.x);
						rc.OffsetRect(
							x - rc.left,
							0
							);
						if( bIsMenuBar )
							bMenuIsCutted = TRUE;
						if(	rc.right  > sizeMax.cx )
							rc.right -= rc.right - sizeMax.cx;
					}

					// If ControlBar has been wrapped, then left justify
					if( bWrapped )
					{
						bWrapped = FALSE;
						rc.OffsetRect( -rc.left, 0 );

					}
					// If ControlBar is completely invisible, then wrap it
					else if(
						rc.Width() < sizeBarMin.cx
						||
						(rc.left >= sizeMax.cx || bMenuIsCutted )
						&&
						(nPos > 0) && (m_arrBars[nPos - 1] != NULL)
						)
					{
						if(	!pBar->IsKindOf(RUNTIME_CLASS(CExtControlBar))
							||	(
								pBar->IsKindOf(RUNTIME_CLASS(CExtControlBar))
								&&
								((CExtControlBar*)pBar)->m_bFixedMode
								)
							)
						{
							m_arrBars.InsertAt(
								nPos,
								(CObject*)NULL
								);
							pBar = NULL;
							pVoid = NULL;
							bWrapped = TRUE;
						}
					}
					if( !bWrapped )
					{
						if(rc != rcBar)
						{
							if(	!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING)
								)
								pBar->m_pDockContext->
									m_rectMRUDockPos = rc;
							AfxRepositionWindow(
								&layout,
								pBar->m_hWnd,
								&rc
								);
						}
						pt.x = rc.left + sizeBar.cx;
						nWidth = max(nWidth, sizeBar.cy);
					} // if( !bWrapped )
				} // if( bHorz )
				else
				{
					// Offset Calculated Rect out to Actual
					if(	rcBar.top > rc.top
						&& !m_bFloating
						)
						rc.OffsetRect(
							0,
							rcBar.top - rc.top
							);

					// If ControlBar goes off the bottom, then bottom justify
					if(	rc.bottom > sizeMax.cy
						&& !m_bFloating
						)
					{
						int y = rc.Height();
						y = max(sizeMax.cy - y, pt.y);
						rc.OffsetRect(
							0,
							y - rc.top
							);
						if(bIsMenuBar)
							bMenuIsCutted = TRUE;
						if(	rc.bottom  > sizeMax.cy )
							rc.bottom -= rc.bottom - sizeMax.cy;
					}

					// If ControlBar has been wrapped, then top justify
					if( bWrapped )
					{
						bWrapped = FALSE;
						rc.OffsetRect( 0, -rc.top );
					}
					// If ControlBar is completely invisible, then wrap it
					else if(
						rc.Height() < sizeBarMin.cy
						||
						(rc.top >= sizeMax.cy || bMenuIsCutted )
						&& (nPos > 0)
						&& (m_arrBars[nPos - 1] != NULL)
						)
					{
						if(	!pBar->IsKindOf(RUNTIME_CLASS(CExtControlBar)) 
							||	(
								pBar->IsKindOf(RUNTIME_CLASS(CExtControlBar))
								&&
								((CExtControlBar*)pBar)->m_bFixedMode
								)
							)
						{
							m_arrBars.InsertAt(
								nPos,
								(CObject*)NULL
								);
							pBar = NULL;
							pVoid = NULL;
							bWrapped = TRUE;
						}
					}

					if( !bWrapped )
					{
						if(rc != rcBar)
						{
							if(	!m_bLayoutQuery
								&& !(pBar->m_dwStyle & CBRS_FLOATING)
								&& pBar->m_pDockContext != NULL
								)
								pBar->m_pDockContext->
									m_rectMRUDockPos = rc;
							AfxRepositionWindow(
								&layout,
								pBar->m_hWnd,
								&rc
								);
						}
						pt.y = rc.top + sizeBar.cy;
						nWidth = max(nWidth, sizeBar.cx);
					} // if( !bWrapped )
				} // else from if( bHorz )
			} // if( pBar->IsVisible() )

			if( !bWrapped )
				// handle any delay/show hide for the bar
				pBar->RecalcDelayShow( &layout );
		} // if( pBar != NULL )
		else
		{
			if( g_bExtendedRepositioning )
			{
				// try to remove wrapping:
				// are we have free space in the end of previouse row?
				if( nPos > 0 && nPos != m_arrBars.GetSize()-1 )
				{
					int nPosPrev = nPos-1;
					CControlBar * pPrevBar = NULL;
					do
					{
						pPrevBar = GetDockedControlBar(nPosPrev--);
						if( pPrevBar != NULL
							&& pPrevBar->IsVisible()
							&& (!pPrevBar->IsFloating())
							)
						{
							if( pPrevBar->IsKindOf(RUNTIME_CLASS(CExtMenuControlBar)) )
							{
								pPrevBar = NULL;
								break;
							}

							// get ideal rect for prev bar
							DWORD dwMode = 0;
							if(	(pPrevBar->m_dwStyle & CBRS_SIZE_DYNAMIC)
								&&
								(pPrevBar->m_dwStyle & CBRS_FLOATING)
								)
								dwMode |= LM_HORZ | LM_MRUWIDTH;
							else if(pPrevBar->m_dwStyle & CBRS_ORIENT_HORZ)
								dwMode |= LM_HORZ | LM_HORZDOCK;
							else
								dwMode |=  LM_VERTDOCK;

							CSize sizePrevBar =
								pPrevBar->CalcDynamicLayout(-1, dwMode);

							CRect rcPrev(pt, sizePrevBar);

							if( bHorz )
							{
								if(	rcPrev.right > sizeMax.cx
									&& !m_bFloating
									)
									pPrevBar = NULL;
							}
							else
							{
								if(	rcPrev.bottom > sizeMax.cy
									&& !m_bFloating
									)
									pPrevBar = NULL;
							}
							if( pPrevBar != NULL )
								break;
						}
						pPrevBar = NULL;
					} while( nPosPrev >= 0 );
					if( pPrevBar != NULL )
					{
						m_arrBars.RemoveAt(nPos);
						nPos--;
						continue;
					}
				} // if( nPos > 0 && nPos != m_arrBars.GetSize()-1 )
			} // if( g_bExtendedRepositioning )
		} // else from if( pBar != NULL )

		if( pBar == NULL && pVoid == NULL && nWidth != 0 )
		{
			// end of row because pBar == NULL
			if( bHorz )
			{
				pt.y += nWidth;
				sizeFixed.cx = max(sizeFixed.cx, pt.x);
				sizeFixed.cy = max(sizeFixed.cy, pt.y);
				pt.x = 0;
				sizeFixed.cy--;
			}
			else
			{
				pt.x += nWidth;
				sizeFixed.cx = max(sizeFixed.cx, pt.x);
				sizeFixed.cy = max(sizeFixed.cy, pt.y);
				pt.y = 0;
				sizeFixed.cx--;
			}
			nWidth = 0;
		}
	} // layout all the control bars
	if( !m_bLayoutQuery )
	{
		VERIFY( layout.hDWP != NULL );
		if( layout.hDWP != NULL )
		{
			VERIFY( ::EndDeferWindowPos(layout.hDWP) );
		}
	} // if( !m_bLayoutQuery )

	// adjust size for borders on the dock bar itself
CRect rc( 0, 0, 0, 0 );
	CalcInsideRect(rc, bHorz);
	if( (!bStretch || !bHorz) && sizeFixed.cx != 0 )
		sizeFixed.cx +=
			-rc.right + rc.left
			+ g_bControlBarFixSizePixel ? 1 : 0;
	if(	(!bStretch || bHorz) && sizeFixed.cy != 0 )
		sizeFixed.cy +=
			-rc.bottom + rc.top
			+ g_bControlBarFixSizePixel ? 1 : 0;

	return sizeFixed;
}