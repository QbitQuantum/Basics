// Calculate the distance between the point and the plane
static double GetDistanceToPlane(const pcl::PointXYZ& point, const Eigen::Vector3f& normalVector, double d)
{
	Eigen::Vector3f t;
	t << point.x, point.y, point.z;
	return fabs(t.dot(normalVector) + d);
}