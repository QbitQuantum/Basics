int SeparatePoints2<Real>::WhichSide (const Vector2<Real>& lineNormal,
    Real lineConstant, int numEdges, const int* edges,
    const Vector2<Real>* points)
{
    // Establish which side of line hull is on.
    Real c0;
    for (int i1 = 0, i0 = numEdges-1; i1 < numEdges; i0 = i1++)
    {
        c0 = lineNormal.Dot(points[edges[i0]]);
        if (c0 > lineConstant + Math<Real>::ZERO_TOLERANCE)
        {
            // Hull on positive side.
            return +1;
        }
        if (c0 < lineConstant - Math<Real>::ZERO_TOLERANCE)
        {
            // Hull on negative side.
            return -1;
        }

        c0 = lineNormal.Dot(points[edges[i1]]);
        if (c0 > lineConstant + Math<Real>::ZERO_TOLERANCE)
        {
            // Hull on positive side.
            return +1;
        }
        if (c0 < lineConstant - Math<Real>::ZERO_TOLERANCE)
        {
            // Hull on negative side.
            return -1;
        }
    }

    // Hull is effectively collinear.
    return 0;
}