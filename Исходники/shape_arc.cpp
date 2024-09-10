bool SHAPE_ARC::Collide( const SEG& aSeg, int aClearance ) const
{
    int minDist = aClearance + m_width / 2;
    auto centerDist = aSeg.Distance( m_pc );
    auto p1 = GetP1();

    if( centerDist < minDist )
        return true;

    auto ab = (aSeg.B - aSeg.A );
    auto ac = ( m_pc - aSeg.A );

    auto lenAbSq = ab.SquaredEuclideanNorm();

    auto lambda = (double) ac.Dot( ab ) / (double) lenAbSq;


    if( lambda >= 0.0 && lambda <= 1.0 )
    {
        VECTOR2I p;

        p.x = (double) aSeg.A.x * lambda + (double) aSeg.B.x * (1.0 - lambda);
        p.y = (double) aSeg.A.y * lambda + (double) aSeg.B.y * (1.0 - lambda);

        auto p0pdist = ( m_p0 - p ).EuclideanNorm();

        if( p0pdist < minDist )
            return true;

        auto p1pdist = ( p1 - p ).EuclideanNorm();

        if( p1pdist < minDist )
            return true;
    }

    auto p0dist = aSeg.Distance( m_p0 );

    if( p0dist > minDist )
        return true;

    auto p1dist = aSeg.Distance( p1 );

    if( p1dist > minDist )
        return false;


    return true;
}