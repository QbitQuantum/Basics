void gray_out_image_on_dc( wxDC& dc, int width, int height )
{
    // assuming the pixels along the edges are of the background color
    wxColour bgCol;
    dc.GetPixel( 0, 0, &bgCol );

    wxPen darkPen ( wxSystemSettings::GetColour(wxSYS_COLOUR_3DSHADOW),1, wxSOLID );
    wxPen lightPen( wxSystemSettings::GetColour(wxSYS_COLOUR_3DHIGHLIGHT),1, wxSOLID );
    wxPen bgPen   ( bgCol,                1, wxSOLID );

    int* src  = create_array( width, height, MASK_BG );
    int* dest = create_array( width, height, MASK_BG );

    int x, y;
    for ( y = 0; y != height; ++y )
    {
        for ( x = 0; x != width; ++x )
        {
            wxColour col;
            dc.GetPixel( x,y, &col );

            GET_ELEM(src,x,y) = MAKE_INT_COLOR( col.Red(), col.Green(), col.Blue() );
        }
    }
    gray_out_pixmap( src, dest, width, height );

    for ( y = 0; y != height; ++y )
    {
        for ( x = 0; x != width; ++x )
        {
            int mask = GET_ELEM(dest,x,y);

            switch (mask)
            {
                case MASK_BG    : { dc.SetPen( bgPen );
                                    dc.DrawPoint( x,y ); break;
                                  }
                case MASK_DARK  : { dc.SetPen( darkPen );
                                    dc.DrawPoint( x,y ); break;
                                  }
                case MASK_LIGHT : { dc.SetPen( lightPen );
                                    dc.DrawPoint( x,y ); break;
                                  }
                default : break;
            }
        }
    }
    delete [] src;
    delete [] dest;
}