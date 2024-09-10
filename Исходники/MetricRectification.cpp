Eigen::Vector3d MetricRectification::normalizeLine(Eigen::Vector3d p0, Eigen::Vector3d p1)
{
	Eigen::Vector3d l = p0.cross(p1);
	l.x() = l.x() / l.z();
	l.y() = l.y() / l.z();
	l.z() = 1.0;
	//return l;
	return p0.cross(p1).normalized();
}