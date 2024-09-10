Box3<Real> MergeBoxes (const Box3<Real>& box0, const Box3<Real>& box1)
{
    // Construct a box that contains the input boxes.
    Box3<Real> box;

    // The first guess at the box center.  This value will be updated later
    // after the input box vertices are projected onto axes determined by an
    // average of box axes.
    box.Center = ((Real)0.5)*(box0.Center + box1.Center);

    // A box's axes, when viewed as the columns of a matrix, form a rotation
    // matrix.  The input box axes are converted to quaternions.  The average
    // quaternion is computed, then normalized to unit length.  The result is
    // the slerp of the two input quaternions with t-value of 1/2.  The result
    // is converted back to a rotation matrix and its columns are selected as
    // the merged box axes.
    Quaternion<Real> q0, q1;
    q0.FromRotationMatrix(box0.Axis);
    q1.FromRotationMatrix(box1.Axis);
    if (q0.Dot(q1) < (Real)0)
    {
        q1 = -q1;
    }

    Quaternion<Real> q = q0 + q1;
    Real invLength = Math<Real>::InvSqrt(q.Dot(q));
    q = invLength*q;
    q.ToRotationMatrix(box.Axis);

    // Project the input box vertices onto the merged-box axes.  Each axis
    // D[i] containing the current center C has a minimum projected value
    // min[i] and a maximum projected value max[i].  The corresponding end
    // points on the axes are C+min[i]*D[i] and C+max[i]*D[i].  The point C
    // is not necessarily the midpoint for any of the intervals.  The actual
    // box center will be adjusted from C to a point C' that is the midpoint
    // of each interval,
    //   C' = C + sum_{i=0}^2 0.5*(min[i]+max[i])*D[i]
    // The box extents are
    //   e[i] = 0.5*(max[i]-min[i])

    int i, j;
    Real dot;
    Vector3<Real> vertex[8], diff;
    Vector3<Real> pmin = Vector3<Real>::ZERO;
    Vector3<Real> pmax = Vector3<Real>::ZERO;

    box0.ComputeVertices(vertex);
    for (i = 0; i < 8; ++i)
    {
        diff = vertex[i] - box.Center;
        for (j = 0; j < 3; ++j)
        {
            dot = diff.Dot(box.Axis[j]);
            if (dot > pmax[j])
            {
                pmax[j] = dot;
            }
            else if (dot < pmin[j])
            {
                pmin[j] = dot;
            }
        }
    }

    box1.ComputeVertices(vertex);
    for (i = 0; i < 8; ++i)
    {
        diff = vertex[i] - box.Center;
        for (j = 0; j < 3; ++j)
        {
            dot = diff.Dot(box.Axis[j]);
            if (dot > pmax[j])
            {
                pmax[j] = dot;
            }
            else if (dot < pmin[j])
            {
                pmin[j] = dot;
            }
        }
    }

    // [min,max] is the axis-aligned box in the coordinate system of the
    // merged box axes.  Update the current box center to be the center of
    // the new box.  Compute the extents based on the new center.
    for (j = 0; j < 3; ++j)
    {
        box.Center += (((Real)0.5)*(pmax[j] + pmin[j]))*box.Axis[j];
        box.Extent[j] = ((Real)0.5)*(pmax[j] - pmin[j]);
    }

    return box;
}