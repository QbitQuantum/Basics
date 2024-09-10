void wxDynamicSashWindowImpl::DrawSash(int x, int y) const
{
    int i, j;

    wxScreenDC dc;
    dc.StartDrawingOnTop(m_container);

    wxBitmap bmp(8, 8);
    wxMemoryDC bdc;
    bdc.SelectObject(bmp);
    bdc.DrawRectangle(-1, -1, 10, 10);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if ((i + j) & 1)
                bdc.DrawPoint(i, j);
        }
    }

    wxBrush brush(bmp);
    dc.SetBrush(brush);
    dc.SetLogicalFunction(wxXOR);

    if ((m_dragging == DSR_CORNER) &&
        (m_window->GetWindowStyle() & wxDS_DRAG_CORNER) != 0)
    {
        int cx = 0;
        int cy = 0;

        m_container->ClientToScreen(&cx, &cy);
        m_container->ClientToScreen(&x, &y);

        if (cx < x && cy < y)
        {
            dc.DrawRectangle(cx - 2, cy - 2, x - cx + 4, 4);
            dc.DrawRectangle(x - 2, cy + 2, 4, y - cy);
            dc.DrawRectangle(cx - 2, cy + 2, 4, y - cy);
            dc.DrawRectangle(cx + 2, y - 2, x - cx - 4, 4);
        }
    }
    else
    {
        int body_w, body_h;
        m_container->GetClientSize(&body_w, &body_h);

        if (y < 0)
            y = 0;
        if (y > body_h)
            y = body_h;
        if (x < 0)
            x = 0;
        if (x > body_w)
            x = body_w;

        if (m_dragging == DSR_HORIZONTAL_TAB)
            x = 0;
        else
            y = 0;

        m_container->ClientToScreen(&x, &y);

        int w, h;
        w = body_w;  h = body_h;

        if (m_dragging == DSR_HORIZONTAL_TAB)
            dc.DrawRectangle(x, y - 2, w, 4);
        else
            dc.DrawRectangle(x - 2, y, 4, h);
    }

    dc.EndDrawingOnTop();
}