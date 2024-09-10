LRESULT CControlBar::OnSizeParent(WPARAM, LPARAM lParam)
{
	AFX_SIZEPARENTPARAMS* lpLayout = (AFX_SIZEPARENTPARAMS*)lParam;
	DWORD dwStyle = RecalcDelayShow(lpLayout);

	if ((dwStyle & WS_VISIBLE) && (dwStyle & CBRS_ALIGN_ANY) != 0)
	{
		// align the control bar
		CRect rect;
		rect.CopyRect(&lpLayout->rect);

		CSize sizeAvail = rect.Size();  // maximum size available

		// get maximum requested size
		CSize size = CalcFixedLayout(lpLayout->bStretch,
			dwStyle & CBRS_ORIENT_HORZ);

		size.cx = min(size.cx, sizeAvail.cx);
		size.cy = min(size.cy, sizeAvail.cy);

		if (dwStyle & CBRS_ORIENT_HORZ)
		{
			lpLayout->sizeTotal.cy += size.cy;
			lpLayout->sizeTotal.cx = max(lpLayout->sizeTotal.cx, size.cx);
			if (dwStyle & CBRS_ALIGN_TOP)
				lpLayout->rect.top += size.cy;
			else if (dwStyle & CBRS_ALIGN_BOTTOM)
			{
				rect.top = rect.bottom - size.cy;
				lpLayout->rect.bottom -= size.cy;
			}
		}
		else if (dwStyle & CBRS_ORIENT_VERT)
		{
			lpLayout->sizeTotal.cx += size.cx;
			lpLayout->sizeTotal.cy = max(lpLayout->sizeTotal.cy, size.cy);
			if (dwStyle & CBRS_ALIGN_LEFT)
				lpLayout->rect.left += size.cx;
			else if (dwStyle & CBRS_ALIGN_RIGHT)
			{
				rect.left = rect.right - size.cx;
				lpLayout->rect.right -= size.cx;
			}
		}
		else
		{
			ASSERT(FALSE);      // can never happen
		}

		rect.right = rect.left + size.cx;
		rect.bottom = rect.top + size.cy;

#ifdef _MAC
		// account for the Macintosh grow box, if there is one
		CWnd* pWnd = GetParentFrame();
		if (pWnd != NULL)
		{
			DWORD dwWndStyle = pWnd->GetStyle();
			DWORD dwExStyle = pWnd->GetExStyle();

			if (!(dwExStyle & WS_EX_MDIFRAME) &&
				(dwExStyle & WS_EX_FORCESIZEBOX) &&
				!(dwWndStyle & (WS_VSCROLL|WS_HSCROLL)))
			{
				CRect rectParent;
				pWnd->GetClientRect(rectParent);

				if (dwStyle & CBRS_ALIGN_BOTTOM)
				{
					if (rect.bottom > rectParent.bottom - afxData.cxVScroll + 1)
						rect.right -= (afxData.cxVScroll - 1);
				}
				else if (dwStyle & CBRS_ALIGN_RIGHT)
				{
					if (rect.bottom > rectParent.bottom - afxData.cyHScroll + 1)
						rect.bottom -= (afxData.cxVScroll - 1);
				}
			}
		}
#endif

		// only resize the window if doing layout and not just rect query
		if (lpLayout->hDWP != NULL)
			AfxRepositionWindow(lpLayout, m_hWnd, &rect);
	}
	return 0;
}