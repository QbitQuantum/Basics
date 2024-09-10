inline Eigen::Vector3d
Pose::unmap(const Eigen::Vector3d& point) const
{
	// Convention: x = R^T * (x' - T)
	return m_orientation.inverse() * (point  -  m_position);
}