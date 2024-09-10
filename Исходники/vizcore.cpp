cv::Affine3d cv::viz::makeCameraPose(const Vec3d& position, const Vec3d& focal_point, const Vec3d& y_dir)
{
    // Compute the transformation matrix for drawing the camera frame in a scene
    Vec3d n = normalize(focal_point - position);
    Vec3d u = normalize(y_dir.cross(n));
    Vec3d v = n.cross(u);

    return makeTransformToGlobal(u, v, n, position);
}