    RECT SCaret::Draw(IRenderTarget *pRT,int x, int y,BOOL bErase)
    {
        SWindow * pOwner = SWindowMgr::GetWindow(m_owner);
        SASSERT(pOwner);
        SASSERT(pOwner->IsFocusable());
        
        CAutoRefPtr<IRenderTarget> pRTCaret;
        GETRENDERFACTORY->CreateRenderTarget(&pRTCaret,0,0);
        pRTCaret->SelectObject(m_bmpCaret);

        CSize szCaret = m_bmpCaret->Size();
        CRect rcCaret(CPoint(x,y),szCaret);
        CRect rcWnd = pOwner->GetClientRect();
        SWindow *pWnd = pOwner->GetParent();
        while(pWnd)
        {
            CRect rcLimit = pWnd->GetClientRect();
            rcWnd = rcWnd & rcLimit;
            pWnd = pWnd->GetParent();
        }
        pOwner->GetContainer()->FrameToHost(rcWnd);
        CRect rcCaretShow = rcCaret & rcWnd;
        
        pRT->BitBlt(&rcCaretShow,pRTCaret,rcCaretShow.left - rcCaret.left,rcCaretShow.top - rcCaret.top,DSTINVERT);
        return rcCaretShow;
    }