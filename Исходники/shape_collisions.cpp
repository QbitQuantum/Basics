static VECTOR2I pushoutForce( const SHAPE_CIRCLE& aA, const SEG& aB, int aClearance )
{
    VECTOR2I f( 0, 0 );

    const VECTOR2I c = aA.GetCenter();
    const VECTOR2I nearest = aB.NearestPoint( c );

    const int r = aA.GetRadius();

    int dist = ( nearest - c ).EuclideanNorm();
    int min_dist = aClearance + r;

    if( dist < min_dist )
    {
        for( int corr = 0; corr < 5; corr++ )
        {
            f = ( aA.GetCenter() - nearest ).Resize( min_dist - dist + corr );

            if( aB.Distance( c + f ) >= min_dist )
                break;
        }
    }

    return f;
}