bool LIB_RECTANGLE::HitTest( wxPoint aPosition, int aThreshold, const TRANSFORM& aTransform )
{
    if( aThreshold < 0 )
        aThreshold = GetPenSize() / 2;

    wxPoint actualStart = aTransform.TransformCoordinate( m_Pos );
    wxPoint actualEnd   = aTransform.TransformCoordinate( m_End );

    // locate lower segment
    wxPoint start, end;

    start = actualStart;
    end.x = actualEnd.x;
    end.y = actualStart.y;

    if( TestSegmentHit( aPosition, start, end, aThreshold ) )
        return true;

    // locate right segment
    start.x = actualEnd.x;
    end.y   = actualEnd.y;

    if( TestSegmentHit( aPosition, start, end, aThreshold ) )
        return true;

    // locate upper segment
    start.y = actualEnd.y;
    end.x   = actualStart.x;

    if( TestSegmentHit( aPosition, start, end, aThreshold ) )
        return true;

    // locate left segment
    start = actualStart;
    end.x = actualStart.x;
    end.y = actualEnd.y;

    if( TestSegmentHit( aPosition, start, end, aThreshold ) )
        return true;

    return false;
}