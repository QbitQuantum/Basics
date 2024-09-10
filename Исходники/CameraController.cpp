Vec3d CameraController::switchCoordinateSystem_vector( const Vec3d& vec, const Matrixd& from, const Matrixd& to )
{
	Matrixd mat;
	mat.invert(to);

	Vec3d begin = Vec3d(0, 0, 0);
	Vec3d end = vec;

	Vec3d begin2 = begin * from * mat;
	Vec3d end2 = end * from * mat;

	Vec3d v = end2 - begin2;
	return v;
}