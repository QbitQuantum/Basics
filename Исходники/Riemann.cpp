Eigen::Matrix<double, 3, 3> getRotationFromA2B(Eigen::Matrix<double, 3, 1> A, Eigen::Matrix<double, 3, 1> B) {
	Eigen::Matrix<double, 3, 1> v = A.cross(B);
	double s = v.norm();
	double c = A.dot(B);

	Eigen::Matrix<double, 3, 3> vx;
	vx <<   0, -v[2], v[1],
			v[2], 0, -v[0],
			-v[1], v[0], 0;
	return Eigen::Matrix<double, 3, 3>::Identity() + vx + ((1.0-c)/(s*s))*vx*vx;
}