void CLegendWnd::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CRect rect;
    GetClientRect(&rect);

    CMemDC MemDC(&dc, rect);
    MemDC.FillSolidRect(&rect, ::GetSysColor(COLOR_BTNFACE));
    //----------------------------------------------------
    CDC dcBmp;
    dcBmp.CreateCompatibleDC(&dc);
    CBitmap* pOldBmp = dcBmp.SelectObject(&m_bmpLegend);

    //draw all legend
    int nX=0, nY=0;
    LegendMap::iterator it;
    for(it=m_legendMap.begin(); it!=m_legendMap.end(); it++)
    {
        int nXOffset = 0;
        switch(it->second.sel_state)
        {
        case SS_NORMAL:
            break;
        case SS_HORVER:
            MemDC.FillSolidRect(nX, nY, nLegendWidth+2, nLegendHeight+2, ::GetSysColor(COLOR_ACTIVECAPTION));
            break;
        case SS_SELECT:
            MemDC.Draw3dRect(nX, nY, nLegendWidth+2, nLegendHeight+2,
                             GetSysColor(COLOR_BTNSHADOW ), GetSysColor(COLOR_BTNHIGHLIGHT));
            break;
        }

        switch(it->second.state)
        {
        case LS_DIE:
            nXOffset = 0;
            break;

        case LS_LIVE_0:
            nXOffset = 9;
            break;

        case LS_LIVE_1:
            nXOffset = 18;
            break;

        case LS_FAULT:
            nXOffset = 27;
            break;
        }
        MemDC.BitBlt(nX+1, nY+1, nLegendWidth, nLegendHeight, &dcBmp, nXOffset, 0, SRCCOPY);

        nX += nLegendWidth+2;
        if(nX + nLegendWidth+2 >= rect.Width())
        {
            nY += nLegendHeight+2;
            nX = 0;
        }
    }

    dcBmp.SelectObject(pOldBmp);
    //----------------------------------------------------
}