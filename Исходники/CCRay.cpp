bool Ray::intersects(const OBB& obb) const
{
    AABB aabb;
    aabb._min = - obb._extents;
    aabb._max = obb._extents;

    Ray ray;
    ray._direction = _direction;
    ray._origin = _origin;

    Mat4 mat = Mat4::IDENTITY;
    mat.m[0] = obb._xAxis.x;
    mat.m[1] = obb._xAxis.y;
    mat.m[2] = obb._xAxis.z;

    mat.m[4] = obb._yAxis.x;
    mat.m[5] = obb._yAxis.y;
    mat.m[6] = obb._yAxis.z;

    mat.m[8] = obb._zAxis.x;
    mat.m[9] = obb._zAxis.y;
    mat.m[10] = obb._zAxis.z;

    mat.m[12] = obb._center.x;
    mat.m[13] = obb._center.y;
    mat.m[14] = obb._center.z;

    mat = mat.getInversed();

    ray.transform(mat);

    return ray.intersects(aabb);
}