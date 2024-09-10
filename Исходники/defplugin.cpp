void wxIFMDefaultPlugin::OnPaintBorder(wxIFMPaintEvent &event)
{
    wxIFMComponent *component = event.GetComponent();

    // don't need to paint if we arent visible
    if( !component->IsVisible() )
        return;

    // get background rect to draw borders around
    wxIFMRectEvent rectevt(wxEVT_IFM_GETBACKGROUNDRECT, component);
    GetIP()->ProcessPluginEvent(rectevt);

    // get border rect
    wxRect rect = rectevt.GetRect();

    rect.y--;
    rect.x--;
    rect.width++;
    rect.height++;

    //! \todo Globalize colour storage
    //wxPen pen_light(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNHIGHLIGHT));
    //wxPen pen_dark(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
    wxPen border_pen(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));
    wxDC &dc = event.GetDC();

    // paint borders
    // top
    if( component->m_borders.top )
    {
        border_pen.SetWidth(component->m_borders.top);
        dc.SetPen(border_pen);
        dc.DrawLine(rect.x, rect.y, rect.x + rect.width, rect.y);
    }

    // left
    if( component->m_borders.left )
    {
        border_pen.SetWidth(component->m_borders.left);
        dc.SetPen(border_pen);
        dc.DrawLine(rect.x, rect.y, rect.x, rect.y + rect.height);
    }

    // right
    if( component->m_borders.right )
    {
        border_pen.SetWidth(component->m_borders.right);
        dc.SetPen(border_pen);
        dc.DrawLine(rect.x + rect.width, rect.y, rect.x + rect.width, rect.y + rect.height + 1);
    }

    // bottom
    if( component->m_borders.bottom )
    {
        border_pen.SetWidth(component->m_borders.bottom);
        dc.SetPen(border_pen);
        dc.DrawLine(rect.x, rect.y + rect.height, rect.x + rect.width + 1, rect.y + rect.height);
    }
}