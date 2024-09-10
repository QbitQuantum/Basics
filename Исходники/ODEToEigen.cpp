Affine3d FromODETransformToEigenTransform(const dReal* pos, const dReal* rot)
{
	Affine3d ret;
	Vector3d trans;
	trans << pos[0], pos[1], pos[2];
	ret.translation() = trans;

	Matrix3d rotation = FromODERotationToEigenMatrix(rot);
	ret.linear() = rotation;
	return ret;
}