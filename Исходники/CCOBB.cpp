void OBB::transform(const Mat4& mat)
{
    Vec4 newcenter = mat * Vec4(_center.x, _center.y, _center.z, 1.0f);// center;
    _center.x = newcenter.x;
    _center.y = newcenter.y;
    _center.z = newcenter.z;

    _xAxis = mat * _xAxis;
    _yAxis = mat * _yAxis;
    _zAxis = mat * _zAxis;

    _xAxis.normalize();
    _yAxis.normalize();
    _zAxis.normalize();

    Vec3 scale, trans;
    Quaternion quat;
    mat.decompose(&scale, &quat, &trans);

    _extents.x *= scale.x;
    _extents.y *= scale.y;
    _extents.z *= scale.z;
    
    computeExtAxis();
}