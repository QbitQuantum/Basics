Box3<Real> Wml::MergeBoxes (const Box3<Real>& rkBox0,
    const Box3<Real>& rkBox1)
{
    // construct a box that contains the input boxes
    Box3<Real> kBox;

    // The first guess at the box center.  This value will be updated later
    // after the input box vertices are projected onto axes determined by an
    // average of box axes.
    kBox.Center() = ((Real)0.5)*(rkBox0.Center() + rkBox1.Center());

    // A box's axes, when viewed as the columns of a matrix, form a rotation
    // matrix.  The input box axes are converted to quaternions.  The average
    // quaternion is computed, then normalized to unit length.  The result is
    // the slerp of the two input quaternions with t-value of 1/2.  The result
    // is converted back to a rotation matrix and its columns are selected as
    // the merged box axes.
    Quaternion<Real> kQ0, kQ1;
    kQ0.FromRotationMatrix(rkBox0.Axes());
    kQ1.FromRotationMatrix(rkBox1.Axes());
    if ( kQ0.Dot(kQ1) < 0.0f )
        kQ1 = -kQ1;

    Quaternion<Real> kQ = kQ0 + kQ1;
    Real fInvLength = Math<Real>::InvSqrt(kQ.Dot(kQ));
    kQ = fInvLength*kQ;
    kQ.ToRotationMatrix(kBox.Axes());

    // Project the input box vertices onto the merged-box axes.  Each axis
    // D[i] containing the current center C has a minimum projected value
    // pmin[i] and a maximum projected value pmax[i].  The corresponding end
    // points on the axes are C+pmin[i]*D[i] and C+pmax[i]*D[i].  The point C
    // is not necessarily the midpoint for any of the intervals.  The actual
    // box center will be adjusted from C to a point C' that is the midpoint
    // of each interval,
    //   C' = C + sum_{i=0}^2 0.5*(pmin[i]+pmax[i])*D[i]
    // The box extents are
    //   e[i] = 0.5*(pmax[i]-pmin[i])

    int i, j;
    Real fDot;
    Vector3<Real> akVertex[8], kDiff;
    Vector3<Real> kMin = Vector3<Real>::ZERO;
    Vector3<Real> kMax = Vector3<Real>::ZERO;

    rkBox0.ComputeVertices(akVertex);
    for (i = 0; i < 8; i++)
    {
        kDiff = akVertex[i] - kBox.Center();
        for (j = 0; j < 3; j++)
        {
            fDot = kDiff.Dot(kBox.Axis(j));
            if ( fDot > kMax[j] )
                kMax[j] = fDot;
            else if ( fDot < kMin[j] )
                kMin[j] = fDot;
        }
    }

    rkBox1.ComputeVertices(akVertex);
    for (i = 0; i < 8; i++)
    {
        kDiff = akVertex[i] - kBox.Center();
        for (j = 0; j < 3; j++)
        {
            fDot = kDiff.Dot(kBox.Axis(j));
            if ( fDot > kMax[j] )
                kMax[j] = fDot;
            else if ( fDot < kMin[j] )
                kMin[j] = fDot;
        }
    }

    // [kMin,kMax] is the axis-aligned box in the coordinate system of the
    // merged box axes.  Update the current box center to be the center of
    // the new box.  Compute the extens based on the new center.
    for (j = 0; j < 3; j++)
    {
        kBox.Center() += (((Real)0.5)*(kMax[j]+kMin[j]))*kBox.Axis(j);
        kBox.Extent(j) = ((Real)0.5)*(kMax[j]-kMin[j]);
    }

    return kBox;
}