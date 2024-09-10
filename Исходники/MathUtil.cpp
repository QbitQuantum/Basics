tQuaternion cMathUtil::QuatDiff(const tQuaternion& q0, const tQuaternion& q1)
{
	return q1 * q0.conjugate();
}