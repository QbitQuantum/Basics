Eigen::Vector3d QuaternionToExponentialMap(const Eigen::Quaterniond& quaternion)
{
	Eigen::Vector3d vec = quaternion.vec();
    if (vec.norm() < ITOMP_EPS)
		return Eigen::Vector3d::Zero();

	double theta = 2.0 * std::acos(quaternion.w());
	vec.normalize();
	return theta * vec;
}