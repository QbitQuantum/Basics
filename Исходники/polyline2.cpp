float PolyLine2::GetPointParam( const Vec2& pt, bool bClosed ) const
{
    int minEdge = -1;
    float minDist = FLT_MAX;
    float minLen  = 0.0f;
    int nPt = m_Points.size();
    if (!bClosed)
    {
        nPt--;
    }
    float len = 0.0f;
    for (int i = 0; i < nPt; i++)
    {
        const Vec2& a = GetPoint( i );
        const Vec2& b = GetPoint( i + 1 );
        float d = pt.dist_seg( a, b );
        if (d < minDist)
        {
            minDist = d;
            minEdge = i;
            minLen  = len;
        }
        len += (a - b).norm();
    }

    const Vec2& a = GetPoint( minEdge );
    const Vec2& b = GetPoint( minEdge + 1 );
    Vec2 dir = b - a;
    dir.normalize();
    float dlen = minLen + dir.dot( pt - a );
    return dlen/GetLength( bClosed );
}