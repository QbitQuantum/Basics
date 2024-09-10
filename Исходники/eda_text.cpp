EDA_RECT EDA_TEXT::GetTextBox( int aLine, int aThickness, bool aInvertY ) const
{
    EDA_RECT       rect;
    wxPoint        pos;
    wxArrayString  strings;
    wxString       text = GetShownText();
    int            thickness = ( aThickness < 0 ) ? m_Thickness : aThickness;
    int            linecount = 1;

    if( m_MultilineAllowed )
    {
        wxStringSplit( text, strings, '\n' );

        if ( strings.GetCount() )     // GetCount() == 0 for void strings
        {
            if( aLine >= 0 && (aLine < (int)strings.GetCount()) )
                text = strings.Item( aLine );
            else
                text = strings.Item( 0 );

            linecount = strings.GetCount();
        }
    }

    // calculate the H and V size
    int    dx = LenSize( text );
    int    dy = GetInterline( aThickness );

    // Creates bounding box (rectangle) for an horizontal text
    wxSize textsize = wxSize( dx, dy );

    if( aInvertY )
        rect.SetOrigin( m_Pos.x, -m_Pos.y );
    else
        rect.SetOrigin( m_Pos );

    // extra dy interval for letters like j and y and ]
    int extra_dy = dy - m_Size.y;
    rect.Move( wxPoint( 0, -extra_dy / 2 ) ); // move origin by the half extra interval

    // for multiline texts and aLine < 0, merge all rectangles
    if( m_MultilineAllowed && aLine < 0 )
    {
        for( unsigned ii = 1; ii < strings.GetCount(); ii++ )
        {
            text = strings.Item( ii );
            dx   = LenSize( text );
            textsize.x  = std::max( textsize.x, dx );
            textsize.y += dy;
        }
    }

    rect.SetSize( textsize );

    /* Now, calculate the rect origin, according to text justification
     * At this point the rectangle origin is the text origin (m_Pos).
     * This is true only for left and top text justified texts (using top to bottom Y axis
     * orientation). and must be recalculated for others justifications
     * also, note the V justification is relative to the first line
     */
    switch( m_HJustify )
    {
    case GR_TEXT_HJUSTIFY_LEFT:
        if( m_Mirror )
            rect.SetX( rect.GetX() - rect.GetWidth() );
        break;

    case GR_TEXT_HJUSTIFY_CENTER:
        rect.SetX( rect.GetX() - (rect.GetWidth() / 2) );
        break;

    case GR_TEXT_HJUSTIFY_RIGHT:
        if( !m_Mirror )
            rect.SetX( rect.GetX() - rect.GetWidth() );
        break;
    }

    dy = m_Size.y + thickness;

    switch( m_VJustify )
    {
    case GR_TEXT_VJUSTIFY_TOP:
        break;

    case GR_TEXT_VJUSTIFY_CENTER:
        rect.SetY( rect.GetY() - ( dy / 2) );
        break;

    case GR_TEXT_VJUSTIFY_BOTTOM:
        rect.SetY( rect.GetY() - dy );
        break;
    }

    if( linecount > 1 )
    {
        int yoffset;
        linecount -= 1;

        switch( m_VJustify )
        {
        case GR_TEXT_VJUSTIFY_TOP:
            break;

        case GR_TEXT_VJUSTIFY_CENTER:
            yoffset = linecount * GetInterline() / 2;
            rect.SetY( rect.GetY() - yoffset );
            break;

        case GR_TEXT_VJUSTIFY_BOTTOM:
            yoffset = linecount * GetInterline( aThickness );
            rect.SetY( rect.GetY() - yoffset );
            break;
        }
    }

    rect.Inflate( thickness / 2 );
    rect.Normalize();       // Make h and v sizes always >= 0

    return rect;
}