void PLTools::Rotate(const Quat &qQuat, Point3 &vVector)
{
	Quat qRes = qQuat.Conjugate()*Quat(vVector.x, vVector.y, vVector.z, 0.0f)*qQuat;
	vVector.x = qRes.x;
	vVector.y = qRes.y;
	vVector.z = qRes.z;
}