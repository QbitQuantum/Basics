AABB3d TransformSequence::compute_motion_segment_bbox(
    const AABB3d&       bbox,
    const Transformd&   from,
    const Transformd&   to) const
{
    //
    // Reference:
    //
    //   http://gruenschloss.org/motion-blur/motion-blur.pdf page 11.
    //

    // Parameters.
    const double MinLength = Pi / 2.0;
    const double RootEps = 1.0e-6;
    const double GrowEps = 1.0e-4;
    const size_t MaxIterations = 100;

    // Start with the bounding box at 'from'.
    const AABB3d from_bbox = from.to_parent(bbox);
    AABB3d motion_bbox = from_bbox;

    // Setup an interpolator between 'from' and 'to'.
    TransformInterpolatord interpolator;
    if (!interpolator.set_transforms(from, to))
        return motion_bbox;

    // Compute the scalings at 'from' and 'to'.
    const Vector3d s0 = interpolator.get_s0();
    const Vector3d s1 = interpolator.get_s1();

    // Compute the relative rotation between 'from' and 'to'.
    const Quaterniond q =
        interpolator.get_q1() * conjugate(interpolator.get_q0());

    // Transform the relative rotation to the axis-angle representation.
    Vector3d axis;
    double angle;
    q.extract_axis_angle(axis, angle);
    if (axis.z < 0.0)
        angle = -angle;

    // The following code only makes sense if there is a rotation component.
    if (angle == 0.0)
        return motion_bbox;

    // Compute the rotation required to align the rotation axis with the Z axis.
    const Vector3d Z(0.0, 0.0, 1.0);
    const Vector3d perp = cross(Z, axis);
    const double perp_norm = norm(perp);
    Transformd axis_to_z;
    if (perp_norm == 0.0)
        axis_to_z = Transformd::identity();
    else
    {
        const Vector3d v = perp / perp_norm;
        const double sin_a = clamp(perp_norm, -1.0, 1.0);
        const double cos_a = sqrt(1.0 - sin_a * sin_a);
        axis_to_z.set_local_to_parent(Matrix4d::make_rotation(v, cos_a, +sin_a));
        axis_to_z.set_parent_to_local(Matrix4d::make_rotation(v, cos_a, -sin_a));
    }

    // Build the linear scaling functions Sx(theta), Sy(theta) and Sz(theta).
    const LinearFunction sx(1.0, s1.x / s0.x, angle);
    const LinearFunction sy(1.0, s1.y / s0.y, angle);
    const LinearFunction sz(1.0, s1.z / s0.z, angle);

    // Consider each corner of the bounding box. Notice an important trick here:
    // we take advantage of the way AABB::compute_corner() works to only iterate
    // over the four corners at Z=min instead of over all eight corners since we
    // anyway transform the rotation to be aligned with the Z axis.
    for (size_t c = 0; c < 4; ++c)
    {
        // Compute the position of this corner at 'from'.
        const Vector3d corner = axis_to_z.point_to_local(from_bbox.compute_corner(c));
        const Vector2d corner2d(corner.x, corner.y);

        // Build the trajectory functions x(theta) and y(theta).
        const TrajectoryX tx(sx, sy, corner2d);
        const TrajectoryY ty(sx, sy, corner2d);

        // Find all the rotation angles at which this corner is an extremum and update the motion bounding box.
        RootHandler root_handler(tx, ty, sz, axis_to_z, corner, motion_bbox);
        find_multiple_roots_newton(
            Bind<TrajectoryX>(tx, &TrajectoryX::d),
            Bind<TrajectoryX>(tx, &TrajectoryX::dd),
            0.0, angle,
            MinLength,
            RootEps,
            MaxIterations,
            root_handler);
        find_multiple_roots_newton(
            Bind<TrajectoryY>(ty, &TrajectoryY::d),
            Bind<TrajectoryY>(ty, &TrajectoryY::dd),
            0.0, angle,
            MinLength,
            RootEps,
            MaxIterations,
            root_handler);
    }

    motion_bbox.robust_grow(GrowEps);

    return motion_bbox;
}