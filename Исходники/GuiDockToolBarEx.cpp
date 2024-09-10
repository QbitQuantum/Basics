void CDockButton::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    CBrush cb;
    COLORREF m_clrBorder=GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style);
    COLORREF m_clrFace=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
    CPen cp(PS_SOLID,1,m_clrFace);
    CPen* cpold=dc.SelectObject(&cp);
    CRect m_rect;
    GetClientRect(m_rect);
    cb.CreateSolidBrush(m_clrFace);
    if (GuiDrawLayer::m_Style== GUISTYLE_XP)
        dc.FillRect(m_rect,&cb);
    else
    {
        CGradient M(CSize(m_rect.Width(),m_rect.Height()));
        if (m_nDockBarAling ==AFX_IDW_DOCKBAR_LEFT || m_nDockBarAling ==AFX_IDW_DOCKBAR_RIGHT)
            M.PrepareCaptionVert(&dc,GuiDrawLayer::m_Style);
        else
            M.PrepareCaption(&dc,GuiDrawLayer::m_Style);
        M.Draw(&dc,m_rect.left,m_rect.top,0,0,m_rect.Width(),m_rect.Height(),SRCCOPY);
    }

    dc.Draw3dRect(m_rect,m_clrBorder,m_clrBorder);
    GuiDrawLayer::DrawIcon(&dc,CPoint(m_rect.left+2,m_rect.top+2),m_szBtn,m_hIcon);

    switch(m_nDockBarAling)
    {


    case AFX_IDW_DOCKBAR_TOP:
        dc.MoveTo(m_rect.left,m_rect.top);
        dc.LineTo(m_rect.right,m_rect.top);
        if(m_hIcon != NULL)
            m_rect.left+=m_szBtn.cx+4;
        DrawTextHorz(&dc,m_rect);
        break;
    case AFX_IDW_DOCKBAR_LEFT:
        dc.MoveTo(m_rect.left,m_rect.top);
        dc.LineTo(m_rect.left,m_rect.bottom);
        if(m_hIcon != NULL)
            m_rect.top+=m_szBtn.cy+4;
        DrawTextVert(&dc,m_rect);
        break;
    case AFX_IDW_DOCKBAR_RIGHT:
        dc.MoveTo(m_rect.right-1,m_rect.top);
        dc.LineTo(m_rect.right-1,m_rect.bottom);
        if(m_hIcon != NULL)
            m_rect.top+=m_szBtn.cy+4;
        DrawTextVert(&dc,m_rect);
        break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        dc.MoveTo(m_rect.left,m_rect.bottom-1);
        dc.LineTo(m_rect.right,m_rect.bottom-1);
        if(m_hIcon != NULL)
            m_rect.left+=m_szBtn.cx+4;
        DrawTextHorz(&dc,m_rect);
        break;
    }
    dc.SelectObject(cpold);

}