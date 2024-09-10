//----------------------------------------------------------------------------
int BspTree2::Classify (const Vector2d& end0, const Vector2d& end1,
    const Vector2d& v0, const Vector2d& v1, Vector2d& intr) const
{
    // For numerical round-off error handling.
    const double epsilon0 = 0.00001;
    const double epsilon1 = 0.99999;

    Vector2d dir = end1 - end0;
    Vector2d nor = dir.Perp();
    Vector2d diff0 = v0 - end0;
    Vector2d diff1 = v1 - end0;

    double d0 = nor.Dot(diff0);
    double d1 = nor.Dot(diff1);

    if (d0*d1 < 0.0)
    {
        // Edge <V0,V1> transversely crosses line.  Compute point of
        // intersection I = V0 + t*(V1 - V0).
        double t = d0/(d0 - d1);
        if (t > epsilon0)
        {
            if (t < epsilon1)
            {
                intr = v0 + t*(v1 - v0);
                if (d1 > 0.0)
                {
                    return TRANSVERSE_POSITIVE;
                }
                else
                {
                    return TRANSVERSE_NEGATIVE;
                }
            }
            else
            {
                // T is effectively 1 (numerical round-off issue), so
                // set d1 = 0 and go on to other cases.
                d1 = 0.0;
            }
        }
        else
        {
            // T is effectively 0 (numerical round-off issue), so
            // set d0 = 0 and go on to other cases.
            d0 = 0.0;
        }
    }

    if (d0 > 0.0 || d1 > 0.0)
    {
        // edge on positive side of line
        return ALL_POSITIVE;
    }

    if (d0 < 0.0 || d1 < 0.0)
    {
        // edge on negative side of line
        return ALL_NEGATIVE;
    }

    return COINCIDENT;
}