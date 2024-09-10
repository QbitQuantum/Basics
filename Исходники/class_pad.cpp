bool D_PAD::HitTest( const EDA_RECT& aRect, bool aContained, int aAccuracy ) const
{
    EDA_RECT arect = aRect;
    arect.Normalize();
    arect.Inflate( aAccuracy );

    wxPoint shapePos = ShapePos();

    EDA_RECT shapeRect;

    int r;

    EDA_RECT bb = GetBoundingBox();

    wxPoint endCenter;
    int radius;

    if( !arect.Intersects( bb ) )
        return false;

    // This covers total containment for all test cases
    if( arect.Contains( bb ) )
        return true;

    switch( GetShape() )
    {
    case PAD_SHAPE_CIRCLE:
        return arect.IntersectsCircle( GetPosition(), GetBoundingRadius() );
    case PAD_SHAPE_RECT:
        shapeRect.SetOrigin( shapePos );
        shapeRect.Inflate( m_Size.x / 2, m_Size.y / 2 );
        return arect.Intersects( shapeRect, m_Orient );
    case PAD_SHAPE_OVAL:

        // Circlular test if dimensions are equal
        if( m_Size.x == m_Size.y )
            return arect.IntersectsCircle( shapePos, GetBoundingRadius() );

        shapeRect.SetOrigin( shapePos );

        // Horizontal dimension is greater
        if( m_Size.x > m_Size.y )
        {
            radius = m_Size.y / 2;

            shapeRect.Inflate( m_Size.x / 2 - radius, radius );

            endCenter = wxPoint( m_Size.x / 2 - radius, 0 );
            RotatePoint( &endCenter, m_Orient );

            // Test circular ends
            if( arect.IntersectsCircle( shapePos + endCenter, radius ) ||
                arect.IntersectsCircle( shapePos - endCenter, radius ) )
            {
                return true;
            }
        }
        else
        {
            radius = m_Size.x / 2;

            shapeRect.Inflate( radius, m_Size.y / 2 - radius );

            endCenter = wxPoint( 0, m_Size.y / 2 - radius );
            RotatePoint( &endCenter, m_Orient );

            // Test circular ends
            if( arect.IntersectsCircle( shapePos + endCenter, radius ) ||
                arect.IntersectsCircle( shapePos - endCenter, radius ) )
            {
                return true;
            }
        }

        // Test rectangular portion between rounded ends
        if( arect.Intersects( shapeRect, m_Orient ) )
        {
            return true;
        }

        break;
    case PAD_SHAPE_TRAPEZOID:
        /* Trapezoid intersection tests:
         * A) Any points of rect inside trapezoid
         * B) Any points of trapezoid inside rect
         * C) Any sides of trapezoid cross rect
         */
        {

        wxPoint poly[4];
        BuildPadPolygon( poly, wxSize( 0, 0 ), 0 );

        wxPoint corners[4];

        corners[0] = wxPoint( arect.GetLeft(),  arect.GetTop() );
        corners[1] = wxPoint( arect.GetRight(), arect.GetTop() );
        corners[2] = wxPoint( arect.GetRight(), arect.GetBottom() );
        corners[3] = wxPoint( arect.GetLeft(),  arect.GetBottom() );

        for( int i=0; i<4; i++ )
        {
            RotatePoint( &poly[i], m_Orient );
            poly[i] += shapePos;
        }

        for( int ii=0; ii<4; ii++ )
        {
            if( TestPointInsidePolygon( poly, 4, corners[ii] ) )
            {
                return true;
            }

            if( arect.Contains( poly[ii] ) )
            {
                return true;
            }

            if( arect.Intersects( poly[ii], poly[(ii+1) % 4] ) )
            {
                return true;
            }
        }

        return false;

        }
    case PAD_SHAPE_ROUNDRECT:
        /* RoundRect intersection can be broken up into simple tests:
         * a) Test intersection of horizontal rect
         * b) Test intersection of vertical rect
         * c) Test intersection of each corner
         */


        r = GetRoundRectCornerRadius();

        /* Test A - intersection of horizontal rect */
        shapeRect.SetSize( 0, 0 );
        shapeRect.SetOrigin( shapePos );
        shapeRect.Inflate( m_Size.x / 2, m_Size.y / 2 - r );

        // Short-circuit test for zero width or height
        if( shapeRect.GetWidth() > 0 && shapeRect.GetHeight() > 0 &&
            arect.Intersects( shapeRect, m_Orient ) )
        {
            return true;
        }

        /* Test B - intersection of vertical rect */
        shapeRect.SetSize( 0, 0 );
        shapeRect.SetOrigin( shapePos );
        shapeRect.Inflate( m_Size.x / 2 - r, m_Size.y / 2 );

        // Short-circuit test for zero width or height
        if( shapeRect.GetWidth() > 0 && shapeRect.GetHeight() > 0 &&
            arect.Intersects( shapeRect, m_Orient ) )
        {
            return true;
        }

        /* Test C - intersection of each corner */

        endCenter = wxPoint( m_Size.x / 2 - r, m_Size.y / 2 - r );
        RotatePoint( &endCenter, m_Orient );

        if( arect.IntersectsCircle( shapePos + endCenter, r ) ||
            arect.IntersectsCircle( shapePos - endCenter, r ) )
        {
            return true;
        }

        endCenter = wxPoint( m_Size.x / 2 - r, -m_Size.y / 2 + r );
        RotatePoint( &endCenter, m_Orient );

        if( arect.IntersectsCircle( shapePos + endCenter, r ) ||
            arect.IntersectsCircle( shapePos - endCenter, r ) )
        {
            return true;
        }

        break;
    default:
        break;
    }

    return false;
}