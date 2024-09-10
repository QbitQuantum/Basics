bool IntrSegment3Triangle3<Real>::Test ()
{
    // Compute the offset origin, edges, and normal.
    Vector3<Real> diff = mSegment->Center - mTriangle->V[0];
    Vector3<Real> edge1 = mTriangle->V[1] - mTriangle->V[0];
    Vector3<Real> edge2 = mTriangle->V[2] - mTriangle->V[0];
    Vector3<Real> normal = edge1.Cross(edge2);

    // Solve Q + t*D = b1*E1 + b2*E2 (Q = diff, D = segment direction,
    // E1 = edge1, E2 = edge2, N = Cross(E1,E2)) by
    //   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
    //   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
    //   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
    Real DdN = mSegment->Direction.Dot(normal);
    Real sign;
    if (DdN > Math<Real>::ZERO_TOLERANCE)
    {
        sign = (Real)1;
    }
    else if (DdN < -Math<Real>::ZERO_TOLERANCE)
    {
        sign = (Real)-1;
        DdN = -DdN;
    }
    else
    {
        // Segment and triangle are parallel, call it a "no intersection"
        // even if the segment does intersect.
        mIntersectionType = IT_EMPTY;
        return false;
    }

    Real DdQxE2 = sign*mSegment->Direction.Dot(diff.Cross(edge2));
    if (DdQxE2 >= (Real)0)
    {
        Real DdE1xQ = sign*mSegment->Direction.Dot(edge1.Cross(diff));
        if (DdE1xQ >= (Real)0)
        {
            if (DdQxE2 + DdE1xQ <= DdN)
            {
                // Line intersects triangle, check if segment does.
                Real QdN = -sign*diff.Dot(normal);
                Real extDdN = mSegment->Extent*DdN;
                if (-extDdN <= QdN && QdN <= extDdN)
                {
                    // Segment intersects triangle.
                    mIntersectionType = IT_POINT;
                    return true;
                }
                // else: |t| > extent, no intersection
            }
            // else: b1+b2 > 1, no intersection
        }
        // else: b2 < 0, no intersection
    }
    // else: b1 < 0, no intersection

    mIntersectionType = IT_EMPTY;
    return false;
}