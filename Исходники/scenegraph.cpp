Affine3 SgCamera::positionLookingFor(const Vector3& eye, const Vector3& direction, const Vector3& up)
{
    Vector3 d = direction.normalized();
    Vector3 c = d.cross(up).normalized();
    Vector3 u = c.cross(d);
    Affine3 C;
    C.linear() << c, u, -d;
    C.translation() = eye;
    return C;
}