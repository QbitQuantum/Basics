double GERBVIEW_FRAME::BestZoom()
{
    GERBER_DRAW_ITEM* item = GetLayout()->m_Drawings;

    // gives a minimal value to zoom, if no item in list
    if( item == NULL  )
        return ZOOM_FACTOR( 350.0 );

    EDA_RECT bbox = GetLayout()->ComputeBoundingBox();

    wxSize  size = m_canvas->GetClientSize();

    double  x   = (double) bbox.GetWidth() / (double) size.x;
    double  y   = (double) bbox.GetHeight() / (double) size.y;
    GetScreen()->SetScrollCenterPosition( bbox.Centre() );

    double  best_zoom = std::max( x, y );
    return best_zoom;
}