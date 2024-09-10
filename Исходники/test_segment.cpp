/**
 * Predicate to check expected distance between a segment and a point
 * @param  aSegA the segment
 * @param  aVec  the vector (point)
 * @param  aExp  expected distance
 * @return       does the distance calculated agree?
 */
bool SegVecDistanceCorrect( const SEG& aSeg, const VECTOR2I& aVec, int aExp )
{
    const int dist = aSeg.Distance( aVec );

    bool ok = ( dist == aExp );

    if( !ok )
    {
        std::stringstream ss;
        ss << "Distance incorrect: expected " << aExp << ", got " << dist;
        BOOST_TEST_INFO( ss.str() );
    }

    return ok;
}