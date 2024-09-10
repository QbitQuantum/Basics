void wxRibbonAUIArtProvider::DrawTool(
            wxDC& dc,
            wxWindow* WXUNUSED(wnd),
            const wxRect& rect,
            const wxBitmap& bitmap,
            wxRibbonButtonKind kind,
            long state)
{
    if(kind == wxRIBBON_BUTTON_TOGGLE)
    {
        if(state & wxRIBBON_TOOLBAR_TOOL_TOGGLED)
            state ^= wxRIBBON_TOOLBAR_TOOL_ACTIVE_MASK;
    }

    wxRect bg_rect(rect);
    bg_rect.Deflate(1);
    if((state & wxRIBBON_TOOLBAR_TOOL_LAST) == 0)
        bg_rect.width++;
    bool is_custom_bg = (state & (wxRIBBON_TOOLBAR_TOOL_HOVER_MASK |
        wxRIBBON_TOOLBAR_TOOL_ACTIVE_MASK)) != 0;
    bool is_split_hybrid = kind == wxRIBBON_BUTTON_HYBRID && is_custom_bg;

    // Background
    if(is_custom_bg)
    {
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(m_tool_hover_background_brush);
        dc.DrawRectangle(bg_rect.x, bg_rect.y, bg_rect.width, bg_rect.height);
        if(state & wxRIBBON_TOOLBAR_TOOL_ACTIVE_MASK)
        {
            wxRect active_rect(bg_rect);
            if(kind == wxRIBBON_BUTTON_HYBRID)
            {
                active_rect.width -= 8;
                if(state & wxRIBBON_TOOLBAR_TOOL_DROPDOWN_ACTIVE)
                {
                    active_rect.x += active_rect.width;
                    active_rect.width = 8;
                }
            }
            dc.SetBrush(m_tool_active_background_brush);
            dc.DrawRectangle(active_rect.x, active_rect.y, active_rect.width,
                active_rect.height);
        }
    }

    // Border
    if(is_custom_bg)
        dc.SetPen(m_toolbar_hover_borden_pen);
    else
        dc.SetPen(m_toolbar_border_pen);
    if((state & wxRIBBON_TOOLBAR_TOOL_FIRST) == 0)
    {
        wxColour existing;
        if(!dc.GetPixel(rect.x, rect.y + 1, &existing) ||
            existing != m_toolbar_hover_borden_pen.GetColour())
        {
            dc.DrawLine(rect.x, rect.y + 1, rect.x, rect.y + rect.height - 1);
        }
    }
    if(is_custom_bg)
    {
        wxRect border_rect(bg_rect);
        border_rect.Inflate(1);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(border_rect.x, border_rect.y, border_rect.width,
            border_rect.height);
    }

    // Foreground
    int avail_width = bg_rect.GetWidth();
    if(kind & wxRIBBON_BUTTON_DROPDOWN)
    {
        avail_width -= 8;
        if(is_split_hybrid)
        {
            dc.DrawLine(rect.x + avail_width + 1, rect.y,
                rect.x + avail_width + 1, rect.y + rect.height);
        }
        dc.DrawBitmap(m_toolbar_drop_bitmap, bg_rect.x + avail_width + 2,
            bg_rect.y + (bg_rect.height / 2) - 2, true);
    }
    dc.DrawBitmap(bitmap, bg_rect.x + (avail_width - bitmap.GetWidth()) / 2,
        bg_rect.y + (bg_rect.height - bitmap.GetHeight()) / 2, true);
}