void wxPanel::OnEraseBackground(wxEraseEvent& event)
{
    wxDC& dc = *event.GetDC();

    const wxSize clientSize = GetClientSize();
    const wxSize bitmapSize = m_bitmapBg.GetSize();

    for ( int x = 0; x < clientSize.x; x += bitmapSize.x )
    {
        for ( int y = 0; y < clientSize.y; y += bitmapSize.y )
        {
            dc.DrawBitmap(m_bitmapBg, x, y);
        }
    }
}