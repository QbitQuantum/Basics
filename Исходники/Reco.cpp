// Returns squared mahalanobis distance
float Reco::mahalanobis_distance (Eigen::Matrix3f cov, Eigen::Vector3f mean, pcl::PointXYZ pt)
{
	Eigen::Vector3f diff (pt.x - mean[0], pt.y - mean[1], pt.z - mean[2]);
	//return diff.dot(cov.inverse() * diff);
	return sqrt(diff.dot(cov.inverse() * diff));
}