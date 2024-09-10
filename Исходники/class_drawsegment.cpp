const EDA_RECT DRAWSEGMENT::GetBoundingBox() const
{
    EDA_RECT bbox;

    bbox.SetOrigin( m_Start );

    switch( m_Shape )
    {
    case S_SEGMENT:
        bbox.SetEnd( m_End );
        break;

    case S_CIRCLE:
        bbox.Inflate( GetRadius() );
        break;

    case S_ARC:
        {
            bbox.Merge( m_End );
            wxPoint end = m_End;
            RotatePoint( &end, m_Start, -m_Angle );
            bbox.Merge( end );

            // Determine the starting quarter
            // 0 right-bottom
            // 1 left-bottom
            // 2 left-top
            // 3 right-top
            unsigned int quarter = 0;       // assume right-bottom

            if( m_End.y < m_Start.y )       // change to left-top
                quarter |= 3;

            if( m_End.x < m_Start.x )       // for left side, the LSB is 2nd bit negated
                quarter ^= 1;

            int radius = GetRadius();
            int angle = (int) GetArcAngleStart() % 900 + m_Angle;
            bool directionCW = ( m_Angle > 0 );      // Is the direction of arc clockwise?

            if( !directionCW )
            {
                angle = 900 - angle;
                quarter = ( quarter + 3 ) % 4;       // -1 modulo arithmetic
            }

            while( angle > 900 )
            {
                switch( quarter )
                {
                case 0:
                    bbox.Merge( wxPoint( m_Start.x, m_Start.y + radius ) );     // down
                    break;

                case 1:
                    bbox.Merge( wxPoint( m_Start.x - radius, m_Start.y ) );     // left
                    break;

                case 2:
                    bbox.Merge( wxPoint( m_Start.x, m_Start.y - radius ) );     // up
                    break;

                case 3:
                    bbox.Merge( wxPoint( m_Start.x + radius, m_Start.y ) );     // right
                    break;
                }

                if( directionCW )
                    ++quarter;
                else
                    quarter += 3;       // -1 modulo arithmetic

                quarter %= 4;
                angle -= 900;
            }
        }
        break;

    case S_POLYGON:
        {
            wxPoint p_end;
            MODULE* module = GetParentModule();

            for( unsigned ii = 0; ii < m_PolyPoints.size(); ii++ )
            {
                wxPoint pt = m_PolyPoints[ii];

                if( module ) // Transform, if we belong to a module
                {
                    RotatePoint( &pt, module->GetOrientation() );
                    pt += module->GetPosition();
                }

                if( ii == 0 )
                    p_end = pt;

                bbox.SetX( std::min( bbox.GetX(), pt.x ) );
                bbox.SetY( std::min( bbox.GetY(), pt.y ) );
                p_end.x   = std::max( p_end.x, pt.x );
                p_end.y   = std::max( p_end.y, pt.y );
            }

            bbox.SetEnd( p_end );
        }
        break;

    default:
        ;
    }

    bbox.Inflate( ((m_Width+1) / 2) + 1 );
    bbox.Normalize();

    return bbox;
}