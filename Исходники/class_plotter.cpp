void PLOTTER::sketchOval( const wxPoint& pos, const wxSize& aSize, double orient, int width )
{
    SetCurrentLineWidth( width );
    width = currentPenWidth;
    int radius, deltaxy, cx, cy;
    wxSize size( aSize );

    if( size.x > size.y )
    {
        std::swap( size.x, size.y );
        orient = AddAngles( orient, 900 );
    }

    deltaxy = size.y - size.x;       /* distance between centers of the oval */
    radius   = ( size.x - width ) / 2;
    cx = -radius;
    cy = -deltaxy / 2;
    RotatePoint( &cx, &cy, orient );
    MoveTo( wxPoint( cx + pos.x, cy + pos.y ) );
    cx = -radius;
    cy = deltaxy / 2;
    RotatePoint( &cx, &cy, orient );
    FinishTo( wxPoint( cx + pos.x, cy + pos.y ) );

    cx = radius;
    cy = -deltaxy / 2;
    RotatePoint( &cx, &cy, orient );
    MoveTo( wxPoint( cx + pos.x, cy + pos.y ) );
    cx = radius;
    cy = deltaxy / 2;
    RotatePoint( &cx, &cy, orient );
    FinishTo( wxPoint( cx + pos.x, cy + pos.y ) );

    cx = 0;
    cy = deltaxy / 2;
    RotatePoint( &cx, &cy, orient );
    Arc( wxPoint( cx + pos.x, cy + pos.y ),
         orient + 1800, orient + 3600,
         radius, NO_FILL );
    cx = 0;
    cy = -deltaxy / 2;
    RotatePoint( &cx, &cy, orient );
    Arc( wxPoint( cx + pos.x, cy + pos.y ),
         orient, orient + 1800,
         radius, NO_FILL );
}