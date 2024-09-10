void CLeftPanelDlgBar::OnPaint() 
{
	CPaintDC dc (this); // device context for painting

	CDC dcMem;
	dcMem.CreateCompatibleDC (&dc);
	CBrush brush (::GetSysColor (COLOR_3DFACE));

	CMDIChildWnd* pChild = ((CMDIFrameWnd*) AfxGetMainWnd ())->MDIGetActive ();

	CRect r;
	GetClientRect (&r);

	if (pChild == NULL)
	{
		dc.FillRect (&r, &brush);
		goto __end;
	}

	CCdCoverCreator2Doc* pDoc = (CCdCoverCreator2Doc*) pChild->GetActiveDocument ();
	if (pDoc == NULL)
	{
		// look whether the last doc is still valid
		POSITION pos = AfxGetApp ()->GetFirstDocTemplatePosition ();
		CDocTemplate* pDocTmpl = AfxGetApp ()->GetNextDocTemplate (pos);
		bool bIsValid = false;
		for (pos = pDocTmpl->GetFirstDocPosition (); pos; )
			if (pDocTmpl->GetNextDoc (pos) == m_pLastDoc)
			{
				bIsValid = true;
				break;
			}

		if (bIsValid)
			pDoc = m_pLastDoc;
		else
			m_pLastDoc = NULL;
	}
	else
		m_pLastDoc = pDoc;

	if (pDoc == NULL)
	{
		dc.FillRect (&r, &brush);
		goto __end;
	}

	CRect rect;
	GetClientRect (rect);
	rect.DeflateRect (5, 5, 5, 5);

	if (pDoc->m_pStyle != NULL)
	{
		CCdCoverCreator2View* pView = (CCdCoverCreator2View*) pChild->GetActiveView ();
		if (pView == NULL)
			goto __end;

		int nHeight = (rect.Width () / 5) * 4;
		CRenderDC rdc (&dc, nHeight, pView->GetDocument ()->m_pStyle);

		m_y[Cover] = 5;
		m_y[Back] = m_y[Cover] + rdc.GetHeight (Cover) + 10;
		m_y[Inlay] = m_y[Back] + rdc.GetHeight (Back) + 10;
		m_y[Label] = m_y[Inlay] + rdc.GetHeight (Inlay) + 10;
		m_y[Booklet] = m_y[Label] + rdc.GetHeight (Label) + 10;

		if (m_bRedraw)
		{
			CLabelRenderer renderer (pDoc->m_pTracks, pDoc->m_pDataCDInfo,
				reinterpret_cast<CBackgroundInfo**> (&(pDoc->m_pBackground)),
				pDoc->m_listFloatingObjects, *(pDoc->m_pStyle));

			for (int i = 0; i < NUM_RENDER_TYPES - 1; i++)
			{
				if ((RenderType) i == Booklet)
					continue;

				CRect rectBmp (0, 0, rdc.GetWidth ((RenderType) i) + 5, /*nHeight*/(m_y[i + 1] - m_y[i]) + 5);

				m_Bitmap[i].DeleteObject ();
				m_Bitmap[i].CreateCompatibleBitmap (&dc, rectBmp.right, rectBmp.bottom);

				// render
				dcMem.SelectObject (&m_Bitmap[i]);
				dcMem.FillRect (rectBmp, &brush);

				renderer.Render (CRenderDC (&dcMem, nHeight, pDoc->m_pStyle), (RenderType) i, true);
			}

			m_bRedraw = false;
		}

		// draw the bitmaps
		int x[] = {
			(rect.Width () - rdc.GetWidth (Cover)) / 2 + 5,
			(rect.Width () - rdc.GetWidth (Back)) / 2 + 5,
			(rect.Width () - rdc.GetWidth (Inlay)) / 2 + 5,
			(rect.Width () - rdc.GetWidth (Label)) / 2 + 5,
			(rect.Width () - rdc.GetWidth (Cover)) / 2 + 5
		};

		dc.SetViewportOrg (x[Booklet], m_y[Booklet]);
		DrawBooklet (&dc, rdc.GetWidth (Cover), rdc.GetWidth (Cover) / 2, pDoc, pView->GetRenderType ());
		dc.SetViewportOrg (0, 0);

		CBrush* pOldBrush = dc.GetCurrentBrush ();

		for (int i = 0; i < NUM_RENDER_TYPES; i++)
		{
			CRect rectArea (rect.left, m_y[i], rect.right,
				m_y[i] + ((RenderType) i == Booklet ? rdc.GetWidth (Cover) / 2 : rdc.GetHeight ((RenderType) i)));

			if ((RenderType) i != Booklet)
			{
				dcMem.SelectObject (m_Bitmap[i]);

				if (pDoc->m_pStyle->m_bHasRenderType[i])
					dc.SelectStockObject (WHITE_BRUSH);
				else
				{
					dc.SetTextColor (RGB (0xff, 0xff, 0xff));
					dc.SetBkColor (RGB (0x7f, 0x7f, 0x7f));
					dc.SelectObject (dc.GetHalftoneBrush ());
				}

				//dc.BitBlt (x[i], m_y[i], rdc.GetWidth ((RenderType) i) + 5, /*nHeight*/(m_y[i + 1] - m_y[i]) + 5, &dcMem, 0, 0, MERGECOPY);
				dc.BitBlt (x[i], m_y[i], rectArea.Width (), rectArea.Height () + 4, &dcMem, 0, 0, MERGECOPY);
			}

			// marker
			Mark (&dc, rectArea, pView->GetRenderType () != (RenderType) i);
		}

		dc.SelectObject (pOldBrush);
	}

__end:

#ifdef PEROUTKA_FEDORISIN
	CBitmap* pOldBmp = (CBitmap*) dcMem.SelectObject (m_bmpLogo);
	dc.FillSolidRect (0, r.bottom - 32, 148, 32, RGB (0xff, 0xff, 0xff));
	dc.BitBlt ((148 - 80) / 2, r.bottom - 32, 80, 32, &dcMem, 0, 0, SRCCOPY);
//	dcMem.SelectObject (pOldBmp);
#endif

	dcMem.DeleteDC ();
	brush.DeleteObject ();
}