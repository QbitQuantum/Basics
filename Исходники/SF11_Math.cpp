Quaternion::Quaternion(const Float3x3& m)
{
    *this = XMQuaternionRotationMatrix(m.ToSIMD());
}