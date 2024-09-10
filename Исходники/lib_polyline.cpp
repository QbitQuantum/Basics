bool LIB_POLYLINE::HitTest( const wxPoint &aPosition, int aThreshold, const TRANSFORM& aTransform ) const
{
    wxPoint ref, start, end;

    if( aThreshold < 0 )
        aThreshold = GetPenSize() / 2;

    for( unsigned ii = 1; ii < GetCornerCount(); ii++ )
    {
        start = aTransform.TransformCoordinate( m_PolyPoints[ii - 1] );
        end   = aTransform.TransformCoordinate( m_PolyPoints[ii] );

        if( TestSegmentHit( aPosition, start, end, aThreshold ) )
            return true;
    }

    return false;
}