Quat	Util_L::GetOrientationQuat(const Vec3f &_front, const Vec3f &_baseUp, S32 _order[3])
{
	// orientation / sol
	Mat4x4	rot;
	Quat	qRot;
	Vec3f	vRight = _front ^  _baseUp;
	vRight.CNormalize();
	Vec3f	vUp = vRight ^ _front;
	vUp.CNormalize();	
	Vec3f	v[3] = { _front, vUp, vRight };	
	for (S32 i = 0;i < 3;i++)
		rot.GetRow(i) = Sign(_order[i]) * v[Abs(_order[i]) - 1];
	qRot = Quat(rot);
	qRot.Normalize();
	return qRot;
}