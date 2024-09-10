bool IntrLine2Circle2<Real>::Find (const Vector2<Real>& origin,
    const Vector2<Real>& direction, const Vector2<Real>& center,
    Real radius, int& rootCount, Real t[2])
{
    // Intersection of a the line P+t*D and the circle |X-C| = R.  The line
    // direction is unit length. The t value is a root to the quadratic
    // equation:
    //   0 = |t*D+P-C|^2 - R^2
    //     = t^2 + 2*Dot(D,P-C)*t + |P-C|^2-R^2
    //     = t^2 + 2*a1*t + a0
    // If two roots are returned, the order is T[0] < T[1].

    Vector2<Real> diff = origin - center;
    Real a0 = diff.SquaredLength() - radius*radius;
    Real a1 = direction.Dot(diff);
    Real discr = a1*a1 - a0;
    if (discr > Math<Real>::ZERO_TOLERANCE)
    {
        rootCount = 2;
        discr = Math<Real>::Sqrt(discr);
        t[0] = -a1 - discr;
        t[1] = -a1 + discr;
    }
    else if (discr < -Math<Real>::ZERO_TOLERANCE)
    {
        rootCount = 0;
    }
    else  // discr == 0
    {
        rootCount = 1;
        t[0] = -a1;
    }

    return rootCount != 0;
}