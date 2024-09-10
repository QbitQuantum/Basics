Vector3d Vector3d::rotate(const Quaternion& rot_q) const
{
    Quaternion vec_q(this->x, this->y, this->z, 0);
    vec_q = (rot_q*vec_q)*rot_q.conjugate();
    Vector3d ret(vec_q.x, vec_q.y, vec_q.z);
    return ret;
}