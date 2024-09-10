void CResizableLayout::ArrangeLayout()
{
	CWnd* pParent = GetResizableWnd();

	// get parent window's rect
	CRect rectParent;
	GetTotalClientRect(&rectParent);

	// init some vars
	BOOL bCallbackPassed = FALSE;
	int i, count = (int)m_arrLayout.GetSize();
	HDWP hdwp = BeginDeferWindowPos(count);

	for (i=0; i<count; ++i)
	{
		LayoutInfo layout = m_arrLayout[i];
		
		if (layout.hWnd == NULL)	// callback
		{
			if (!bCallbackPassed)	// first time only
			{
				bCallbackPassed = TRUE;
				// update previous controls
				EndDeferWindowPos(hdwp);
				// start again for callback controls
				hdwp = BeginDeferWindowPos(count-i);
			}
			// callbacks are added at the end, so that
			// you don't have multiple screen updates

			if (!ArrangeLayoutCallback(layout))	// request data
				continue;
		}

		CRect rectChild, newrc;
		CWnd* pWnd = CWnd::FromHandle(layout.hWnd); // temporary solution

		pWnd->GetWindowRect(&rectChild);
		pParent->ScreenToClient(&rectChild);
		
		// calculate new top-left corner

		newrc.left = layout.sizeMarginTL.cx + rectParent.Width() * layout.sizeTypeTL.cx / 100;
		newrc.top = layout.sizeMarginTL.cy + rectParent.Height() * layout.sizeTypeTL.cy / 100;
		
		// calculate new bottom-right corner

		newrc.right = layout.sizeMarginBR.cx + rectParent.Width() * layout.sizeTypeBR.cx / 100;
		newrc.bottom = layout.sizeMarginBR.cy + rectParent.Height() * layout.sizeTypeBR.cy / 100;

		if (!newrc.EqualRect(&rectChild))
		{
			if (layout.bAdjHScroll)
			{
				// needs repainting, due to horiz scrolling
				int diff = newrc.Width() - rectChild.Width();
				int max = pWnd->GetScrollLimit(SB_HORZ);
			
				layout.bNeedRefresh = FALSE;
				if (max > 0 && pWnd->GetScrollPos(SB_HORZ) > max - diff)
				{
					layout.bNeedRefresh = TRUE;
				}
			}

			// set flags 
			DWORD flags = SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREPOSITION;
			//if (layout.bNeedRefresh)
			//	flags |= SWP_NOCOPYBITS;
			if (newrc.TopLeft() == rectChild.TopLeft())
				flags |= SWP_NOMOVE;
			if (newrc.Size() == rectChild.Size())
				flags |= SWP_NOSIZE;
			
			hdwp = DeferWindowPos(hdwp, layout.hWnd, NULL, newrc.left, newrc.top,
				newrc.Width(), newrc.Height(), flags);
		}
	}
	// go re-arrange child windows
	EndDeferWindowPos(hdwp);

	// refresh those that need
	for (i=0; i<count; ++i)
	{
		LayoutInfo& layout = m_arrLayout[i];
	
		if (layout.bNeedRefresh)
		{
			::RedrawWindow(layout.hWnd, NULL, NULL, RDW_INVALIDATE|RDW_NOFRAME);
		//	::InvalidateRect(layout.hWnd, NULL, TRUE);
		//	::UpdateWindow(layout.hWnd);
		}
	}
}