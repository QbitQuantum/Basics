int IntrSegment2Segment2<Real>::Classify (Real* s, Vector2<Real>* diff,
    Vector2<Real>* diffN)
{
    // The intersection of two lines is a solution to P0+s0*D0 = P1+s1*D1.
    // Rewrite this as s0*D0 - s1*D1 = P1 - P0 = Q.  If D0.Dot(Perp(D1)) = 0,
    // the lines are parallel.  Additionally, if Q.Dot(Perp(D1)) = 0, the
    // lines are the same.  If D0.Dot(Perp(D1)) is not zero, then
    //   s0 = Q.Dot(Perp(D1))/D0.Dot(Perp(D1))
    // produces the point of intersection.  Also,
    //   s1 = Q.Dot(Perp(D0))/D0.Dot(Perp(D1))

    Vector2<Real> originDiff = mSegment1->Center - mSegment0->Center;
    if (diff)
    {
        *diff = originDiff;
    }

    Real D0DotPerpD1 = mSegment0->Direction.DotPerp(mSegment1->Direction);
    if (Math<Real>::FAbs(D0DotPerpD1) > Math<Real>::ZERO_TOLERANCE)
    {
        // Lines intersect in a single point.
        if (s)
        {
            Real invD0DotPerpD1 = ((Real)1)/D0DotPerpD1;
            Real diffDotPerpD0 = originDiff.DotPerp(mSegment0->Direction);
            Real diffDotPerpD1 = originDiff.DotPerp(mSegment1->Direction);
            s[0] = diffDotPerpD1*invD0DotPerpD1;
            s[1] = diffDotPerpD0*invD0DotPerpD1;
        }
        return IT_POINT;
    }

    // Lines are parallel.
    originDiff.Normalize();
    if (diffN)
    {
        *diffN = originDiff;
    }

    Real diffNDotPerpD1 = originDiff.DotPerp(mSegment1->Direction);
    if (Math<Real>::FAbs(diffNDotPerpD1) <= Math<Real>::ZERO_TOLERANCE)
    {
        // Lines are colinear.
        return IT_SEGMENT;
    }

    // Lines are parallel, but distinct.
    return IT_EMPTY;
}