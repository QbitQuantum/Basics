Eigen::Vector3d get_earth_dipole(const Eigen::Vector3d& position)
{
	const double distance = position.norm();
	const Eigen::Vector3d
		direction = position / distance,
		projected_dip_mom = dipole_moment.dot(direction) * direction;

	return 1e-7 * (3 * projected_dip_mom - dipole_moment) / std::pow(distance, 3);
}