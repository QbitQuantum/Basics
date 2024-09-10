GLCamera::GLCamera(const Vector3d &pos, const Vector3d &target, const Vector3d &up)
{
    m_pos = pos;
    m_target = target;
    m_up = up;
    n = Vector3d( pos.x-target.x, pos.y-target.y, pos.z-target.z);
    u = Vector3d(up.cross(n).x, up.cross(n).y, up.cross(n).z);
    v = Vector3d(n.cross(u).x,n.cross(u).y,n.cross(u).z);

    n.normalize();
    u.normalize();
    v.normalize();

    setModelViewMatrix();
}