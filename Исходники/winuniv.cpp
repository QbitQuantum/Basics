// the event handler executed when the window background must be painted
void wxWindow::OnErase(wxEraseEvent& event)
{
    if ( !m_renderer )
    {
        event.Skip();

        return;
    }

    DoDrawBackground(*event.GetDC());

#if wxUSE_SCROLLBAR
    // if we have both scrollbars, we also have a square in the corner between
    // them which we must paint
    if ( m_scrollbarVert && m_scrollbarHorz )
    {
        wxSize size = GetSize();
        wxRect rectClient = GetClientRect(),
               rectBorder = m_renderer->GetBorderDimensions(GetBorder());

        wxRect rectCorner;
        rectCorner.x = rectClient.GetRight() + 1;
        rectCorner.y = rectClient.GetBottom() + 1;
        rectCorner.SetRight(size.x - rectBorder.width);
        rectCorner.SetBottom(size.y - rectBorder.height);

        if ( GetUpdateRegion().Contains(rectCorner) )
        {
            m_renderer->DrawScrollCorner(*event.GetDC(), rectCorner);
        }
    }
#endif // wxUSE_SCROLLBAR
}