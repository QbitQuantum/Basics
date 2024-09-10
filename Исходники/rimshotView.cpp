LRESULT CRimshotView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    CRect rect;
    CBitmap *pBmp;

    switch (message)
    {
    case DRAW_COMPLETE_MSG:
	GetClientRect(&rect);
	if (m_Draw.max_copy_size.cx < rect.Width() || m_Draw.max_copy_size.cy < rect.Height())
	{
	    m_Draw.max_copy_size.cx = max(m_Draw.max_copy_size.cx, rect.Width());
	    m_Draw.max_copy_size.cy = max(m_Draw.max_copy_size.cy, rect.Height());
	    pBmp = new CBitmap();
	    pBmp->CreateDiscardableBitmap(GetDC(), m_Draw.max_copy_size.cx, m_Draw.max_copy_size.cy);
	    m_Draw.pCopyCanvas->SelectObject(pBmp);
	    delete m_Draw.pCopyBitmap;
	    m_Draw.pCopyBitmap = pBmp;
	}
	m_Draw.copy_size.cx = rect.Width();
	m_Draw.copy_size.cy = rect.Height();
	if (WaitForSingleObject(m_Draw.hMutex, 2000) == WAIT_OBJECT_0)
	{
	    m_Draw.pCopyCanvas->BitBlt(0, 0, rect.Width(), rect.Height(), m_Draw.pCanvas, 0, 0, SRCCOPY);
	    ReleaseMutex(m_Draw.hMutex);
	}
	Invalidate(FALSE);
	break;
    }
    return CView::WindowProc(message, wParam, lParam);
}