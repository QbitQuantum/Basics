void wxStdRenderer::DrawFrameIcon(wxDC& dc,
                                  const wxRect& rect,
                                  const wxIcon& icon,
                                  int flags)
{
    if ( icon.Ok() )
    {
        wxRect r = GetFrameClientArea(rect, flags & ~wxTOPLEVEL_TITLEBAR);
        dc.DrawIcon(icon, r.x, r.y);
    }
}