void CLayoutManager::OnEraseBkgnd(BOOL bPeek, HDC hDC)
{
	CDC * pDC = CDC::FromHandle(hDC);

	if (bPeek)
	{
		CWnd * pWnd;
		CRect r;
		CRgn rNew, rTmp;

		/* save */
		::GetClipRgn(pDC->m_hDC, (HRGN)m_rClip.m_hObject);

		/* refine */
		rNew.CreateRectRgn(0,0,0,0);
		for (pWnd = m_pWnd->GetWindow(GW_CHILD); 
		     pWnd;
		     pWnd = pWnd->GetNextWindow())
		{
			if (! pWnd->IsWindowVisible())
				continue;

			pWnd->GetWindowRect(&r);
			m_pWnd->ScreenToClient(&r);
			rTmp.CreateRectRgnIndirect(&r);	
			rNew.CombineRgn(&rNew, &rTmp, RGN_OR);
			rTmp.DeleteObject();
		}
		pDC->SelectClipRgn(&rNew, RGN_DIFF);
	}
	else
	{
		/* restore */
		pDC->SelectClipRgn(&m_rClip, RGN_COPY);
	}
}