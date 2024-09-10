void Route::RenderSegment( ocpnDC& dc, int xa, int ya, int xb, int yb, ViewPort &VP,
        bool bdraw_arrow, int hilite_width )
{
    //    Get the dc boundary
    int sx, sy;
    dc.GetSize( &sx, &sy );

    //    Try to exit early if the segment is nowhere near the screen
    wxRect r( 0, 0, sx, sy );
    wxRect s( xa, ya, 1, 1 );
    wxRect t( xb, yb, 1, 1 );
    s.Union( t );
    if( !r.Intersects( s ) ) return;

    //    Clip the line segment to the dc boundary
    int x0 = xa;
    int y0 = ya;
    int x1 = xb;
    int y1 = yb;

    //    If hilite is desired, use a Native Graphics context to render alpha colours
    //    That is, if wxGraphicsContext is available.....

    if( hilite_width ) {
        if( Visible == cohen_sutherland_line_clip_i( &x0, &y0, &x1, &y1, 0, sx, 0, sy ) ) {
            wxPen psave = dc.GetPen();

            wxColour y = GetGlobalColor( _T ( "YELO1" ) );
            wxColour hilt( y.Red(), y.Green(), y.Blue(), 128 );

            wxPen HiPen( hilt, hilite_width, wxSOLID );

            dc.SetPen( HiPen );
            dc.StrokeLine( x0, y0, x1, y1 );

            dc.SetPen( psave );
            dc.StrokeLine( x0, y0, x1, y1 );
        }
    } else {
        if( Visible == cohen_sutherland_line_clip_i( &x0, &y0, &x1, &y1, 0, sx, 0, sy ) )
            dc.StrokeLine( x0, y0, x1, y1 );
    }

    if( bdraw_arrow ) {
        //    Draw a direction arrow

        double theta = atan2( (double) ( yb - ya ), (double) ( xb - xa ) );
        theta -= PI / 2.;

        wxPoint icon[10];
        double icon_scale_factor = 100 * VP.view_scale_ppm;
        icon_scale_factor = fmin ( icon_scale_factor, 1.5 );              // Sets the max size
        icon_scale_factor = fmax ( icon_scale_factor, .10 );

        //    Get the absolute line length
        //    and constrain the arrow to be no more than xx% of the line length
        double nom_arrow_size = 20.;
        double max_arrow_to_leg = .20;
        double lpp = sqrt( pow( (double) ( xa - xb ), 2 ) + pow( (double) ( ya - yb ), 2 ) );

        double icon_size = icon_scale_factor * nom_arrow_size;
        if( icon_size > ( lpp * max_arrow_to_leg ) ) icon_scale_factor = ( lpp * max_arrow_to_leg )
                / nom_arrow_size;

        for( int i = 0; i < 7; i++ ) {
            int j = i * 2;
            double pxa = (double) ( s_arrow_icon[j] );
            double pya = (double) ( s_arrow_icon[j + 1] );

            pya *= icon_scale_factor;
            pxa *= icon_scale_factor;

            double px = ( pxa * sin( theta ) ) + ( pya * cos( theta ) );
            double py = ( pya * sin( theta ) ) - ( pxa * cos( theta ) );

            icon[i].x = (int) ( px ) + xb;
            icon[i].y = (int) ( py ) + yb;
        }
        wxPen savePen = dc.GetPen();
        dc.SetPen( *wxTRANSPARENT_PEN );
        dc.StrokePolygon( 6, &icon[0], 0, 0 );
        dc.SetPen( savePen );
    }
}