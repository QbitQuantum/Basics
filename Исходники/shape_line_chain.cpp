int SHAPE_LINE_CHAIN::EdgeContainingPoint( const VECTOR2I& aPt, int aAccuracy ) const
{
    if( !PointCount() )
		return -1;

	else if( PointCount() == 1 )
    {
	    VECTOR2I dist = m_points[0] - aPt;
	    return ( hypot( dist.x, dist.y ) <= aAccuracy + 1 ) ? 0 : -1;
    }

    for( int i = 0; i < SegmentCount(); i++ )
    {
        const SEG s = CSegment( i );

        if( s.A == aPt || s.B == aPt )
            return i;

        if( s.Distance( aPt ) <= aAccuracy + 1 )
            return i;
    }

    return -1;
}