    void Update()
    {
        // maintain top/left pos
        CRect rcwnd;
        GetWindowRect(rcwnd);

        // Clear text
        m_wndRTF.SetWindowText(NULL);

        // Stream in new text...
        CComVariant bstr;
        std::string text;
        if(m_vertex)
            m_vertex->GetProperty(PROP_TOOLTIP, bstr);
        if(m_edge)
            m_edge->GetProperty(PROP_TOOLTIP, bstr);
        if (bstr.vt == VT_BSTR)
            text = CW2A(bstr.bstrVal);
        LPCSTR pstrText=text.c_str();
        RtfStream st = { pstrText, 0 }; 
        EDITSTREAM es = { 0 };
        es.dwCookie = (DWORD) &st;
        es.dwError = 0;
        es.pfnCallback = _StreamReadCallback;
        UINT uFormat = pstrText[0]=='{' ? SF_RTF : SF_TEXT;
        m_wndRTF.StreamIn(uFormat, es);

        // Request new layout
        int cx = DEFAULT_WIDTH;
        CRect rc( 0, 0, cx, DEFAULT_HEIGHT);
        m_wndRTF.ResizeClient(cx, DEFAULT_HEIGHT, FALSE);
        m_wndRTF.SetRect(&rc);
        m_wndRTF.RequestResize();
        CRect rcRTF(m_rcRTF);
        CRect rcOrig(m_rcRTF);

        // Resize RTF control until the height changes. This will indicate
        // the minimum/optimal width of the text.
        int iStep = 30;
        while( true ) 
        {
            ATLASSERT(cx>0);
            CRect rc( 0, 0, cx - iStep, DEFAULT_HEIGHT);
            m_wndRTF.ResizeClient(cx - iStep, DEFAULT_HEIGHT, FALSE);
            m_wndRTF.SetRect(&rc);
            m_wndRTF.RequestResize();
            if(rcRTF.Height() != m_rcRTF.Height()) 
            {
                if( iStep <= 1 ) break;
                iStep /= 2;
            }
            else 
            {
                cx -= iStep;
                if( cx <= 0 ) 
                {
                    rcRTF = rcOrig;
                    break;
                }
                rcRTF = m_rcRTF; // Apply better width
            }
        }

        bool notnormal=IsIconic() || IsZoomed();
        m_wndRTF.SetWindowPos(0, &rcRTF, (notnormal?0:SWP_SHOWWINDOW) | SWP_NOACTIVATE | SWP_NOZORDER);
        if(!notnormal)
        {
            DWORD exstyle=GetWndExStyle(0);
            rcwnd.right=rcwnd.left+rcRTF.Width();
            rcwnd.bottom=rcwnd.top+rcRTF.Height();
            ::AdjustWindowRectEx(&rcwnd, GetWndStyle(0), FALSE, exstyle);
            // finally, keep it inside screen bounds
            CRect rcScreen;
            ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcScreen, 0);
            if(rcwnd.right > rcScreen.right) 
                rcwnd.OffsetRect(-(rcwnd.right-rcScreen.right), 0);
            if(rcwnd.top < rcScreen.top) 
                rcwnd.OffsetRect(0, rcScreen.top-rcwnd.top);

            SetWindowPos(0, rcwnd, SWP_NOZORDER);
        }
    }