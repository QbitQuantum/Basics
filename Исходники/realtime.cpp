void
drawBoundingBox(PointCloudT::Ptr cloud,
				boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer,
				int z)
{
	
	//Eigen::Vector4f centroid;
	pcl::compute3DCentroid(*cloud, centroid);
	
	//Eigen::Matrix3f covariance;
	computeCovarianceMatrixNormalized(*cloud, centroid, covariance);
	//Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigen_solver(covariance,
	//Eigen::ComputeEigenvectors);

	eigen_solver.compute(covariance,Eigen::ComputeEigenvectors);
	
//	eigen_solver = boost::shared_ptr<Eigen::SelfAdjointEigenSolver>
//		(covariance,Eigen::ComputeEigenvectors);

	eigDx = eigen_solver.eigenvectors();
    eigDx.col(2) = eigDx.col(0).cross(eigDx.col(1));


	//Eigen::Matrix4f p2w(Eigen::Matrix4f::Identity());
	p2w.block<3,3>(0,0) = eigDx.transpose();
	p2w.block<3,1>(0,3) = -1.f * (p2w.block<3,3>(0,0) * centroid.head<3>());
    //pcl::PointCloud<PointT> cPoints;
    pcl::transformPointCloud(*cloud, cPoints, p2w);


	//PointT min_pt, max_pt;
    pcl::getMinMax3D(cPoints, min_pt, max_pt);
    const Eigen::Vector3f mean_diag = 0.5f*(max_pt.getVector3fMap() + min_pt.getVector3fMap());

	const Eigen::Quaternionf qfinal(eigDx);
    const Eigen::Vector3f tfinal = eigDx*mean_diag + centroid.head<3>();
	
	//viewer->addPointCloud(cloud);
	viewer->addCube(tfinal, qfinal, max_pt.x - min_pt.x, max_pt.y - min_pt.y, max_pt.z - min_pt.z,boost::lexical_cast<std::string>((z+1)*200));

}