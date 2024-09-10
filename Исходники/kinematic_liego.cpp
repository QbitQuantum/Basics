Eigen::Matrix4f ForwardKinematicsLiego::getEpsilon(Eigen::Vector3f omega,
		Eigen::Vector3f q) {
	Eigen::Matrix4f eps = getDash(omega);
	omega = -omega.cross(q);
	eps(0, 3) = omega[0];
	eps(1, 3) = omega[1];
	eps(2, 3) = omega[2];
	return eps;
}