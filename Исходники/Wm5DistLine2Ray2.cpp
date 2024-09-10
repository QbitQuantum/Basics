Real DistLine2Ray2<Real>::GetSquared ()
{
    Vector2<Real> diff = mLine->Origin - mRay->Origin;
    Real a01 = -mLine->Direction.Dot(mRay->Direction);
    Real b0 = diff.Dot(mLine->Direction);
    Real c = diff.SquaredLength();
    Real det = Math<Real>::FAbs((Real)1 - a01*a01);
    Real b1, s0, s1, sqrDist;

    if (det >= Math<Real>::ZERO_TOLERANCE)
    {
        b1 = -diff.Dot(mRay->Direction);
        s1 = a01*b0 - b1;

        if (s1 >= (Real)0)
        {
            // Two interior points are closest, one on line and one on ray.
            Real invDet = ((Real)1)/det;
            s0 = (a01*b1 - b0)*invDet;
            s1 *= invDet;
            sqrDist = (Real)0;
        }
        else
        {
            // Origin of ray and interior point of line are closest.
            s0 = -b0;
            s1 = (Real)0;
            sqrDist = b0*s0 + c;

            // Account for numerical round-off errors.
            if (sqrDist < (Real)0)
            {
                sqrDist = (Real)0;
            }
        }
    }
    else
    {
        // Lines are parallel, closest pair with one point at ray origin.
        s0 = -b0;
        s1 = (Real)0;
        sqrDist = b0*s0 + c;

        // Account for numerical round-off errors.
        if (sqrDist < (Real)0)
        {
            sqrDist = (Real)0;
        }
    }

    mClosestPoint0 = mLine->Origin + s0*mLine->Direction;
    mClosestPoint1 = mRay->Origin + s1*mRay->Direction;
    return sqrDist;
}