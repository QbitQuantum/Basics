//----------------------------------------------------------------------------
// Compute the intersection of the segment C+t*V, [0,tMax], with a finite
// cylinder.  The cylinder has center P, radius r, height h, and axis
// direction U2.  The set {U0,U1,U2} is orthonormal and right-handed.  In the
// coordinate system of the cylinder, a point A = P + x*U0 + y*U1 + z*U2.  To
// be inside the cylinder, x*x + y*y <= r*r and |z| <= h/2.  The function
// returns 'true' iff [t0,t1] is a nonempty interval.
//----------------------------------------------------------------------------
static bool IntersectLineCylinder (const SphereStruct& sph,
    const Vector3f& V, const Vector3f& P, const Vector3f& U0,
    const Vector3f& U1, const Vector3f& U2, float halfHeight,
    const float tMax, float& t0, float& t1)
{
    t0 = 0.0f;
    t1 = tMax;

    // Clip against the plane caps.
    if (!ClipAgainstPlane(sph.C, V, U2, P + halfHeight*U2, t0, t1)
    ||  !ClipAgainstPlane(sph.C, V, -U2, P - halfHeight*U2, t0, t1))
    {
        return false;
    }

    // In cylinder coordinates, C+t*V = P + x(t)*U0 + y(t)*U1 + z(t)*U2,
    // x(t) = Dot(U0,C+t*V-P) = a0 + t*b0, y(t) = Dot(U1,C+t*V-P) = a1 + t*b1
    Vector3f CmP = sph.C - P;
    float a0 = U0.Dot(CmP), b0 = U0.Dot(V);
    float a1 = U1.Dot(CmP), b1 = U1.Dot(V);

    // Clip the segment [t0,t1] against the cylinder wall.
    float x0 = a0 + t0*b0, y0 = a1 + t0*b1, r0Sqr = x0*x0 + y0*y0;
    float x1 = a0 + t1*b0, y1 = a1 + t1*b1, r1Sqr = x1*x1 + y1*y1;
    float rSqr = sph.RSqr;

    // Some case require computing intersections of the segment with the
    // circle of radius r.  This amounts to finding roots for the quadratic
    // Q(t) = x(t)*x(t) + y(t)*y(t) - r*r = q2*t^2 + 2*q1*t + q0, where
    // q0 = a0*a0+b0*b0-r*r, q1 = a0*a1+b0*b1, and q2 = a1*a1+b1*b1.  Compute
    // the coefficients only when needed.
    float q0, q1, q2, T;

    if (r0Sqr > rSqr)
    {
        if (r1Sqr > rSqr)
        {
            q2 = b0*b0 + b1*b1;
            if (q2 > 0.0f)
            {
                q0 = a0*a0 + a1*a1 - rSqr;
                q1 = a0*b0 + a1*b1;
                float discr = q1*q1 - q0*q2;
                if (discr < 0.0f)
                {
                    // The quadratic has no real-valued roots, so the
                    // segment is outside the cylinder.
                    return false;
                }

                float rootDiscr = sqrtf(discr);
                float invQ2 = 1.0f/q2;
                float root0 = (-q1 - rootDiscr)*invQ2;
                float root1 = (-q1 + rootDiscr)*invQ2;

                // We know that (x0,y0) and (x1,y1) are outside the
                // cylinder, so Q(t0) > 0 and Q(t1) > 0.  This reduces
                // the number of cases to analyze for intersection of
                // [t0,t1] and [root0,root1].
                if (t1 < root0 || t0 > root1)
                {
                    // The segment is strictly outside the cylinder.
                    return false;
                }
                else
                {
                    // [t0,t1] strictly contains [root0,root1]
                    t0 = root0;
                    t1 = root1;
                }
            }
            else  // q2 == 0.0f and q1 = 0.0f; that is, Q(t) = q0
            {
                // The segment is degenerate, a point that is outside the
                // cylinder.
                return false;
            }
        }
        else if (r1Sqr < rSqr)
        {
            // Solve nondegenerate quadratic and clip.  There must be a single
            // root T in [t0,t1].  Discard [t0,T].
            q0 = a0*a0 + a1*a1 - rSqr;
            q1 = a0*b0 + a1*b1;
            q2 = b0*b0 + b1*b1;
            t0 = (-q1 - sqrtf(fabsf(q1*q1 - q0*q2)))/q2;
        }
        else // r1Sqr == rSqr
        {
            // The segment intersects the circle at t1.  The other root is
            // necessarily T = -t1-2*q1/q2.  Use it only when T <= t1, in
            // which case discard [t0,T].
            q1 = a0*b0 +a1*b1;
            q2 = b0*b0 + b1*b1;
            T = -t1 - 2.0f*q1/q2;
            t0 = (T < t1 ? T : t1);
        }
    }
    else if (r0Sqr < rSqr)
    {
        if (r1Sqr > rSqr)
        {
            // Solve nondegenerate quadratic and clip.  There must be a single
            // root T in [t0,t1].  Discard [T,t1].
            q0 = a0*a0 + a1*a1 - rSqr;
            q1 = a0*b0 + a1*b1;
            q2 = b0*b0 + b1*b1;
            t1 = (-q1 + sqrtf(fabsf(q1*q1 - q0*q2)))/q2;
        }
        // else:  The segment is inside the cylinder.
    }
    else // r0Sqr == rSqr
    {
        if (r1Sqr > rSqr)
        {
            // The segment intersects the circle at t0.  The other root is
            // necessarily T = -t0-2*q1/q2.  Use it only when T >= t0, in
            // which case discard [T,t1].
            q1 = a0*b0 + a1*b1;
            q2 = b0*b0 + b1*b1;
            T = -t0 - 2.0f*q1/q2;
            t1 = (T > t0 ? T : t0);
        }
        // else:  The segment is inside the cylinder.
    }

    return true;
}