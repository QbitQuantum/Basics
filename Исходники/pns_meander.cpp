SHAPE_LINE_CHAIN PNS_MEANDER_SHAPE::genMeanderShape( VECTOR2D aP, VECTOR2D aDir,
        bool aSide, PNS_MEANDER_TYPE aType, int aAmpl, int aBaselineOffset )
{
    const PNS_MEANDER_SETTINGS& st = Settings();
    int cr = cornerRadius();
    int offset = aBaselineOffset;
    int spc = spacing();

    if( aSide )
        offset *= -1;

    VECTOR2D dir_u_b( aDir.Resize( offset ) );
    VECTOR2D dir_v_b( dir_u_b.Perpendicular() );

    if( 2 * cr > aAmpl )
    {
        cr = aAmpl / 2;
    }

    if( 2 * cr > spc )
    {
        cr = spc / 2;
    }

    SHAPE_LINE_CHAIN lc;

    start( &lc, aP + dir_v_b, aDir );

    switch( aType )
    {
        case MT_EMPTY:
        {
            lc.Append( aP + dir_v_b + aDir );
            break;
        }
        case MT_START:
        {
            arc( cr - offset, false );
            uShape( aAmpl - 2 * cr + std::abs( offset ), cr + offset, spc - 2 * cr );
            forward( std::min( cr - offset, cr + offset ) );
            forward( std::abs( offset ) );

            break;
        }

        case MT_FINISH:
        {
            start( &lc, aP - dir_u_b, aDir );
            turn ( 90 );
            forward( std::min( cr - offset, cr + offset ) );
            forward( std::abs( offset ) );
            uShape( aAmpl - 2 * cr + std::abs( offset ), cr + offset, spc - 2 * cr );
            arc( cr - offset, false );
            break;
        }

        case MT_TURN:
        {
            start( &lc, aP - dir_u_b, aDir );
            turn( 90 );
            forward( std::abs( offset ) );
            uShape ( aAmpl - cr, cr + offset, spc - 2 * cr );
            forward( std::abs( offset ) );
            break;
        }

        case MT_SINGLE:
        {
            arc( cr - offset, false );
            uShape( aAmpl - 2 * cr + std::abs( offset ), cr + offset, spc - 2 * cr );
            arc( cr - offset, false );
            lc.Append( aP + dir_v_b + aDir.Resize ( 2 * st.m_spacing ) );
            break;
        }

        default:
            break;
    }

    if( aSide )
    {
        SEG axis ( aP, aP + aDir );

        for( int i = 0; i < lc.PointCount(); i++ )
            lc.Point( i ) = reflect( lc.CPoint( i ), axis );
    }

    return lc;
}