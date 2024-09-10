bool IntrLine2Circle2<Real>::Find (const Vector2<Real>& rkOrigin,
    const Vector2<Real>& rkDirection, const Vector2<Real>& rkCenter,
    Real fRadius, int& riRootCount, Real afT[2])
{
    // Intersection of a the line P+t*D and the circle |X-C| = R.  The line
    // direction is unit length. The t value is a root to the quadratic
    // equation:
    //   0 = |t*D+P-C|^2 - R^2
    //     = t^2 + 2*Dot(D,P-C)*t + |P-C|^2-R^2
    //     = t^2 + 2*a1*t + a0
    // If two roots are returned, the order is T[0] < T[1].

    Vector2<Real> kDiff = rkOrigin - rkCenter;
    Real fA0 = kDiff.SquaredLength() - fRadius*fRadius;
    Real fA1 = rkDirection.Dot(kDiff);
    Real fDiscr = fA1*fA1 - fA0;
    if (fDiscr > Math<Real>::ZERO_TOLERANCE)
    {
        riRootCount = 2;
        fDiscr = Math<Real>::Sqrt(fDiscr);
        afT[0] = -fA1 - fDiscr;
        afT[1] = -fA1 + fDiscr;
    }
    else if (fDiscr < -Math<Real>::ZERO_TOLERANCE)
    {
        riRootCount = 0;
    }
    else  // fDiscr == 0
    {
        riRootCount = 1;
        afT[0] = -fA1;
    }

    return riRootCount != 0;
}