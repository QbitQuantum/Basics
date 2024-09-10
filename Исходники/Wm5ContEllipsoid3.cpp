const Ellipsoid3<Real> MergeEllipsoids (const Ellipsoid3<Real>& ellipsoid0,
    const Ellipsoid3<Real>& ellipsoid1)
{
    Ellipsoid3<Real> merge;

    // compute the average of the input centers
    merge.Center = ((Real)0.5)*(ellipsoid0.Center + ellipsoid1.Center);

    // bounding ellipsoid orientation is average of input orientations
    Quaternion<Real> q0(ellipsoid0.Axis), q1(ellipsoid1.Axis);
    if (q0.Dot(q1) < (Real)0)
    {
        q1 = -q1;
    }
    Quaternion<Real> q = q0 + q1;
    q = Math<Real>::InvSqrt(q.Dot(q))*q;
    q.ToRotationMatrix(merge.Axis);

    // Project the input ellipsoids onto the axes obtained by the average
    // of the orientations and that go through the center obtained by the
    // average of the centers.
    for (int i = 0; i < 3; ++i)
    {
        // Projection axis.
        Line3<Real> line(merge.Center, merge.Axis[i]);

        // Project ellipsoids onto the axis.
        Real min0, max0, min1, max1;
        ProjectEllipsoid(ellipsoid0, line, min0, max0);
        ProjectEllipsoid(ellipsoid1, line, min1, max1);

        // Determine the smallest interval containing the projected
        // intervals.
        Real maxIntr = (max0 >= max1 ? max0 : max1);
        Real minIntr = (min0 <= min1 ? min0 : min1);

        // Update the average center to be the center of the bounding box
        // defined by the projected intervals.
        merge.Center += line.Direction*(((Real)0.5)*(minIntr + maxIntr));

        // Compute the extents of the box based on the new center.
        merge.Extent[i] = ((Real)0.5)*(maxIntr - minIntr);
    }

    return merge;
}