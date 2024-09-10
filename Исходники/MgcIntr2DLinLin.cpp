//----------------------------------------------------------------------------
bool Mgc::FindIntersection (const Line2& rkLine, const Ray2& rkRay,
    int& riQuantity, Real afT[2])
{
    Vector2 kDiff;
    Real fD0SqrLen;
    bool bIntersects = Find(rkLine.Origin(),rkLine.Direction(),
        rkRay.Origin(),rkRay.Direction(),kDiff,fD0SqrLen,riQuantity,afT);

    if ( bIntersects )
    {
        if ( riQuantity == 1 )
        {
            if ( afT[1] < 0.0f )
            {
                // lines intersect, but ray does not intersect line
                riQuantity = 0;
            }
        }
        else
        {
            // ray is contained by line, adjust intersection interval
            if ( rkLine.Direction().Dot(rkRay.Direction()) > 0.0f )
            {
                afT[0] = (kDiff.Dot(rkLine.Direction()))/fD0SqrLen;
                afT[1] = Math::MAX_REAL;
            }
            else
            {
                afT[0] = -Math::MAX_REAL;
                afT[1] = (kDiff.Dot(rkLine.Direction()))/fD0SqrLen;
            }
        }
    }

    return riQuantity != 0;
}